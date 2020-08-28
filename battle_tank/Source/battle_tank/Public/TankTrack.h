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
	unsigned short socket_amount = 3;

	FVector *sockets = new FVector[socket_amount*2];

	void _refresh_force_sockets();

private:
	// FVector sockets[][];
	// TArray<FVector> b[3][2];
	void _reset_sockets();
};
