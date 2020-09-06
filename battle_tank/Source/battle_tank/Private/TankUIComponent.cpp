// Fill out your copyright notice in the Description page of Project Settings.

#include "TankUIComponent.h"
#include "Blueprint/UserWidget.h"
#include "TankHUD.h"
#include "TankWidget.h"

// Sets default values for this component's properties
UTankUIComponent::UTankUIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UTankUIComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
}

// Called every frame
void UTankUIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//Setup
void UTankUIComponent::_setup_widget(TSubclassOf<UTankWidget> tank_widget_Subclass_toset)
{
	tank_widget_Subclass = tank_widget_Subclass_toset;
	tank_HUD = Cast<ATankHUD>(Cast<APlayerController>(Cast<APawn>(GetOwner())->GetController())->GetHUD());
};

//Set
void UTankUIComponent::_set_widget()
{
	tank_widget = CreateWidget<UTankWidget>(GetWorld(), tank_widget_Subclass);
	tank_HUD->_set_current_widget(tank_widget);
};
//Unset
void UTankUIComponent::_unset_widget()
{
	if (tank_widget == nullptr)
	{
		return;
	}
	tank_HUD->_set_current_widget(nullptr);
	delete tank_widget;
};

/* - Draw - 
 * 
 */
//CALL:Show Aiming Box
void UTankUIComponent::_show_aiming_box(bool flag)
{
	tank_widget->_show_aiming_box(flag);
}

//CALL : change projectile image
void UTankUIComponent::_setup_projectile(float reload_time_toset, UTexture2D *projectile_texture_toset)
{
	tank_widget->_setup_projectile(reload_time_toset, projectile_texture_toset);
};
//CALL : Reload Image
void UTankUIComponent::_reload_projectile()
{
	tank_widget->_reload_projectile();
};

//CALL : Setup lock buffer
void UTankUIComponent::_setup_lock_buffer(float max_buffer_toset)
{
	tank_widget->_setup_lock_buffer(max_buffer_toset);
}
//CALL : update
void UTankUIComponent::_update_lock_buffer(float lock_buffer_toset, AimingState aiming_state_toset)
{
	tank_widget->_update_lock_buffer(lock_buffer_toset, aiming_state_toset);
};
//CALL : _Lock draw
void UTankUIComponent::_do_lock_buffer()
{
	tank_widget->_do_lock_buffer();
};