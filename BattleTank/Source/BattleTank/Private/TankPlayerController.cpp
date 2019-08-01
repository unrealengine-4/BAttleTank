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

ATank* ATankPlayerController::GetControlledTank()
{
	return	Cast<ATank>(GetPawn());
}