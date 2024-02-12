// The DSP team

#pragma once

#include "CoreMinimal.h"
#include "DRBaseCharacter.h"
#include "PlayerCharacter.generated.h"

class USceneComponent;
UCLASS(Blueprintable)
class DARKAGE_API APlayerCharacter : public ADRBaseCharacter
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();

	USkeletalMeshComponent* GetFirstPersonMesh() const;

	float PlayFPAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate = 1.0f, FName StartSectionName = NAME_None);

	void StopFPAnimMontage(class UAnimMontage* AnimMontage);
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	USceneComponent* FPRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	class USpringArmComponent* MeshRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Camera")
	USceneComponent* OffsetRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Camera")
	class USkeletalMeshComponent* FPMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Camera")
	class UCameraComponent* CameraComponent;

	virtual void OnStartAimingInternal() override;

	virtual void OnStopAimingInternal() override;

};
