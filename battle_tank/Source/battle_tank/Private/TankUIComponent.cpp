// Fill out your copyright notice in the Description page of Project Settings.

#include "TankUIComponent.h"
//include first
#include "Blueprint/UserWidget.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
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
// - Setup -
//BP -
void UTankUIComponent::_setup(TSubclassOf<UTankWidget> tank_widget_Subclass_toset)
{
	if (owner_tank == nullptr)
	{
		return;
	}
	tank_widget_Subclass = tank_widget_Subclass_toset;
};
//Cpp -
UTankWidget *UTankUIComponent::_initialize_widget()
{
	owner_tank = Cast<ATank>(GetOwner());
	tank_widget = CreateWidget<UTankWidget>(GetWorld(), tank_widget_Subclass);

	_setup_lock_buffer(owner_tank->_get_max_lock_buffer());
	_setup_projectile(owner_tank->_get_reload_time(), owner_tank->_get_projectile_image());

	return tank_widget;
};
//Get
UTankWidget *UTankUIComponent::_get_widget()
{
	return tank_widget;
};
//Free
void UTankUIComponent::_free_tank_widget()
{
	tank_widget = nullptr;
};

/* - Draw - 
 * 
 */
// - Turning -
//CALL:Show Aiming Box
void UTankUIComponent::_show_aiming_box(bool flag)
{
	if (tank_widget == nullptr)
	{
		return;
	}
	tank_widget->_show_aiming_box(flag);
}

// - Weapon - (Projectile)
//CALL : change projectile image
void UTankUIComponent::_setup_projectile(float reload_time_toset, UTexture2D *projectile_texture_toset)
{
	if (tank_widget == nullptr)
	{
		return;
	}
	tank_widget->_setup_projectile(reload_time_toset, projectile_texture_toset);
};
//CALL : Reload Image
void UTankUIComponent::_reload_projectile()
{
	if (tank_widget == nullptr)
	{
		return;
	}
	tank_widget->_reload_projectile();
};
//CALL : Hide Image
void UTankUIComponent::_fire()
{
	if (tank_widget == nullptr)
	{
		return;
	}
	tank_widget->_hide_projectile_image();
}

// - LOCK - (Aiming)
//CALL : Setup lock buffer
void UTankUIComponent::_setup_lock_buffer(float max_buffer_toset)
{
	if (tank_widget == nullptr)
	{
		return;
	}
	tank_widget->_setup_lock_buffer(max_buffer_toset);
}
//CALL : update
void UTankUIComponent::_update_lock_buffer(float lock_buffer_toset, AimingState aiming_state_toset)
{
	if (tank_widget == nullptr)
	{
		return;
	}
	tank_widget->_update_lock_buffer(lock_buffer_toset, aiming_state_toset);
};
//CALL : _Lock draw
void UTankUIComponent::_do_lock_buffer()
{
	if (tank_widget == nullptr)
	{
		return;
	}
	tank_widget->_do_lock_buffer();
};

//Draw : Projectile path
void UTankUIComponent::_draw_projectile_path()
{
	if (owner_tank == nullptr)
	{
		return;
	}
	//Initiallize Parameters to _predict path method()
	FVector launch_velocity = (owner_tank->_get_launch_normal()) * (owner_tank->_get_launch_speed());
	FVector launch_location = owner_tank->_get_launch_location();

	FPredictProjectilePathParams PredictParams{
		10.f,			 //CollisionRadius
		launch_location, //start location
		launch_velocity, //----------------- get owner->barrel aiming velocity : launch_velocity
		3.0f,			 //MaxSimTime
		ECollisionChannel::ECC_Visibility,
		nullptr}; //													####	TODO : Debug
	PredictParams.ActorsToIgnore.Add(owner_tank);
	// PredictParams.OverrideGravityZ = -5000.f;

	//Initiallize Result Struct to _predict path method()
	FPredictProjectilePathResult PredictResult;

	if (UGameplayStatics::PredictProjectilePath(
			this,
			PredictParams,
			PredictResult))
	{
		//----####有效射程	in MaxSimTime
		//获得第一个击中点
		//---------------------------------------------------------Debug
		DrawDebugLine(
			GetWorld(),
			launch_location, //start location
			PredictResult.HitResult.Location,
			FColor::Blue,
			false,
			0.0f,
			0.0f,
			100.0f);
	}
	else
	{
		//-----####有效射程外 out of MaxSimTime
		//---------------------------------------------------------Debug
		DrawDebugLine(
			GetWorld(),
			launch_location, //start location
			PredictResult.LastTraceDestination.Location,
			FColor::Blue,
			false,
			0.0f,
			0.0f,
			100.0f);
	}
	// //------------------------------------Debug
	// UE_LOG(LogTemp, Error, TEXT("Hit Result is : %s"), *(PredictResult.HitResult.Location.ToString()));
	// UE_LOG(LogTemp, Error, TEXT("Last Trace Destnation is : %s"), *(PredictResult.LastTraceDestination.Location.ToString()));
	// UE_LOG(LogTemp, Error, TEXT("Barrel location is : %s"), *(owner->barrel->GetSocketLocation(FName(TEXT("launch_socket"))).ToString()));
}
