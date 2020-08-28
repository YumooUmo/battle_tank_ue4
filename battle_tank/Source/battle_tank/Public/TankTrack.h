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
	FVector **_get_track_sockets();
	void _free_track_sockets();

	void _refresh_force_sockets();

private:
	FVector **sockets = nullptr;
	// FVector sockets[][];
	// TArray<FVector> b[3][2];

	// FVector front_socket[2], track_socket[2], back_socket[2];
	bool track_on = false;
};
