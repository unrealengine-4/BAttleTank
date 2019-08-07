// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottel(float Throttel)
{
	//auto Time = GetWorld()->GetTimeSeconds();


	//TODO clamp actual throttle value so usser Can not Over-Derive

	auto ForceApplied = GetForwardVector() * Throttel * TrackMaxDriingFource;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}