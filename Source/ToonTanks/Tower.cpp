// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h" 
#include "Kismet/GameplayStatics.h"

ATower::ATower() {}

void ATower::BeginPlay() {
  Super::BeginPlay();
  Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
  GetWorldTimerManager().SetTimer(FireTimeHandler, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(float DeltaTime) {
  Super::Tick(DeltaTime); 
  if (InFireDistance()) {
    TurnTurret(Tank->GetActorLocation());
  }
}

bool ATower::InFireDistance() {
  if (Tank) {
    FVector TankLocation = Tank->GetActorLocation();
    if (FVector::Dist(GetActorLocation(), TankLocation) <= FireDistance) {
      return true;
    }
  }
  return false;
}

void ATower::CheckFireCondition() {
  if (InFireDistance() && Tank && Tank->bAlive) {
    Fire();
  }
}

void ATower::HandleDestruction() {
  Super::HandleDestruction();
  Destroy();
}
