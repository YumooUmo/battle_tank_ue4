// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//last generate
#include "TankProjectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class BATTLE_TANK_API ATankProjectile : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Reload time
	UPROPERTY(EditAnywhere, Category = Setup)
	float reload_time = 2.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = UI)
	class UTexture2D *projectile_image;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Setup)
	float mass_toset = 1.f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Setup)
	float launch_force_override = -1.f;
	
public:
	// Sets default values for this actor's properties
	ATankProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//------------------------------------------public---------------------------------------------
	//Get Mass
	float _get_mass();

	float _get_launch_speed(float launch_force);
	float _get_reload_time();
	UTexture2D *_get_projectile_image();

	//Set
	UFUNCTION(BlueprintCallable, Category = UI)
	void _set_projectile_image(UTexture2D *projectile_image_toset);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void _set_mass(float mass_override);

	//Launch
	virtual void _launch(float launch_force);
};
