// The DSP team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DRPlayerController.generated.h"

struct FInputActionValue;
//class UPlayerHUDWidget;
UCLASS()
class DARKAGE_API ADRPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void SetPawn(APawn* InPawn) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UDRCharacterInputConfig* InputActions;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "Widgets")
	//TSubclassOf<UPlayerHUDWidget> PlayerHudWidgetClass;

	virtual void SetupInputComponent() override;

private:
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Jump(const FInputActionValue& Value);

	void PlayerStartFire(const FInputActionValue& Value);

	void PlayerStopFire(const FInputActionValue& Value);

	void StartAiming(const FInputActionValue& Value);

	void StopAiming(const FInputActionValue& Value);

	void Reload(const FInputActionValue& Value);

	void EquipNextItem(const FInputActionValue& Value);

	void EquipPreviousItem(const FInputActionValue& Value);

	TSoftObjectPtr<class ADRBaseCharacter> CachedBaseCharacter;

	void CreateAndInitializeWidgets();

	//UPlayerHudWidget* PlayerHudWidget = nullptr;
};
