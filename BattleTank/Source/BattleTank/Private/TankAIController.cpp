// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	TankAimingComponet = Cast<ATank>(GetPawn())->FindComponentByClass<UTankAimingComponent>();
}
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto GetControlledTank = Cast<ATank>(GetPawn());
	auto GetPlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!TankAimingComponet) { return; }
	if (GetPlayerTank) {
		
		//Move towards player
		MoveToActor(GetPlayerTank, AcceptanceRedius);
		

		//fire
		auto HitLocation = GetPlayerTank->GetActorLocation();
		TankAimingComponet->AimAt(HitLocation);

		GetControlledTank->Fire();//TODO dont fire every frame

	}
}
