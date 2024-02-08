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
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* CrouchAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* SprintAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* ReloadAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* FireAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* PunchAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* MenuAction;


};
