// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

//tick
void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	//calculate Slippagespeed 
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
		
	//workout requred accelration this frame tocorrect
	auto CurrectionAccelration = - SlippageSpeed / DeltaTime * GetRightVector();
	
	//calculate apply sideway for m = m a
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CurrectionForce = (TankRoot->GetMass() * CurrectionAccelration) / 2;
	TankRoot->AddForce(CurrectionForce); 
}

void UTankTrack::SetThrottel(float Throttel)
{
	//auto Time = GetWorld()->GetTimeSeconds();


	//TODO clamp actual throttle value so usser Can not Over-Derive

	auto ForceApplied = GetForwardVector() * Throttel * TrackMaxDriingFource;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}