// The DSP team

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DarkRageTypes.h"
#include "BaseCharacterAnimInstance.generated.h"


UCLASS()
class DARKRAGE_API UBaseCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character animation");
	EEquipableItemType CurrentEquippedItemType = EEquipableItemType::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character animation | Weapon")
	bool bIsAiming = false;

private:
	TWeakObjectPtr<class ADRBaseCharacter> CachedBaseCharacter;
};
