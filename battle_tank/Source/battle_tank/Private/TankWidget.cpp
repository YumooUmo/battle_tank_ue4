// Fill out your copyright notice in the Description page of Project Settings.

#include "TankWidget.h"
#include "TimerManager.h"
#include "UMG.h"
// UTankWidget::UTankWidget(const FObjectInitializer &ObjectInitializer){};

void UTankWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
//setup
void UTankWidget::_setup(UImage *crosshair_toset, UImage *aiming_box_toset,
						 UImage *projectile_image_toset, UProgressBar *lock_buffer_bar_toset)
{
	crosshair = crosshair_toset;
	aiming_box = aiming_box_toset;
	projectile_image = projectile_image_toset;
	lock_buffer_bar = lock_buffer_bar_toset;
}

// - Aiming Box -
void UTankWidget::_show_aiming_box(bool flag)
{
	if (aiming_box == nullptr)
	{
		return;
	}
	if (flag)
	{
		if (aiming_box->Visibility == ESlateVisibility::Hidden)
		{
			aiming_box->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		if (aiming_box->Visibility == ESlateVisibility::Visible)
		{
			aiming_box->SetVisibility(ESlateVisibility::Hidden);
		}
	}
};

// - Change Projectile Image - set reload_time
void UTankWidget::_setup_projectile(float reload_time_toset, UTexture2D *projectile_texture_toset)
{
	reload_time = reload_time_toset;
	projectile_image->SetBrushFromTexture(projectile_texture_toset);
};

// - Reload Image -
void UTankWidget::_reload_projectile()
{
	if (projectile_image == nullptr)
	{
		return;
	}
	if (reload_timer.IsValid())
	{
		sum_reload_time = 0.f;
	}
	GetWorld()->GetTimerManager().SetTimer(reload_timer, this,
										   &UTankWidget::_show_reload_projectile,
										   pace, true);
};
//CALL : hide - fire
void UTankWidget::_hide_projectile_image()
{
	projectile_image->SetVisibility(ESlateVisibility::Hidden);
};
//show every tick, stop at reload time finish;
void UTankWidget::_show_reload_projectile()
{
	if (sum_reload_time < reload_time)
	{
		sum_reload_time += pace;
		projectile_image->SetOpacity(_repeat(max_repeat_opacity, pace));
		if (sum_reload_time >= reload_time)
		{
			sum_reload_time = 0.f;
			projectile_image->SetOpacity(1.f);
			GetWorld()->GetTimerManager().ClearTimer(reload_timer);
		}
	}
};

// - Lock Buffer -
void UTankWidget::_setup_lock_buffer(float max_buffer_toset)
{
	max_buffer = max_buffer_toset;
}
void UTankWidget::_update_lock_buffer(float lock_buffer_toset, AimingState aiming_state_toset)
{
	lock_buffer = lock_buffer_toset;
	aiming_state = aiming_state_toset;
};
void UTankWidget::_do_lock_buffer()
{
	if (lock_buffer_bar == nullptr)
	{
		return;
	}
	if (lock_buffer_timer.IsValid())
	{
		return;
	}
	if (max_buffer > 0)
	{
		lock_buffer_bar->SetRenderOpacity(100.f);
		GetWorld()->GetTimerManager().SetTimer(lock_buffer_timer, this,
											   &UTankWidget::_show_lock_buffer,
											   pace, true);
	}
};
void UTankWidget::_show_lock_buffer()
{
	static float lag = 0.f;

	if (lock_buffer == max_buffer)
	{
		lag += pace;
		lock_buffer_bar->SetRenderOpacity(1.f - lag);
		if (lag > 1.f)
		{
			GetWorld()->GetTimerManager().ClearTimer(lock_buffer_timer);
			lag = 0.f;
		}
	}
	else
	{
		if (aiming_state == AimingState::usable)
		{
			lock_buffer_bar->SetFillColorAndOpacity(FLinearColor(0.065f, 0.130f, 0.796f, 0.7f));
		}
		else if (aiming_state == AimingState::locking)
		{
			lock_buffer_bar->SetFillColorAndOpacity(FLinearColor(0.755f, 0.529f, 0.072f, 0.7f));
		}
		else if (aiming_state == AimingState::overheat)
		{
			lock_buffer_bar->SetFillColorAndOpacity(
				lock_buffer > 0 ? FLinearColor(0.242f, 0.242f, 0.242f, 0.7f)
								: FLinearColor(0.517f, 0.043f, 0.043f, 0.7f));
		}
		lock_buffer_bar->SetPercent(lock_buffer / max_buffer);
		lag = 0.f;
	}
};

//	TODO : Add Curve
float UTankWidget::_repeat(float max, float pace)
{
	static float sum = 0.f;
	static bool add = true;
	if (!add)
	{
		if (sum > 0)
		{
			sum -= pace;
			if (sum <= 0)
			{
				sum = 0;
				add = true;
			}
		}
	}
	else
	{
		if (sum < 1.f)
		{
			sum += pace;
			if (sum >= 1.f)
			{
				sum = 1.f;
				add = false;
			}
		}
	}
	return sum * max;
}
