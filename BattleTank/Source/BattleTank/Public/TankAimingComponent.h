// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelRefrance(UTankBarrel* BarrelToSet);

	void SetTurretRefrance(UTankTurret* TurretToSet);


public:	
	void AimAt(FVector HitLocation, float LaunchSpeed);

	void MoveBarrleTowards(FVector AimDerection);
		
	UTankBarrel* Barrel;
	UTankTurret* Turret;
};
