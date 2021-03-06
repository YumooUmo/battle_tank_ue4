// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//last generate
#include "TankProjectile.generated.h"

class URadialForceComponent;
class UParticleSystemComponent;

UCLASS()
class BATTLE_TANK_API ATankProjectile : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	APlayerController *controller = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "StaticMesh")
	UStaticMeshComponent *projectile_mesh = nullptr;

	// - Particles -
	//launch
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Launch")
	UParticleSystemComponent *launch_blast = nullptr;
	//impact
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Hit")
	UParticleSystemComponent *impact_blast = nullptr;

	//hit pawn impact
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Hit")
	UParticleSystemComponent *pawn_blast = nullptr;

	// - Explosion Force -
	//Radius Force
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Hit")
	URadialForceComponent *radial_force = nullptr;

	// - Hit -
	bool bHit = false;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Hit")
	float min_speed_for_damage = 10000.f;

	UFUNCTION()
	void _hit(UPrimitiveComponent *HitComponent,
			  AActor *OtherActor,
			  UPrimitiveComponent *OtherComponent,
			  FVector NormalImpulse,
			  const FHitResult &Hit);

	// - Reload -
	UPROPERTY(EditAnywhere, Category = Reload)
	float reload_time = 2.f;

	// - Mass -
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mass)
	float mass_toset = 100.f;

	// - Launch -
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Launch)
	float launch_force_override = -1.f;

	// - Life Destroy -
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Life)
	float life_span = 5.f;
	uint8 max_life_hit = 200;

	FTimerHandle destroy_timer;

	// - UI -
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = UI)
	class UTexture2D *projectile_image;

public:
	// Sets default values for this actor's properties
	ATankProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//------------------------------------------public---------------------------------------------
	// - Get -
	//mass
	float _get_mass();
	// //ammo
	// uint8 _get_ammo_defaults();
	//launch speed
	float _get_launch_speed(float launch_force);
	//reload time
	float _get_reload_time();
	//UI image
	UTexture2D *_get_projectile_image();

	// - Set -
	UFUNCTION(BlueprintCallable, Category = UI)
	void _set_controller(AController *InController);
	//UI image
	UFUNCTION(BlueprintCallable, Category = UI)
	void _set_projectile_image(UTexture2D *projectile_image_toset);
	//set Mass
	UFUNCTION(BlueprintCallable, Category = Setup)
	void _set_mass(float mass_override);

	// //set ammo
	// UFUNCTION(BlueprintCallable, Category = Setup)
	// void _set_ammo_defaults(uint8 ammo_toset);

	// - Launch -
	virtual void _launch(float launch_force);

	// - Destroy -
	virtual void _take_damage();
};
