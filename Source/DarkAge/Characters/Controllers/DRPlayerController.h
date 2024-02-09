// The DSP team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DRPlayerController.generated.h"

struct FInputActionValue;
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

	virtual void SetupInputComponent() override;

private:
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Jump(const FInputActionValue& Value);

	void Crouch(const FInputActionValue& Value);

	void Sprint(const FInputActionValue& Value);

	void ForceStopSprint(const FInputActionValue& Value);

	void PlayerStartFire(const FInputActionValue& Value);

	void PlayerStopFire(const FInputActionValue& Value);

	void Reload(const FInputActionValue& Value);

	void Punch(const FInputActionValue& Value);

	void Menu(const FInputActionValue& Value);

	TSoftObjectPtr<class ADRBaseCharacter> CachedBaseCharacter;
};
