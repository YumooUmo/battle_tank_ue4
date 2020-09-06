// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "AimingState.h"
#include "CoreMinimal.h"
//generate last
#include "TankUIComponent.generated.h"

class ATankHUD;
class UTankWidget;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API UTankUIComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankUIComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void _setup_widget(TSubclassOf<UTankWidget> tank_widget_class_toset);

	void _set_widget();
	void _unset_widget();

	/* - Draw - 
    * 
    */
	//CALL: Show Aiming Box
	void _show_aiming_box(bool flag);
	//CALL : change projectile image
	void _setup_projectile(float reload_time_toset, UTexture2D *projectile_texture_toset);
	//CALL : Reload Image
	void _reload_projectile();

	//CALL : Setup lock buffer
	void _setup_lock_buffer(float max_buffer_toset);
	//CALL : update
	void _update_lock_buffer(float lock_buffer_toset, AimingState aiming_state_toset);
	//CALL : _Lock draw
	void _do_lock_buffer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	ATankHUD *tank_HUD = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Widget")
	TSubclassOf<UTankWidget> tank_widget_Subclass = nullptr;
	UTankWidget *tank_widget = nullptr;
};
