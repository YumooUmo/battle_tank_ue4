// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
//last generate
#include "AimingComponent.generated.h"

class ATank;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAimingComponent();
	virtual void BeginPlay() override;
	virtual void _set_owner(ATank *owenr_tank);

	virtual void _aiming_by_normal(FVector aiming_normal, FVector camera_location);
	virtual void _aiming_at(FVector aiming_location);
	virtual void _draw_projectile_path();

protected:
	// Called when the game starts

private:
	ATank *owner;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	virtual void _move_turrent_barrel(FVector aiming_normal);
};
