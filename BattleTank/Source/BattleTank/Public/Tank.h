	// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Delegates/Delegate.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{	
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;

	FTankDelegate OnDeath;	

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	//Return current healt as a persentage of String health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPersent() const;

private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Healt")
		int32 CurrentHealth;



};
