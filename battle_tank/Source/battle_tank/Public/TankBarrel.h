// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
//last generate
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Mobile"))
class BATTLE_TANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

	// UStaticMesh static_mesh;

public:
	//Get Launch location of the barrel
	virtual FVector _get_launch_location() const;

	//Get Launch Velocity : where Barrel Actually Aiming at right now
	virtual FVector _get_launch_normal() const;

	//Elevate to Aiming velocity
	virtual bool _elevate_barrel(float relative_speed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float _max_elevate_speed = 20.f;

	UPROPERTY(EditAnywhere, Category = Setup)
	float _max_elevate_angle = 40.f;

	UPROPERTY(EditAnywhere, Category = Setup)
	float _min_elevate_angle = -10.f;
};
