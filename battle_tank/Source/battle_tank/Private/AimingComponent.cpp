// Fill out your copyright notice in the Description page of Project Settings.

#include "AimingComponent.h"
//FIRST include
#include "Tank.h"
#include "TankUIComponent.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}

// Called when the game starts
void UAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

// Called every frame
void UAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(GetWorld()->DeltaTimeSeconds, TickType, ThisTickFunction);
	// ...
}

//-----------------------------------		private		---------------------------------

//-----------------------------------		public		---------------------------------
void UAimingComponent::_setup_UI_component(UTankUIComponent *UI_component_toset)
{
	UI_component = UI_component_toset;
}

//-----------------------------------		Lock Action		---------------------------------
void UAimingComponent::_should_lock()
{
	//Draw_Path : Pressed
	if (aiming_state == AimingState::locking)
	{
		if (lock_buffer <= 0.f)
		{
			lock_buffer = -overheat_lag;
			aiming_state = AimingState::overheat;
		}
		else
		{
			lock_buffer -= pace;
			UI_component->_draw_projectile_path();
		}
	}
	//Draw_Path : Not Pressed
	else
	{
		if (lock_buffer < max_buffer)
		{
			lock_buffer += pace * cool_rate;
			if (aiming_state == AimingState::overheat && lock_buffer > recover_value)
			{
				aiming_state = AimingState::usable;
			}
			//limit
			if (lock_buffer > max_buffer)
			{
				lock_buffer = max_buffer;
				GetWorld()->GetTimerManager().ClearTimer(lock_timer);
			}
		}
	}
	UI_component->_update_lock_buffer(lock_buffer, aiming_state);
};

//CALL
void UAimingComponent::_lock(bool flag)
{
	//Draw_Path : Pressed
	if (aiming_state != AimingState::overheat)
	{
		if (flag)
		{
			aiming_state = AimingState::locking;
			if (lock_timer.IsValid())
			{
				return;
			}
			UI_component->_do_lock_buffer();
			GetWorld()->GetTimerManager().SetTimer(lock_timer, this,
													&UAimingComponent::_should_lock,
													pace, true);
		}
		//Draw_Path : Released
		else
		{
			aiming_state = AimingState::usable;
		}
	}
};
