// The DSP team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DRBaseCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAimStateChanged, bool)

class UCharacterAttributesComponent;
class UCharacterEquipmentComponent;
UCLASS(Abstract, NotBlueprintable)
class DARKRAGE_API ADRBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADRBaseCharacter();

	virtual void BeginPlay() override;

	void StartFire();

	void StopFire();

	void StartAiming();

	void StopAiming();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
	void OnStartAiming();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
	void OnStopAiming();

	void Reload();

	void NextItem();

	void PreviousItem();

	void Punch();

	void Menu();

	float GetCurrentMovementSpeed() const;

	USkeletalMeshComponent* GetFirstPersonMesh() const;

	float PlayFPAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate = 1.0f, FName StartSectionName = NAME_None);

	void StopFPAnimMontage(class UAnimMontage* AnimMontage);

	virtual void Falling() override;

	virtual void NotifyJumpApex() override;

	virtual void Landed(const FHitResult& Hit) override;

	const UCharacterAttributesComponent* GetCharacterAttributesComponent() const;

	const UCharacterEquipmentComponent* GetCharacterEquipmentComponent() const;

	UCharacterEquipmentComponent* GetCharacterEquipmentComponent_Mutable() const;

	bool IsAiming() const { return bIsAiming; }

	FOnAimStateChanged OnAimingStateChanged;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Components")
	UCharacterAttributesComponent* CharacterAttributesComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Components")
	UCharacterEquipmentComponent* CharacterEquipmentComponent;

	virtual void OnDeath();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Camera")
	class USkeletalMeshComponent* FPMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character| Animations")
	class UAnimMontage* OnDeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character | Attributes")
	class UCurveFloat* FallDamageCurve;

	virtual void OnStartAimingInternal();

	virtual void OnStopAimingInternal();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Attributes")
	bool bIsAiming = false;

private:
	FVector CurrentFallApex;

	float CurrentAimingMovementSpeed = 0.0f;

	float MaxMovementSpeed = 0.0f;
};
