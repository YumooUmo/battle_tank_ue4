// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AimingState.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
//Generate Last
#include "TankHUD.generated.h"
/**
 * 
 */
class UTankWidget;
class ATankPlayerController;

UCLASS()
class BATTLE_TANK_API ATankHUD : public AHUD
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;
	ATankPlayerController *player_controller = nullptr;

	//SWidget Menu
	TSharedPtr<class SMenu> smenu;
	//SWidget Container
	TSharedPtr<class SWidget> widget_container;

	//UMG
	UTankWidget *tank_widget = nullptr;
	//UMG
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<UUserWidget> tank_widget_subclass;

protected:
	// - Framerate -
	UPROPERTY(EditDefaultsOnly, Category = "FrameratePace")
	float pace = 0.01f;

	// - Flicker -
	//Opacity
	UPROPERTY(EditDefaultsOnly, Category = "Flicker")
	float max_flicker_opacity = 0.3f;
	//param
	float sum_flick = 0.f;
	bool add = true;

	// - Reload -
	//param
	FTimerHandle reload_timer;

	// -Lock Buffer -
	//delay times
	UPROPERTY(EditDefaultsOnly, Category = "DelayTimes")
	float delay_times = 0.5f;
	//param
	AimingState aiming_state = AimingState::usable;
	float lock_buffer_percent;
	FTimerHandle lock_buffer_timer;

	float _flicker(float max);

public:
	//Slate
	void _show_pause_menu();
	void _remove_menu();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void _setup_tank_widget();
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void _remove_tank_widget();

	/* - Draw - 
    * 
    */
	// - Turning -
	//Tank call - SHOW Aiming Box
	void _change_crosshair_color(bool flag);

	//HUD call - change projectile image
	void _setup_projectile(UTexture2D *projectile_texture_toset);
	//Tank call - Reload Image
	void _reload_projectile();
	//Tank call - Reload ready
	void _reload_ready();
	//SHOW
	void _show_reload_projectile();
	//Tank call - Hide
	void _hide_projectile_image();
	
	// - Lock Buffer -
	//Tank call - update
	void _update_lock_buffer(float percent_toset, AimingState aiming_state_toset);
	//Tank call - Lock draw
	void _do_lock_buffer();
	//SHOW
	void _show_lock_buffer();
};
