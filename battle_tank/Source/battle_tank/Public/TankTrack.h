// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Setup)
	float _max_force = 4000000.f;

	UFUNCTION(BlueprintCallable, Category = play)
	void _set_throttle(float throttle);

};
