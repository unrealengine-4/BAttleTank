// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
/**
 * responsible for driving the tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
public:

	//is used for moving tank 1,-1
	UFUNCTION(BlueprintCallable, category = Movement)
	void IntendMoveForword(float Throw);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankTrack* LeftTraceToSet, UTankTrack* RightTrackToSet);

	UFUNCTION(BlueprintCallable, category = Movement)
	void IntendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable, category = Movement)
	void IntendTurnLeft(float Throw);

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;


private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;


};
