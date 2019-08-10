// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "TankPlayerController.generated.h"


/**
 * 
 */

class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()


protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComonent(UTankAimingComponent* TankAimingCompRef);

public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	

	///helps to move barrel towards crossair
	void AimTowardsCrosshair();
	///Get the world location through crosshair
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333;

	UPROPERTY(EditAnywhere)
	float TraceRange = 1000000;

private:
	UTankAimingComponent* TankAimingcomponent = nullptr;

};