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
private:
	// - Grounded -
	UFUNCTION()
	void _grounded(UPrimitiveComponent *HitComponent,
				   AActor *OtherActor,
				   UPrimitiveComponent *OtherComponent,
				   FVector NormalImpulse,
				   const FHitResult &Hit);

	// - Friction -
	UPROPERTY(EditAnywhere, Category = "Friction")
	float friction_factor = 3.f;
	float side_speed = 0.f;
	/* Dependency owner */
	//mass
	float tank_mass;
	void _apply_side_friction();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Accelerate")
	float _max_force = 8000000.f;
	float force = 0.f;
	uint8 socket_amount = 3;
	FVector *sockets = new FVector[socket_amount * 2];

public:
	UTankTrack();
	// - Force -
	//sockets
	bool _refresh_force_sockets();
	void _reset_sockets();
	//apply
	void _apply_force(float throttle);
	void _apply_force();
};
