// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled tak not dound"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller :%s"), *(ControlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();

}

ATank* ATankPlayerController::GetControlledTank()
{
	return	Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; ///out paramiter

	//get world location through crosshair 
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit location :%s"), *HitLocation.ToString());
	}
	//if it hits the landscape
	//tell controled tank to ain at rthis point

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	return true;
	HitLocation = FVector(1.f);
}