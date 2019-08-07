// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTraceToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTraceToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTraceToSet;
	RightTrack = RightTrackToSet;
}


void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForword = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwordIntention = MoveVelocity.GetSafeNormal();

	auto result = FVector::DotProduct(TankForword, AIForwordIntention);

	auto Rotate = FVector::CrossProduct(TankForword, AIForwordIntention);
	 IntendMoveForword(result);
	IntendTurnRight(Rotate.Z);

}

void UTankMovementComponent::IntendMoveForword(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottel(Throw);
	RightTrack->SetThrottel(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottel(Throw);
	RightTrack->SetThrottel(-Throw);
}

void UTankMovementComponent::IntendTurnLeft(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottel(-Throw);
	RightTrack->SetThrottel(Throw);
}