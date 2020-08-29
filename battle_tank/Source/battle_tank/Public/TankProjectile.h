// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//last generate
#include "TankProjectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class BATTLE_TANK_API ATankProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATankProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//------------------------------------------public---------------------------------------------

	//SET MovementComponent
	// UProjectileMovementComponent *projectile_movement_component = nullptr;

	//Reload time
	UPROPERTY(EditAnywhere, Category = Setup)
	float reload_time = 2.f;

	//launch_speed
	UPROPERTY(EditAnywhere, Category = Setup)
	float launch_force = 50000.f;

	//Launch
	virtual void _launch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
