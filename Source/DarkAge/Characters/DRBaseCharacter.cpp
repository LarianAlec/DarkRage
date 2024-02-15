// The DSP team


#include "DRBaseCharacter.h"
#include "Components/CharacterComponents/CharacterAttributesComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CharacterComponents/CharacterEquipmentComponent.h"
#include "Actors/Equipment/Weapons/RangeWeaponItem.h"
#include "Engine/DamageEvents.h"
#include "Engine/HitResult.h"
#include "GameFramework/Actor.h"
#include "Animation/AnimMontage.h"


ADRBaseCharacter::ADRBaseCharacter()
{
	CharacterAttributesComponent = CreateDefaultSubobject<UCharacterAttributesComponent>(TEXT("Character Attributes"));
	CharacterEquipmentComponent = CreateDefaultSubobject<UCharacterEquipmentComponent>(TEXT("Character Equipment"));
	FPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));
	FPMesh->SetupAttachment(RootComponent);
	MaxMovementSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

void ADRBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	CharacterAttributesComponent->OnDeathEvent.AddUObject(this, &ADRBaseCharacter::OnDeath);
}


void ADRBaseCharacter::StartFire()
{
	if (CharacterEquipmentComponent->IsEquipping())
	{
		return;
	}
	ARangeWeaponItem* CurrentRangeWeapon = CharacterEquipmentComponent->GetCurrentRangeWeapon();
	if (IsValid(CurrentRangeWeapon))
	{
		CurrentRangeWeapon->StartFire();
	}
}

void ADRBaseCharacter::StopFire()
{
	ARangeWeaponItem* CurrentRangeWeapon = CharacterEquipmentComponent->GetCurrentRangeWeapon();
	if (IsValid(CurrentRangeWeapon))
	{
		CurrentRangeWeapon->StopFire();
	}
}

void ADRBaseCharacter::StartAiming()
{
	ARangeWeaponItem* CurrentRangeWeapon = GetCharacterEquipmentComponent()->GetCurrentRangeWeapon();
	if (!IsValid(CurrentRangeWeapon))
	{
		return;
	}

	bIsAiming = true;
	CurrentAimingMovementSpeed = CurrentRangeWeapon->GetAimMovementMaxSpeed();

	GetCharacterMovement()->MaxWalkSpeed = CurrentAimingMovementSpeed;
	CurrentRangeWeapon->StartAim();
	OnStartAiming();
}

void ADRBaseCharacter::StopAiming()
{
	if (!bIsAiming)
	{
		return;
	}

	ARangeWeaponItem* CurrentRangeWeapon = GetCharacterEquipmentComponent()->GetCurrentRangeWeapon();
	if (IsValid(CurrentRangeWeapon))
	{
		CurrentRangeWeapon->StopAim();
	}

	GetCharacterMovement()->MaxWalkSpeed = MaxMovementSpeed;
	bIsAiming = false;
	CurrentAimingMovementSpeed = 0.0f;

	OnStopAiming();
}

void ADRBaseCharacter::OnStartAiming_Implementation()
{
	OnStartAimingInternal();
}

void ADRBaseCharacter::OnStopAiming_Implementation()
{
	OnStopAimingInternal();
}

void ADRBaseCharacter::Reload()
{
	if (IsValid(CharacterEquipmentComponent->GetCurrentRangeWeapon()))
	{
		CharacterEquipmentComponent->ReloadCurrentWeapon();
	}
}

void ADRBaseCharacter::NextItem()
{
	CharacterEquipmentComponent->EquipNextItem();
}

void ADRBaseCharacter::PreviousItem()
{
	CharacterEquipmentComponent->EquipPreviousItem();
}

void ADRBaseCharacter::Punch()
{
	UE_LOG(LogTemp, Warning, TEXT("ADRBaseCharacter::Punch()"));
}

void ADRBaseCharacter::Menu()
{
	UE_LOG(LogTemp, Warning, TEXT("ADRBaseCharacter::Menu()"));
}

float ADRBaseCharacter::GetCurrentMovementSpeed() const
{
	return CurrentAimingMovementSpeed;
}

USkeletalMeshComponent* ADRBaseCharacter::GetFirstPersonMesh() const
{
	return FPMesh;
}

float ADRBaseCharacter::PlayFPAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate, FName StartSectionName)
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

void ADRBaseCharacter::StopFPAnimMontage(class UAnimMontage* AnimMontage)
{
	UAnimInstance* AnimInstance = (IsValid(FPMesh)) ? FPMesh->GetAnimInstance() : nullptr;
	UAnimMontage* MontageToStop = (AnimMontage) ? AnimMontage : GetCurrentMontage();
	bool bShouldStopMontage = AnimInstance && MontageToStop && !AnimInstance->Montage_GetIsStopped(MontageToStop);

	if (bShouldStopMontage)
	{
		AnimInstance->Montage_Stop(MontageToStop->BlendOut.GetBlendTime(), MontageToStop);
	}
}

void ADRBaseCharacter::Falling()
{
	this->GetCharacterMovement()->bNotifyApex = true;
}

void ADRBaseCharacter::NotifyJumpApex()
{
	Super::NotifyJumpApex();
	CurrentFallApex = GetActorLocation();
}

void ADRBaseCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	float FallHeight = (CurrentFallApex - GetActorLocation()).Z * 0.01f;
	if (IsValid(FallDamageCurve))
	{
		float DamageAmount = FallDamageCurve->GetFloatValue(FallHeight);
		AActor* SelfPointer = Cast<AActor>(this);
		TakeDamage(DamageAmount, FDamageEvent(), GetController(), SelfPointer);
	}
}

const UCharacterAttributesComponent* ADRBaseCharacter::GetCharacterAttributesComponent() const
{
	return CharacterAttributesComponent;
}

const UCharacterEquipmentComponent* ADRBaseCharacter::GetCharacterEquipmentComponent() const
{
	return CharacterEquipmentComponent;
}

UCharacterEquipmentComponent* ADRBaseCharacter::GetCharacterEquipmentComponent_Mutable() const
{
	return CharacterEquipmentComponent;
}

void ADRBaseCharacter::OnDeath()
{
	GetCharacterMovement()->DisableMovement();
	float Duration = PlayAnimMontage(OnDeathAnimMontage);

}

void ADRBaseCharacter::OnStartAimingInternal()
{
	if (OnAimingStateChanged.IsBound())
	{
		OnAimingStateChanged.Broadcast(true);
	}
}

void ADRBaseCharacter::OnStopAimingInternal()
{
	if (OnAimingStateChanged.IsBound())
	{
		OnAimingStateChanged.Broadcast(false);
	}
}

