// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "AimingComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAimingComponent();
	virtual void BeginPlay() override;
	virtual void _set_barrel_reference(UStaticMeshComponent *barrel_to_set);
	virtual void _aiming_at(FVector aiming_location);

	virtual void _draw_projectile_path(float launch_speed);
	virtual void _launch();

protected:
	// Called when the game starts

private:
	FVector launch_velocity{0}; //####get from barrel aiming
	FVector aiming_normal{0};

	UStaticMeshComponent *barrel = nullptr;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
