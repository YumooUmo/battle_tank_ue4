// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AimingState.h"
#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
//last generate
#include "AimingComponent.generated.h"

class UTankBarrel;
class UTankTurrent;
class ATankHUD;
class ATankProjectile;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

protected:
	// - Turrent -
	// UPROPERTY(BlueprintReadOnly, Category = "Mesh")
	UTankBarrel *barrel = nullptr;
	// UPROPERTY(BlueprintReadOnly, Category = "Mesh")
	UTankTurrent *turrent = nullptr;
	bool is_moving = true;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float ai_aiming_tolerance = 0.03f;
	bool ai_aiming = false;

	// - Lock -
	/*OUT Dpendence - launch speed*/
	float launch_speed = 0.f;

	//property
	UPROPERTY(BlueprintReadOnly, Category = "Lock")
	AimingState aiming_state = AimingState::usable;

	UPROPERTY(EditDefaultsOnly, Category = "Lock")
	float max_buffer = 5.f;
	UPROPERTY(EditDefaultsOnly, Category = "Lock")
	float lock_buffer = max_buffer;
	UPROPERTY(EditDefaultsOnly, Category = "Lock")
	float cool_rate = 0.8f;
	UPROPERTY(EditDefaultsOnly, Category = "Lock")
	float recover_value = 2.f;
	UPROPERTY(EditDefaultsOnly, Category = "Lock")
	float overheat_lag = 2.f;

	FTimerHandle lock_timer;

	// - HUD -
	ATankHUD *tank_hud = nullptr;

public:
	// Sets default values for this component's properties
	UAimingComponent();
	virtual void BeginPlay() override;

	// - Setup -
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void _setup(UTankTurrent *turrent_toset, UTankBarrel *barrel_toset);
	// UI
	void _set_hud();
	void _set_widget();

	// - Break -
	void _break_barrel();
	void _break();

	// - Get -
	//vector
	FVector _get_launch_normal();
	//location
	FVector _get_launch_location();
	// is_barrel
	bool _is_barrel();
	// is_turrent
	bool _is_turrent();
	//is aiming on (for AI, return ai_aiming)
	bool _is_aiming_on();

	// - Turing -
	//_turning_to to aiming_direction
	virtual void _turning_to(FVector aiming_normal);
	//ai aiming
	virtual void _ai_turning(FVector aiming_location);

	// - Lock -
	//action
	virtual void _lock(bool flag);
	virtual void _should_lock();
	/*OUT Dpendence - launch speed*/
	void _update_launch_speed(float launch_speed_toset);

	//CALL : Draw Projectile Path
	void _draw_projectile_path();
};
