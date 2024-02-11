// The DSP team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UI/PlayerHUDWidget.h"
#include "DRPlayerController.generated.h"

struct FInputActionValue;
class UPlayerHUDWidget;
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "Widgets")
	TSubclassOf<UPlayerHUDWidget> PlayerHUDWidgetClass;

	virtual void SetupInputComponent() override;

private:
	void PlayerStartFire(const FInputActionValue& Value);

	void PlayerStopFire(const FInputActionValue& Value);

	void StartAiming(const FInputActionValue& Value);

	void StopAiming(const FInputActionValue& Value);

	void Reload(const FInputActionValue& Value);

	void EquipNextItem(const FInputActionValue& Value);

	void EquipPreviousItem(const FInputActionValue& Value);

	TSoftObjectPtr<class ADRBaseCharacter> CachedBaseCharacter;

	void CreateAndInitializeWidgets();

	UPlayerHUDWidget* PlayerHUDWidget = nullptr;
};
