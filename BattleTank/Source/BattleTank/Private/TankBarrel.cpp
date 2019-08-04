// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	//Move the barrel right amount this frame 
	//Given the maximum elivation speed each frsme
	auto ClampReletiveSpeed = FMath::Clamp <float> (RelativeSpeed, -1, +1);
	auto ElevationChange = ClampReletiveSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto RawClamp = FMath::Clamp<float>(RawNewElevation, MinElevationInDegree, MaxElevaioInDegree);
	SetRelativeRotation(FRotator(RawClamp, 0, 0));
}