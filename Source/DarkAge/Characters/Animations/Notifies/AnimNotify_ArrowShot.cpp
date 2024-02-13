// The DSP team


#include "Characters/Animations/Notifies/AnimNotify_ArrowShot.h"
#include "Characters/DRBaseCharacter.h"
#include "Actors/Equipment/Weapons/RangeWeaponItem.h"
#include "Components/CharacterComponents/CharacterEquipmentComponent.h"
#include "Components/Weapon/WeaponBarrelComponent.h"

void UAnimNotify_ArrowShot::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ARangeWeaponItem* RangeWeapon = Cast<ARangeWeaponItem>(MeshComp->GetOwner());
	ADRBaseCharacter* CachedBaseCharacter = Cast<ADRBaseCharacter>(RangeWeapon->GetOwner());
	if (!IsValid(CachedBaseCharacter))
	{
		return;
	}

	APlayerController* Controller = CachedBaseCharacter->GetController<APlayerController>();
	if (!IsValid(Controller))
	{
		return;
	}

	const UCharacterEquipmentComponent* EquipmentComponent = CachedBaseCharacter->GetCharacterEquipmentComponent();

	FVector PlayerViewPoint;
	FRotator PlayerViewRotation;

	Controller->GetPlayerViewPoint(PlayerViewPoint, PlayerViewRotation);

	FVector ViewDirection = PlayerViewRotation.RotateVector(FVector::ForwardVector);

	RangeWeapon->GetWeaponBarrelComponent_Mutable()->Shot(PlayerViewPoint, ViewDirection, Controller, RangeWeapon->GetCurrentBulletSpreadAngle());
}