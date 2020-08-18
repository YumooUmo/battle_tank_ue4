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
	UProjectileMovementComponent *projectile_movement_component = nullptr;
	
	//Get launch_speed
	virtual float _get_launch_speed() const;

	//Launch
	virtual void _launch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float launch_speed = 100000.f;
};
