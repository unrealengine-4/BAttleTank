// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "TankBarrel.h"
// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::GetBarrelAndTurretRefrance(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!BarrelToSet || !TurretToSet) { 
		UE_LOG(LogTemp, Warning, TEXT("Get Barrel And Turret Refrance Not Found in Aiming Component"));
		return; 
	}
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) {
		UE_LOG(LogTemp, Warning, TEXT("Barrel Refrance Not Found in Aiming Component"));
		return; 
	}
	FVector OutLaunchVelocity;
	auto StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//Calculate the outvelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if(bHaveAimSolution)
	{
		auto AimDerection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrleTowards(AimDerection);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("suggestprojectile velocityaim direction not found"));
	}
	
}

void UTankAimingComponent::MoveBarrleTowards(FVector AimDerection)
{
	//Workout current deffrance between current barrel rotaion, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDerection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::Check()
{
	UE_LOG(LogTemp, Warning, TEXT("I am loging becouse check method is called "));
}