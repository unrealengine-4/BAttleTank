	// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "TankAimingComponent.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetPawn();
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
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

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnDeath.AddUniqueDynamic(this, &	ATankPlayerController::PossessedTankDeth);
	}
}

void ATankPlayerController::StartSpectatingOnly()
{
	Super::StartSpectatingOnly();
}

void ATankPlayerController::PossessedTankDeth()
{
	UE_LOG(LogTemp, Warning, TEXT("You Died"));
	StartSpectatingOnly();
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(TankAimingcomponent)) { return; }

	FVector HitLocation; 
	bool HitResult = GetSightRayHitLocation(HitLocation);
	if (HitResult)
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
		return true;
	}
	else
	{
		HitLocation = FVector(0.0);
	}
	return false;
}
