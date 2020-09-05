// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
//Generate Last
#include "TankHUD.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_TANK_API ATankHUD : public AHUD
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

	//SWidget Menu
	TSharedPtr<class SMenu> smenu;
	//SWidget Container
	TSharedPtr<class SWidget> widget_container;

	//UMG
	UUserWidget *current_widget = nullptr;


public:
	//Slate
	void _show_pause_menu();
	void _remove_menu();
	// void DrawHUD() override;
	//UMG
	void _set_current_widget(UUserWidget *current_widget_toset);
};
