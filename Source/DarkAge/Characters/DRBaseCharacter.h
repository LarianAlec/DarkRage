// The DSP team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DRBaseCharacter.generated.h"


class UCharacterAttributesComponent;
UCLASS(Abstract, NotBlueprintable)
class DARKAGE_API ADRBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADRBaseCharacter();

	virtual void BeginPlay() override;

	virtual void MoveForward(float Value) {};

	virtual void MoveRight(float Value) {};

	virtual void Turn(float Value) {};

	virtual void LookUp(float Value) {};

	void StartFire();

	void StopFire();

	void Reload();

	void Punch();

	void Menu();

	const UCharacterAttributesComponent* GetCharacterAttributesComponent() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Components")
	UCharacterAttributesComponent* CharacterAttributesComponent;

	virtual void OnDeath();


private:

};
