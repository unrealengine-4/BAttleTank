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
	
private:
	UTankTrack();

public:
	//Beginplay
	virtual void BeginPlay() override;

	//tick
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void ApplySidwayForce();


	UFUNCTION(BlueprintCallable, Category = "input")
	void SetThrottel(float Throttel);

	void DriveTrack();

	float CurrentThrottel = 0;

	//Max force per trace, in newtons
	UPROPERTY(EditDefaultsOnly, Category = "Force")
	float TrackMaxDriingFource = 400000; //assunme 40 tun tank and, 1G accelration

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);


};
