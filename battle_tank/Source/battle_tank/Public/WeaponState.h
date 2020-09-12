#pragma once

UENUM()
enum class WeaponState : uint8
{
	empty,
	reloading,
	ready,
	out_of_ammo
};