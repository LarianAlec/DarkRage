// The DSP team

#pragma once

#include "CoreMinimal.h"
#include "DRBaseCharacter.h"
#include "PlayerCharacter.generated.h"


UCLASS(Blueprintable)
class DARKAGE_API APlayerCharacter : public ADRBaseCharacter
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();

	virtual void MoveForward(float Value) override;
	virtual void MoveRight(float Value) override;
	virtual void Turn(float Value) override;
	virtual void LookUp(float Value) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Camera")
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Camera")
	class USpringArmComponent* SpringArmComponent;
};
