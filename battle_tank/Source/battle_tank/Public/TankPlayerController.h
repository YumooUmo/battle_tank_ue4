// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// #include "battle_tank.h"
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
	UPROPERTY(VisibleAnywhere)
	float aiming_range = 100000.f;
	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	float crosshair_x = 0.5;
	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	float crosshair_y = 0.35;

	ATankHUD *tank_HUD = nullptr;
	FVector aiming_normal{0};

	ATank *tank_controlled = nullptr;

	//-------------------------------TICK--------------------------------

	//-------By Location
	// void _aiming() const;

public:
	//-------------------------------GET----------------------------------
	// bool _get_screen_aiming_location(FVector &location_screen_aiming) const;
	UFUNCTION(BlueprintCallable, Category = Comppnent)
	void _get_aiming_normal();

	void _set_current_widget(UTankWidget *widget_toset);
};