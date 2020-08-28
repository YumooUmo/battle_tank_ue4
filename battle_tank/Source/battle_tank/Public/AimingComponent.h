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

	virtual void _draw_projectile_path(FVector launch_velocity, FVector launch_location, AActor *ignore);
	virtual bool _is_drawing(float DeltaTime);
	virtual void _set_drawable(bool flag);


protected:
private:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	float max_buffer = 5.f;
	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	float draw_buffer = 5.f;
	bool draw = false;


};
