// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto GetControlledTank = Cast<ATank>(GetPawn());
	auto GetPlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (GetPlayerTank) {
		
		//Move towards player
		MoveToActor(GetPlayerTank, AcceptanceRedius);
		

		//fire
		auto HitLocation = GetPlayerTank->GetActorLocation();
		GetControlledTank->AimAt(HitLocation);

		GetControlledTank->Fire();//TODO dont fire every frame

	}
}
