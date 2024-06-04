// The DSP team

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReticleWidget.generated.h"


UCLASS()
class DARKRAGE_API UReticleWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnAimingStateChanged(bool bIsAiming);
};
