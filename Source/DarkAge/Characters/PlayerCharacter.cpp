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

	FPMesh->AttachToComponent(OffsetRoot, FAttachmentTransformRules::KeepRelativeTransform);
	FPMesh->AddLocalOffset(FVector(0.0f, 0.0f, -96.0f));
	FPMesh->AddLocalRotation(FRotator(0.0f, -90.0f, 0.0f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	CameraComponent->AttachToComponent(FPMesh, FAttachmentTransformRules::KeepRelativeTransform, SocketCamera);
	CameraComponent->AddLocalRotation(FRotator(0.0f, 90.0f, 0.0f));
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
