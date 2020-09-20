// Fill out your copyright notice in the Description page of Project Settings.

#include "TankHUD.h"
//Include First
#include "Blueprint/UserWidget.h"
#include "Config.h"
#include "Engine/Engine.h"
#include "SMenu.h"
#include "TankWidget.h"
#include "Widgets/SWeakWidget.h"

void ATankHUD::BeginPlay()
{
    Super::BeginPlay();
    FString name = GetName();
    UE_LOG(LogTemp, Warning, TEXT("DONKEY : HUD %s C++ BeginPlay "), *name);
};

// - Set UP -
void ATankHUD::_setup_widget_class(TSubclassOf<UUserWidget> tank_widget_subclass_toset)
{
    tank_widget_subclass = tank_widget_subclass_toset;
};

/* - Flicker -
 * function -                 #### TODO : Add Curve
 */
float ATankHUD::_flicker(float flick_frequence)
{
    if (!add)
    {
        if (sum_flick <= 0)
        {
            sum_flick = 0;
            add = true;
        }
        else if (sum_flick > 0)
        {
            sum_flick -= pace * flick_frequence;
            if (sum_flick <= 0)
            {
                sum_flick = 0;
                add = true;
            }
        }
    }
    else
    {
        if (sum_flick >= 1.f)
        {
            sum_flick = 1.f;
            add = false;
        }
        else if (sum_flick < 1.f)
        {
            sum_flick += pace * flick_frequence;
            if (sum_flick >= 1.f)
            {
                sum_flick = 1.f;
                add = false;
            }
        }
    }
    return sum_flick;
}

/* - Pause Menu -
 * Slate -
 */
void ATankHUD::_show_pause_menu()
{
    if (GEngine && GEngine->GameViewport)
    {
        FText text = FText::FromString("HaHaHa");
        smenu = SNew(SMenu).OwningHUD(this).Title(text);
        // smenu->Get().OnSettingClicked();

        GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(widget_container, SWeakWidget).PossiblyNullContent(smenu.ToSharedRef()));

        if (PlayerOwner)
        {
            PlayerOwner->bShowMouseCursor = true;
            PlayerOwner->SetInputMode(FInputModeUIOnly());
        }
    }
};
void ATankHUD::_remove_menu()
{
    if (GEngine && GEngine->GameViewport && widget_container.IsValid())
    {
        GEngine->GameViewport->RemoveViewportWidgetContent(widget_container.ToSharedRef());
    }
    if (PlayerOwner)
    {
        PlayerOwner->bShowMouseCursor = false;
        PlayerOwner->SetInputMode(FInputModeGameOnly());
        // this->Destroy();
    }
};

/* - Tank Widget -
 * Setup -
 */
void ATankHUD::_setup_tank_widget()
{
    if (!ensure(tank_widget_subclass))
    {
        return;
    }
    if (tank_widget != nullptr)
    {
        tank_widget->RemoveFromViewport();
        tank_widget = nullptr;
    }
    tank_widget = CreateWidget<UTankWidget>(GetWorld(), tank_widget_subclass);
    if (tank_widget)
    {
        tank_widget->AddToViewport();
    }
};

void ATankHUD::_remove_tank_widget()
{
    if (tank_widget)
    {
        tank_widget->RemoveFromViewport();
        tank_widget = nullptr;
    }
};

/* - Tank Widget -
 * Draw - 
 */
// - Turning -
//Tank call - SHOW Aiming Box
void ATankHUD::_change_crosshair_color(bool flag)
{
    if (tank_widget)
    {
        if (flag)
        {
            tank_widget->_set_crosshair_fcolor(FLinearColor(0.638f, 0.f, 0.005f, 0.85f));
        }
        else
        {
            tank_widget->_set_crosshair_fcolor(FLinearColor(0.065f, 0.130f, 0.796f, 0.85f));
        }
    }
};

//HUD start - change projectile image
void ATankHUD::_setup_projectile(UTexture2D *projectile_texture_toset)
{
    if (tank_widget)
    {
        tank_widget->_set_projectile_image_texture(projectile_texture_toset);
    }
};
//Tank call - Reload Image
void ATankHUD::_reload_projectile()
{
    if (tank_widget)
    {
        sum_flick = 0.f;
        if (reload_timer.IsValid())
        {
            return;
        }
        GetWorld()->GetTimerManager().SetTimer(reload_timer, this,
                                               &ATankHUD::_show_reload_projectile,
                                               pace, true);
    }
};
//Tank call - Reload ready
void ATankHUD::_reload_ready()
{
    if (tank_widget)
    {
        if (reload_timer.IsValid())
            GetWorld()->GetTimerManager().ClearTimer(reload_timer);
        tank_widget->_set_projectile_image_ropacity(1.f);
    }
}
//Tank call - Set image opacity
void ATankHUD::_set_pjt_image_opacity(float opacity)
{
    tank_widget->_set_projectile_image_ropacity(opacity);
};
//SHOW
void ATankHUD::_show_reload_projectile()
{
    tank_widget->_set_projectile_image_ropacity(_flicker(4.f) * max_flicker_opacity);
};
//Tank call - Hide
void ATankHUD::_hide_projectile_image()
{
    if (tank_widget)
    {
        tank_widget->_set_projectile_image_ropacity(0.f);
    }
};
//SET ammo
void ATankHUD::_set_ammo_amount(uint8 ammo_toset)
{
    FText ammo = FText::FromString(FString::FromInt(ammo_toset));
    tank_widget->_set_ammo_amount(ammo);
};

// - Lock Buffer - (Aiming)
//Tank call - update
void ATankHUD::_update_lock_buffer(float percent_toset, AimingState aiming_state_toset)
{
    lock_buffer_percent = percent_toset;
    aiming_state = aiming_state_toset;
};
//Tank call - Lock
void ATankHUD::_do_lock_buffer()
{
    if (tank_widget)
    {
        if (lock_buffer_timer.IsValid())
        {
            return;
        }
        tank_widget->_set_lock_buffer_bar_ropacity(100.f);
        GetWorld()->GetTimerManager().SetTimer(lock_buffer_timer, this,
                                               &ATankHUD::_show_lock_buffer,
                                               pace, true);
    }
};
//SHOW
void ATankHUD::_show_lock_buffer()
{
    //Delay Disapear
    static float lag = 0.f;
    if (lock_buffer_percent > 98.f)
    {
        lag += pace * 0.5f;
        tank_widget->_set_lock_buffer_bar_ropacity(1.f - lag);
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
            tank_widget->_set_lock_buffer_bar_fcolor(FLinearColor(0.065f, 0.130f, 0.796f, 0.8f));
        }
        else if (aiming_state == AimingState::locking)
        {
            tank_widget->_set_lock_buffer_bar_fcolor(FLinearColor(0.755f, 0.529f, 0.072f, 0.8f));
        }
        else if (aiming_state == AimingState::overheat)
        {
            if (lock_buffer_percent > 0)
            {
                tank_widget->_set_lock_buffer_bar_fcolor(
                    FLinearColor(0.242f, 0.242f, 0.242f, 0.8f));
            }
            else
            {
                tank_widget->_set_lock_buffer_bar_fcolor(
                    FLinearColor(0.638f, 0.f, 0.005f, 0.8f));
                tank_widget->_set_lock_buffer_bar_percent(-lock_buffer_percent);
                return;
            }
        }
        tank_widget->_set_lock_buffer_bar_percent(lock_buffer_percent);
        lag = 0.f;
    }
};
