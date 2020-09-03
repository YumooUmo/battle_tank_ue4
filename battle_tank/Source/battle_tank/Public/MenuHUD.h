// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
//Generate Last
#include "MenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_TANK_API AMenuHUD : public AHUD
{
	GENERATED_BODY()
protected:
	TSharedPtr<class SMenu> smenu;
	TSharedPtr<class SWidget> widget_container;

	virtual void BeginPlay() override;

public:
	void _show_menu();
	void _remove_menu();
};
