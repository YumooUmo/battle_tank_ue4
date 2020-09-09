// Fill out your copyright notice in the Description page of Project Settings.

#include "TankProjectile.h"
//FIRST include
#include "Engine/Texture2DDynamic.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ATankProjectile::ATankProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//SET move_component
	// projectile_movement_component = CreateDefaultSubobject<UProjectileMovementComponent>(FName(TEXT("projectile_movement_component")));
	// projectile_movement_component->bAutoActivate = false;
	UE_LOG(LogTemp, Warning, TEXT("DONKEY : Projectile C++ Construct "));
}

// Called when the game starts or when spawned
void ATankProjectile::BeginPlay()
{
	Super::BeginPlay();
	_set_mass(mass_toset);
	UE_LOG(LogTemp, Warning, TEXT("DONKEY : Projectile C++ BeginPlay "));
}

// Called every frame
void ATankProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//------------------------------------------------------public-----------------------------------------------------------------
// - GET -
//get mass
float ATankProjectile::_get_mass()
{
	if (mass_toset > 0.f)
		return mass_toset;
	return 1.f;
}
//get reload time
float ATankProjectile::_get_reload_time()
{
	return reload_time;
};
//get image
UTexture2D *ATankProjectile::_get_projectile_image()
{
	return projectile_image;
}
//get speed
float ATankProjectile::_get_launch_speed(float launch_force)
{
	if (launch_force_override > 0)
	{
		launch_force = launch_force_override;
	}
	if (mass_toset > 0)
		return launch_force / mass_toset;
	return 10000.f;
};

// - SET -
//set image
void ATankProjectile::_set_projectile_image(UTexture2D *projectile_image_toset)
{
	projectile_image = projectile_image_toset;
};
//set mass
void ATankProjectile::_set_mass(float mass_override)
{
	UPrimitiveComponent *root = Cast<UPrimitiveComponent>(RootComponent);
	if (ensure(root))
	{
		root->SetMassOverrideInKg(NAME_None, mass_override, true);
	}
};

//Launch
void ATankProjectile::_launch(float launch_force)
{
	if (launch_force_override > 0)
	{
		launch_force = launch_force_override;
	}
	UPrimitiveComponent *projectile;
	projectile = Cast<UPrimitiveComponent>(this->GetRootComponent());
	if (this->IsRootComponentMovable())
	{
		// UE_LOG(LogTemp,Error,TEXT("ForwardVector Component of %s is "),*(GetActorForwardVector().ToString()));
		projectile->AddImpulse(GetActorForwardVector() * launch_force);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Potential Error : 1/ Root Component of %s is not moveable. 2/ Root Component is Not a Primitive Component."), *(this->GetName()));
	}
};
