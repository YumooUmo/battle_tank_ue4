// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AimingState.h"
#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
//last generate
#include "AimingComponent.generated.h"

class ATankPlayerController;
class ATank;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAimingComponent();

	virtual void BeginPlay() override;

	//Setup
	void _set_controller(ATankPlayerController *player_controller_toset);

	//Property
	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	float max_buffer = 5.f;
	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	float lock_buffer = max_buffer;
	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	float cool_rate = 0.8f;
	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	float recover_value = 2.f;
	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	float overheat_lag = 2.f;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	AimingState aiming_state = AimingState::usable;

	//Lock action
	virtual void _should_lock();
	virtual void _lock(bool flag);

	//CALL : Draw Projectile Path
	void _draw_projectile_path();

protected:
	ATankPlayerController *player_controller = nullptr;
	ATank *owner_tank = nullptr;

	//framerate to seconds
	UPROPERTY(EditDefaultsOnly, Category = "Framerate(seconds)")
	float pace = 0.01f;

	FTimerHandle lock_timer;

private:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
