#pragma once
#include "../../../../../../../Source/Runtime/Core/Public/UObject/NameTypes.h"

#define ECC_Bullet ECC_GameTraceChannel1

const FName FXParamTraceEnd = FName("TraceEnd");

const FName SocketCamera = FName("camera");

const FName SocketCharacterWeapon = FName("GripPoint");
const FName SocketWeaponMuzzle = FName("MuzzleSocket");

UENUM(BlueprintType)
enum class EEquipableItemType : uint8 
{
	None,
	Crossbow,
	Bow,
};

UENUM(BlueprintType)
enum class EAmunitionType : uint8
{
	None, 
	Bolts,
	Arrows,
	MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EEquipmentSlots : uint8
{
	None,
	PrimaryWeapon,
	SecondaryWeapon,
	MAX UMETA(Hidden)
};