	// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent)
	{
		FoundAimingComonent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Aiming component not found"));
	}

	TankAimingcomponent = AimingComponent;
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
	if (!TankAimingcomponent) { 
		UE_LOG(LogTemp, Warning, TEXT("Tank palyer Controller : Tank Aiming component Null pointer ."));
		return; 
	}

	FVector HitLocation; 
	if (GetSightRayHitLocation(HitLocation))
	{
		TankAimingcomponent->AimAt(HitLocation);
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
