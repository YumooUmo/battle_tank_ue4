// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "AimingState.h"
#include "WeaponState.h"
//last generate
#include "TankWidget.generated.h"

// class UImage
/**
 *
 */
class UImage;
class UProgressBar;
class UTexture2DDynamic;
// class AimingState;

UCLASS()
class BATTLE_TANK_API UTankWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// UTankWidget(const FObjectInitializer &ObjectInitializer);
	virtual void NativeConstruct() override;

	//	UI property
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = flicker)
	float max_repeat_opacity = 0.6f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = flicker)
	float pace = 0.01f;
	//(framerate)

	//	UI object
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = UI)
	UImage *crosshair;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = UI)
	UImage *aiming_box;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = UI)
	UImage *projectile_image;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = UI)
	UProgressBar *lock_buffer_bar;

	//CALL: Show Aiming Box
	void _show_aiming_box(bool flag);

	//CALL : Reload Image
	void _reload_projectile();
	//show
	void _show_reload_projectile();

	//CALL : change projectile image
	UFUNCTION(BlueprintNativeEvent)
	void _set_projectile(float reload_time_toset, UTexture2DDynamic *projectile_texture_toset);

	//CALL : update
	void _update_lock_buffer(float lock_buffer_toset, AimingState aiming_state_toset);
	//CALL : _Lock draw
	void _do_lock_buffer();
	//show
	void _show_lock_buffer();

private:
	//Reload State
	static float _repeat(float max, float pace);
	float sum_reload_time = 0.f;
	float reload_time = 0.f;

	//Aiming State
	AimingState aiming_state = AimingState::usable;
	float max_buffer = 0.f;
	float lock_buffer = max_buffer;

	FTimerHandle reload_timer;
	FTimerHandle lock_buffer_timer;
};
