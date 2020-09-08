// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
//last generate
#include "TankTurrent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API UTankTurrent : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	virtual void _rotate_turrent(float relative_speed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float _max_rotate_speed = 100.f;
};
