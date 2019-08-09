// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATank::SetAimingComponentRef(UTankAimingComponent* AimingComonentToSet)
{
	TankAimingComponent = AimingComonentToSet;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	if (!TankAimingComponent) {
		UE_LOG(LogTemp, Warning, TEXT("Tank Aiming Component refrnce not fount in tank "));
		return; 
	}
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}


void ATank::Fire()
{
	if (!TankAimingComponent) { return; }
	bool IsReloded = (FPlatformTime::Seconds()) - LastFireTime > ReloadTimeSeconds;

	if (TankAimingComponent->Barrel && IsReloded)
	{
		//spawn a projectile in the socate location of barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
		TankAimingComponent->Barrel->GetSocketLocation(FName("Projectile")),
		TankAimingComponent->Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds(); 
	}

	
}

