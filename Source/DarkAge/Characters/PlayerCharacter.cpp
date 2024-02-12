// The DSP team


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DarkRageTypes.h"
#include "Actors/Equipment/Weapons/RangeWeaponItem.h"
#include "Components/CharacterComponents/CharacterEquipmentComponent.h"

APlayerCharacter::APlayerCharacter()
{
	FPRoot = CreateDefaultSubobject<USceneComponent>(TEXT("FP Root"));
	FPRoot->SetupAttachment(RootComponent);

	MeshRoot = CreateDefaultSubobject<USpringArmComponent>(TEXT("Mesh Root"));
	MeshRoot->AttachToComponent(FPRoot, FAttachmentTransformRules::KeepRelativeTransform);
	MeshRoot->AddLocalOffset(FVector(0.0f, 0.0f, 60.0f));
	MeshRoot->bUsePawnControlRotation = true;
	MeshRoot->bInheritRoll = false;
	MeshRoot->bDoCollisionTest = false;
	MeshRoot->TargetArmLength = 0.0f;

	OffsetRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Offset Root"));
	OffsetRoot->AttachToComponent(MeshRoot, FAttachmentTransformRules::KeepRelativeTransform);
	OffsetRoot->AddLocalOffset(FVector(0.0f, 0.0f, -60.0f));

	FPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));
	FPMesh->AttachToComponent(OffsetRoot, FAttachmentTransformRules::KeepRelativeTransform);
	FPMesh->AddLocalOffset(FVector(0.0f, 0.0f, -96.0f));
	FPMesh->AddLocalRotation(FRotator(0.0f, -90.0f, 0.0f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	CameraComponent->AttachToComponent(FPMesh, FAttachmentTransformRules::KeepRelativeTransform, SocketCamera);
	CameraComponent->AddLocalRotation(FRotator(0.0f, 90.0f, 0.0f));
}

USkeletalMeshComponent* APlayerCharacter::GetFirstPersonMesh() const
{
	return FPMesh;
}

float APlayerCharacter::PlayFPAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate, FName StartSectionName)
{
	UAnimInstance* AnimInstance = (IsValid(FPMesh)) ? FPMesh->GetAnimInstance() : nullptr;
	if (AnimMontage && AnimInstance)
	{
		float const Duration = AnimInstance->Montage_Play(AnimMontage, InPlayRate);

		if (Duration > 0.f)
		{
			// Start at a given Section.
			if (StartSectionName != NAME_None)
			{
				AnimInstance->Montage_JumpToSection(StartSectionName, AnimMontage);
			}

			return Duration;
		}
	}

	return 0.f;
}

void APlayerCharacter::StopFPAnimMontage(class UAnimMontage* AnimMontage)
{
	{
		UAnimInstance* AnimInstance = (IsValid(FPMesh)) ? FPMesh->GetAnimInstance() : nullptr;
		UAnimMontage* MontageToStop = (AnimMontage) ? AnimMontage : GetCurrentMontage();
		bool bShouldStopMontage = AnimInstance && MontageToStop && !AnimInstance->Montage_GetIsStopped(MontageToStop);

		if (bShouldStopMontage)
		{
			AnimInstance->Montage_Stop(MontageToStop->BlendOut.GetBlendTime(), MontageToStop);
		}
	}
}

void APlayerCharacter::OnStartAimingInternal()
{
	Super::OnStartAimingInternal();
	APlayerController* PlayerController = GetController<APlayerController>();
	if (!IsValid(PlayerController))
	{
		return;
	}

	APlayerCameraManager* CameraManager = PlayerController->PlayerCameraManager;
	if (IsValid(CameraManager))
	{
		ARangeWeaponItem* CurrentRangeWeapon = GetCharacterEquipmentComponent()->GetCurrentRangeWeapon();
		CameraManager->SetFOV(CurrentRangeWeapon->GetAimFOV());
	}
}

void APlayerCharacter::OnStopAimingInternal()
{
	Super::OnStopAimingInternal();
	APlayerController* PlayerController = GetController<APlayerController>();
	if (!IsValid(PlayerController))
	{
		return;
	}

	APlayerCameraManager* CameraManager = PlayerController->PlayerCameraManager;
	if (IsValid(CameraManager))
	{
		ARangeWeaponItem* CurrentRangeWeapon = GetCharacterEquipmentComponent()->GetCurrentRangeWeapon();
		CameraManager->UnlockFOV();
	}
}
