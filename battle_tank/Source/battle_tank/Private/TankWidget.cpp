// Fill out your copyright notice in the Description page of Project Settings.

#include "TankWidget.h"
#include "TimerManager.h"
#include "UMG.h"
// UTankWidget::UTankWidget(const FObjectInitializer &ObjectInitializer){};

UTankWidget::UTankWidget(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer){
		FString name =GetName();
	UE_LOG(LogTemp, Warning, TEXT("DONKEY : Widget %s C++ Construct "),*name);
};

void UTankWidget::NativeConstruct()
{
	Super::NativeConstruct();
		FString name =GetName();
	UE_LOG(LogTemp, Warning, TEXT("DONKEY : Widget %s C++ NativeConstruct "),*name);
}

// - GET -
UImage *UTankWidget::_get_crosshair()
{
	return crosshair;
};
UImage *UTankWidget::_get_projectile_image()
{
	return projectile_image;
};
UProgressBar *UTankWidget::_get_lock_buffer_bar()
{
	return lock_buffer_bar;
};

/* - Draw -
 *				#### TODO : Template
 */
// - Crosshair -
void UTankWidget::_set_crosshair_fcolor(FLinearColor color_toset)
{
	crosshair->SetColorAndOpacity(color_toset);
};

// - Projectile Image -
void UTankWidget::_set_projectile_image_texture(UTexture2D *projectile_texture_toset)
{
	projectile_image->SetBrushFromTexture(projectile_texture_toset);
};

void UTankWidget::_set_projectile_image_ropacity(float render_opacity_toset)
{
	projectile_image->SetRenderOpacity(render_opacity_toset);
};

// - Lock Buffer Bar -
void UTankWidget::_set_lock_buffer_bar_ropacity(float render_opacity_toset)
{
	lock_buffer_bar->SetRenderOpacity(render_opacity_toset);
};

void UTankWidget::_set_lock_buffer_bar_fcolor(FLinearColor color_toset)
{
	lock_buffer_bar->SetFillColorAndOpacity(color_toset);
};

void UTankWidget::_set_lock_buffer_bar_percent(float percent_toset)
{
	lock_buffer_bar->SetPercent(percent_toset);
};
