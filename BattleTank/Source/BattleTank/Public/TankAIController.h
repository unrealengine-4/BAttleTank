// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankAIController.generated.h"

/**
 * 
 */

class ATankPlayerController;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn* InPawn) override;
	UTankAimingComponent* TankAimingComponet = nullptr;

private:

	//How far ai tank can com to player tank
	UPROPERTY(EditAnywhere, Category = "setup")
		float AcceptanceRedius = 8000;

	UFUNCTION()
		void OnPossedTankDeath();

};
