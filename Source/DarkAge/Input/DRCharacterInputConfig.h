// The DSP team

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DRCharacterInputConfig.generated.h"

class UInputAction;
UCLASS()
class DARKAGE_API UDRCharacterInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* FireAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* AimAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* ReloadAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* EquipNextItemAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* EquipPreviousItemAction;
};
