// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

//ENUM
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAimo
};


//forwod declaration

class ATank;
class AProjectile;
class UTankBarrel;
class UTankTurret;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()
		
protected:

	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Aiming;


public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	//Beigne Play
	virtual void BeginPlay() override;

	//Tick
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	//Firing projectile 
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void GetBarrelAndTurretRefrance(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
		
	bool IsBarrelMovig();


public:	

	EFiringState GetFiringState() const;
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	int GetRoundsLeft() const;

	void AimAt(FVector HitLocation);

	void MoveBarrleTowards(FVector AimDerection);
		
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditAnywhere, Category = "Firing")
	int RoundLeft = 3;

	FVector AimDirection;

private:
	

	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchSpeed = 5000;

	UPROPERTY(EditAnywhere, Category = "Firing")
		float ReloadTimeSeconds = 3;

	

	double LastFireTime = 0;

	
};
