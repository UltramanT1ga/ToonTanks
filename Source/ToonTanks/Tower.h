// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn {
	GENERATED_BODY()

public:
	ATower();
	virtual void Tick(float DeltaTime) override;
	void HandleDestruction();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Fire")
	float FireDistance = 800.f;
	
	ATank* Tank;

	float FireRate = 2.f;
	FTimerHandle FireTimeHandler;
	void CheckFireCondition();
	bool InFireDistance();
};

