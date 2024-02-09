// The DSP team


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DarkRageTypes.h"

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

	FPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh 1P"));
	FPMesh->AttachToComponent(OffsetRoot, FAttachmentTransformRules::KeepRelativeTransform);
	FPMesh->AddLocalOffset(FVector(0.0f, 0.0f, -96.0f));
	FPMesh->AddLocalRotation(FRotator(0.0f, -90.0f, 0.0f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	CameraComponent->AttachToComponent(FPMesh, FAttachmentTransformRules::KeepRelativeTransform, SocketCamera);
	CameraComponent->AddLocalRotation(FRotator(0.0f, 90.0f, 0.0f));
}

void APlayerCharacter::MoveForward(float Value)
{
	if (!FMath::IsNearlyZero(Value, 1e-6f))
	{
		FRotator YawRotator(0.0f, GetControlRotation().Yaw, 0.0f);
		FVector ForwardVector = YawRotator.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardVector, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (!FMath::IsNearlyZero(Value, 1e-6f))
	{
		FRotator YawRotator(0.0f, GetControlRotation().Yaw, 0.0f);
		FVector RightVector = YawRotator.RotateVector(FVector::RightVector);
		AddMovementInput(RightVector, Value);
	}
}

void APlayerCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void APlayerCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}
