// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// #include "battle_tank.h"
#include "AimingState.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
//last generate
#include "TankPlayerController.generated.h"

class ATank;
class ATankHUD;
class UTankWidget;

/**
 * 
 */
UCLASS()
class BATTLE_TANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

	//-------------------------------Menu---------------------------------
	void _open_pause_menu();

private:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	//-------------------------------Property-------------------------
	FVector aiming_normal{0.f, 0.f, 0.f};

	UPROPERTY(VisibleAnywhere)
	float aiming_range = 100000.f;
	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	float crosshair_x = 0.5;
	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	float crosshair_y = 0.35;

	//Begin play initialize
	ATankHUD *tank_HUD = nullptr;
	ATank *tank_controlled = nullptr;

public:
	//-------------------------------GET----------------------------------
	// bool _get_screen_aiming_location(FVector &location_screen_aiming) const;
	UFUNCTION(BlueprintCallable, Category = Comppnent)
	void _get_aiming_normal();

	void _setup_tank_widget();
	void _unset_tank_widget();

	/* - Draw - 
    * 
    */

	// - Turning -
	//Tank : Show Aiming Box
	void _change_crosshair_color(bool flag);

	// - Weapon - (Projectile)
	// - HUD : change projectile image
	void _setup_projectile();
	//Tank : Reload Image
	void _reload_projectile();
	//Tank : Hide
	void _hide_projectile_image();

	// - LOCK - (Aiming)
	// - HUD : Setup lock buffer
	void _setup_lock_buffer();
	//Tank : update
	void _update_lock_buffer(float lock_buffer_toset, AimingState aiming_state_toset);
	//Tank : _Lock draw
	void _do_lock_buffer();
};