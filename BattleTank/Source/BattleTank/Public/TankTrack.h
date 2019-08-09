// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "input")
	void SetThrottel(float Throttel);

	//Max force per trace, in newtons
	UPROPERTY(EditDefaultsOnly, Category = "Force")
		float TrackMaxDriingFource = 400000; //assunme 40 tun tank and, 1G accelration

};
