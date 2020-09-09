// Fill out your copyright notice in the Description page of Project Settings.

#include "TankHUD.h"
//Include First
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"
#include "SMenu.h"
#include "TankPlayerController.h"
#include "TankWidget.h"
#include "Widgets/SWeakWidget.h"
// #include "GameFramework/HUD.h"
// #include "GameFramework/PlayerController.h"

void ATankHUD::BeginPlay()
{
    Super::BeginPlay();
    FString name = GetName();
    UE_LOG(LogTemp, Warning, TEXT("DONKEY : HUD %s C++ BeginPlay "), *name);
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
        player_controller = Cast<ATankPlayerController>(PlayerOwner);
        player_controller->_setup_projectile();
        tank_widget->AddToViewport();
    }
};

void ATankHUD::_remove_tank_widget()
{
    if (!ensure(tank_widget))
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
    if (tank_widget && tank_widget->_get_crosshair())
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
    if (!ensure(tank_widget))
    {
        return;
    }
    tank_widget->_set_projectile_image_texture(projectile_texture_toset);
};
//Tank call - Reload Image
void ATankHUD::_reload_projectile()
{
    if (ensure(tank_widget && tank_widget->_get_projectile_image()))
    {
        sum_flick = 0.f;
        if (ensure(reload_timer.IsValid()))
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
    if (ensure(tank_widget && tank_widget->_get_projectile_image()))
    {
        GetWorld()->GetTimerManager().ClearTimer(reload_timer);
        tank_widget->_set_projectile_image_ropacity(1.f);
    }
}
//SHOW
void ATankHUD::_show_reload_projectile()
{
    tank_widget->_set_projectile_image_ropacity(_flicker(4.f) * max_flicker_opacity);
};
//Tank call - Hide
void ATankHUD::_hide_projectile_image()
{
    if (ensure(tank_widget && tank_widget->_get_projectile_image()))
    {
        tank_widget->_set_projectile_image_ropacity(0.f);
    }
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
    if (ensure(tank_widget && tank_widget->_get_lock_buffer_bar()))
    {
        if (ensure(lock_buffer_timer.IsValid()))
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
