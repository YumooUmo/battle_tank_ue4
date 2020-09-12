// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
//last generate
#include "TankWidget.generated.h"

// class UImage
/**
 *
 */
class UImage;
class UProgressBar;
class UTexture;
class UTextBlock;
// class AimingState;

UCLASS()
class BATTLE_TANK_API UTankWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UTankWidget(const FObjectInitializer &ObjectInitializer);
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UImage *crosshair;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UImage *projectile_image;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UProgressBar *lock_buffer_bar;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UTextBlock *ammo_amount;

	// - Draw -
	void _set_crosshair_fcolor(FLinearColor color_toset);

	void _set_projectile_image_texture(UTexture2D *projectile_texture_toset);

	void _set_projectile_image_ropacity(float render_opacity_toset);

	void _set_ammo_amount(FText ammo_toset);

	void _set_lock_buffer_bar_ropacity(float render_opacity_toset);

	void _set_lock_buffer_bar_fcolor(FLinearColor color_toset);

	void _set_lock_buffer_bar_percent(float percent_toset);

};
