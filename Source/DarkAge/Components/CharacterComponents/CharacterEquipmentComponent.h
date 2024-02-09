// The DSP team

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DarkRageTypes.h"
#include "CharacterEquipmentComponent.generated.h"


typedef TArray<class AEquipableItem*, TInlineAllocator<(uint32)EEquipmentSlots::MAX>> TItemsArray;
typedef TArray<int32, TInlineAllocator<(uint32)EAmunitionType::MAX>> TAmunitionArray;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCurrentWeaponAmmoChanged, int32, int32)

class ARangeWeaponItem;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DARKAGE_API UCharacterEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	EEquipableItemType GetCurrentEquippedItemType() const;

	ARangeWeaponItem* GetCurrentRangeWeapon() const;

	bool IsEquipping() const;

	void ReloadCurrentWeapon();

	void EquipItemInSlot(EEquipmentSlots Slot);

	void AttachCurrentItemToEquippedSocket();

	void UnEquipCurrentItem();

	void EquipNextItem();

	void EquipPreviousItem();

	FOnCurrentWeaponAmmoChanged OnCurrentWeaponAmmoChangedEvent;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loadout")
	TMap<EAmunitionType, int32> MaxAmunitionAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loadout")
	TMap<EEquipmentSlots, TSubclassOf<class AEquipableItem>> ItemsLoadout;

private:
	TAmunitionArray AmunitionArray;

	TItemsArray ItemsArray;

	void CreateLoadout();

	void EquipAnimationFinished();

	uint32 NextItemsArraySlotIndex(uint32 CurrentSlotIndex);

	uint32 PreviousItemsArraySlotIndex(uint32 CurrentSlotIndex);

	int32 GetAvaliableAmunitionCurrentForWeapon();

	bool bIsEquipping = false;

	UFUNCTION()
	void OnWeaponReloadComplete();

	UFUNCTION()
	void OnCurrentWeaponAmmoChanged(int32 Ammo);

	FDelegateHandle OnCurrentWeaponAmmoChangedHandle;

	FDelegateHandle OnCurrentWeaponReloadedHandle;

	EEquipmentSlots CurrentEquippedSlot;

	AEquipableItem* CurrentEquippedItem;

	ARangeWeaponItem* CurrentEquippedWeapon;

	TWeakObjectPtr<class ADRBaseCharacter> CachedBaseCharacter;

	FTimerHandle EquipTimer;
};
