// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
//FIRST include
#include "Tank.h"
#include "AimingComponent.h"

void ATankAIController::BeginPlay()
{

    Super::BeginPlay();

    //GET TANK
    tank_controlled = _get_controlled_tank();
    tank_of_player = _get_player_tank();
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // UE_LOG(LogTemp, Warning, TEXT("Ticking"));
    _aiming();
    _fire();
    _reload();
}

//return a Tank pointer
ATank *ATankAIController::_get_controlled_tank() const
{
    return Cast<ATank>(GetPawn());
}

ATank *ATankAIController::_get_player_tank() const
{
    return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::_aiming() const
{
    if (tank_controlled != nullptr && tank_of_player != nullptr)
    {
        //aiming at player's tank
        tank_controlled->aiming_component->_aiming_at(tank_of_player->GetActorLocation());
        return;
    }
    else
    {
        return;
    }
}

//SET weapon number : Change Weapon , projectile number
void ATankAIController::_set_projectile_number(int projectile_number)
{
	tank_controlled->_set_projectile_number(projectile_number);
};

//SET exchange weapon
void ATankAIController::_exchange_projectile()
{
	tank_controlled->_exchange_projectile();
};

//Fire()
void ATankAIController::_fire() //---------	TODO ------------Refact : using Template to Fire with differen projectile number
{
    tank_controlled->_fire();
};

//Reload
void ATankAIController::_reload()
{
    tank_controlled->_reload();
};