// The DSP team


#include "Characters/Animations/BaseCharacterAnimInstance.h"
#include "Characters/DRBaseCharacter.h"
#include "Components/CharacterComponents/CharacterEquipmentComponent.h"

void UBaseCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	checkf(TryGetPawnOwner()->IsA<ADRBaseCharacter>(), TEXT("UBaseCharacterAnimInstance::NativeBeginPlay must be used with ADRBaseCharacter"));
	CachedBaseCharacter = StaticCast<ADRBaseCharacter*>(TryGetPawnOwner());
}

void UBaseCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (!CachedBaseCharacter.IsValid())
	{
		return;
	}

	bIsAiming = CachedBaseCharacter->IsAiming();

	const UCharacterEquipmentComponent* CharacterEquipment = CachedBaseCharacter->GetCharacterEquipmentComponent();
	CurrentEquippedItemType = CharacterEquipment->GetCurrentEquippedItemType();
}
