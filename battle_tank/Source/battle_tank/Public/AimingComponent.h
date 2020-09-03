// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
//last generate
#include "AimingComponent.generated.h"

class ATank;
UENUM()
enum class AimingState : uint8
{
	usable,
	locking,
	overheat
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAimingComponent();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	float max_buffer = 5.f;
	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	float draw_buffer = max_buffer;
	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	float cool_rate = 0.8f;
	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	float recover_value = 2.f;
	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	float overheat_lag = 2.f;

	virtual void _lock_projectile_path(FVector launch_velocity, FVector launch_location, AActor *ignore);
	virtual bool _should_lock();
	virtual float _lock(bool flag);

	UPROPERTY(BlueprintReadOnly, Category = "State")
	AimingState aiming_state = AimingState::usable;
	
protected:

private:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
