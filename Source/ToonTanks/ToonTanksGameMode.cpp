// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::ActorDied(AActor* DiedActor) {
  if (DiedActor == Tank) {
    Tank->HandleDestruction();
    if (ToonTanksPlayerController) {
      //Tank->DisableInput(Tank->GetPlayerController());
      //Tank->GetPlayerController()->bShowMouseCursor = false;
      ToonTanksPlayerController->SetPlayerEnabledState(false);
    }
    GameOver(false);
  }
  else if (ATower* Tower = Cast<ATower>(DiedActor)) {
    Tower->HandleDestruction();
    if (!--TowerCount) {
      GameOver(true);
    }
  }
}

void AToonTanksGameMode::BeginPlay() {
  Super::BeginPlay();
  HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart() {
  TowerCount = GetTowerCount();

  Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
  ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
  
  StartGame();
  if (ToonTanksPlayerController) {
    ToonTanksPlayerController->SetPlayerEnabledState(false);

    FTimerHandle TimerHandle;
    FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(
      ToonTanksPlayerController,
      &AToonTanksPlayerController::SetPlayerEnabledState,
      true
    );
    GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, StartDelay, false);
  }
}

int32 AToonTanksGameMode::GetTowerCount() {
  TArray<AActor*> Towers;
  UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
  return Towers.Num();
}