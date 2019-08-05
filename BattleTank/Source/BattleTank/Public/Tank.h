	// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelRefrance(UTankBarrel* BarreToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretRefrance(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Fire();


protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

public:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector HitLocation);

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;
	
	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 10000;

	UPROPERTY(EditAnywhere, Category = Firing)
	float ReloadTimeSeconds = 3;

	

private:
	///Local barrel refrance for spawning a proejectile
	UTankBarrel* Barrel = nullptr;

	
	double LastFireTime = 0;
	
};
