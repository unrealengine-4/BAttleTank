// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float Rotation)
{
	//Move the Turret right amount this frame 
	auto ClampRotarion = FMath::Clamp<float>(Rotation, -1, +1);
	auto RotationChange = ClampRotarion * MaxDegreePerSeconds * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, NewRotation, 0)); //TODO Tank turret NOT ROTATE 360*
	//Given the maximum rotation speed each frsme
}