// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	TankAimingComponet = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto GetControlledTank = GetPawn();
	auto GetPlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!TankAimingComponet) { return; }
	if (GetPlayerTank) {
		
		//Move towards player
		MoveToActor(GetPlayerTank, AcceptanceRedius);
		

		//fire
		auto HitLocation = GetPlayerTank->GetActorLocation();
		TankAimingComponet->AimAt(HitLocation);

		if (TankAimingComponet->GetFiringState() == EFiringState::Locked)
		{
			TankAimingComponet->Fire();//TODO dont fire every frame
		}
	

	}
}
