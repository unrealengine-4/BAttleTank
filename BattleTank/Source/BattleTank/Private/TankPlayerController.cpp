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

ATank* ATankPlayerController::GetControlledTank() const
{
	return	Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; 
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}

	//tell controled tank to ain at rthis point

}
//get world location through crosshair  if it hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//find the crosshair position
	int32 ViewpoertSizeX, ViewportSizeY;
	GetViewportSize(ViewpoertSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewpoertSizeX * CrossHairXLocation,  ViewportSizeY * CrossHairYLocation);

	//Deproject the screen position	of the croshair to a world dorection
	FVector CameraWorldLocation;
	FVector LookDirection;
	DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);

		//Line trace along that look direction and see what we hit (up to max range)
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * TraceRange;
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
	))
	{
		HitLocation = HitResult.Location;
	}
	else
	{
		HitLocation = FVector(0.0);
	}
	return true;
}
