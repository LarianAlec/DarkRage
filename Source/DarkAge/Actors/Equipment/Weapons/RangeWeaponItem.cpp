// The DSP team


#include "Actors/Equipment/Weapons/RangeWeaponItem.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/Weapon/WeaponBarrelComponent.h"
#include "Characters/DRBaseCharacter.h"
#include "DarkRageTypes.h"

ARangeWeaponItem::ARangeWeaponItem()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Root"));

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(RootComponent);

	WeaponBarrel = CreateDefaultSubobject<UWeaponBarrelComponent>(TEXT("Weapon Barrel"));
	WeaponBarrel->SetupAttachment(WeaponMesh, SocketWeaponMuzzle);

	EquippedSocketName = SocketCharacterWeapon;
}

void ARangeWeaponItem::StartFire()
{
	MakeShot();
	if (WeaponFireMode == EWeaponFireMode::FullAuto)
	{
		GetWorld()->GetTimerManager().ClearTimer(ShotTimer);
		GetWorld()->GetTimerManager().SetTimer(ShotTimer, this, &ARangeWeaponItem::MakeShot, GetShotTimerInterval(), true);
	}
}

void ARangeWeaponItem::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(ShotTimer);
}

void ARangeWeaponItem::StartAim()
{
	bIsAiming = true;
}

void ARangeWeaponItem::StopAim()
{
	bIsAiming = false;
}

void ARangeWeaponItem::StartReload()
{
	checkf(GetOwner()->IsA<ADRBaseCharacter>(), TEXT("ARangeWeaponItem::StartReload() only ADRBaseCharacter can be an owner of a ARangeWeaponItem"))
	ADRBaseCharacter* CharacterOwner = StaticCast<ADRBaseCharacter*>(GetOwner());

	bIsReloading = true;
	if (IsValid(CharacterReloadMontage))
	{
		float MontageDuration = CharacterOwner->PlayFPAnimMontage(CharacterReloadMontage);
		CharacterOwner->PlayAnimMontage(CharacterReloadMontage);
		PlayAnimMontage(WeaponReloadMontage);
		GetWorld()->GetTimerManager().SetTimer(ReloadTimer, [this]() { EndReload(true); }, MontageDuration, false);
	}
	else
	{
		EndReload(true);
	}
}

void ARangeWeaponItem::EndReload(bool bIsSuccess)
{
	if (!bIsReloading)
	{
		return;
	}

	if (!bIsSuccess)
	{
		checkf(GetOwner()->IsA<ADRBaseCharacter>(), TEXT("ARangeWeaponItem::StartReload() only ADRBaseCharacter can be an owner of a ARangeWeaponItem"))
		ADRBaseCharacter* CharacterOwner = StaticCast<ADRBaseCharacter*>(GetOwner());
		CharacterOwner->StopFPAnimMontage(CharacterReloadMontage);
		StopAnimMontage(WeaponReloadMontage);
	}

	GetWorld()->GetTimerManager().ClearTimer(ReloadTimer);

	bIsReloading = false;
	if (bIsSuccess && OnReloadComplete.IsBound())
	{
		OnReloadComplete.Broadcast();
	}
}

int32 ARangeWeaponItem::GetAmmo() const
{
	return Ammo;
}

int32 ARangeWeaponItem::GetMaxAmmo() const
{
	return MaxAmmo;
}

void ARangeWeaponItem::SetAmmo(int32 NewAmmo)
{
	Ammo = NewAmmo;
	if (OnAmmoChanged.IsBound())
	{
		OnAmmoChanged.Broadcast(Ammo);
	}
}

EAmunitionType ARangeWeaponItem::GetAmmoType() const
{
	return AmmoType;
}

bool ARangeWeaponItem::CanShoot() const
{
	return Ammo > 0;
}

float ARangeWeaponItem::GetAimFOV() const
{
	return AimFOV;
}

float ARangeWeaponItem::GetAimMovementMaxSpeed() const
{
	return AimMovementMaxSpeed;
}

void ARangeWeaponItem::BeginPlay()
{
	Super::BeginPlay();
	SetAmmo(MaxAmmo);
}

void ARangeWeaponItem::MakeShot()
{
	checkf(GetOwner()->IsA<ADRBaseCharacter>(), TEXT("ARangeWeaponItem::MakeShot() only ADRBaseCharacter can be an owner of a ARangeWeaponItem"))
	ADRBaseCharacter* CharacterOwner = StaticCast<ADRBaseCharacter*>(GetOwner());

	if (!CanShoot())
	{
		StopFire();
		if (Ammo == 0 && bAutoReload)
		{
			CharacterOwner->Reload();
		}
		return;
	}

	EndReload(false);
	CharacterOwner->PlayFPAnimMontage(CharacterFireMontage);
	PlayAnimMontage(WeaponFireMontage);

	APlayerController* Controller = CharacterOwner->GetController<APlayerController>();
	if (!IsValid(Controller))
	{
		return;
	}

	FVector PlayerViewPoint;
	FRotator PlayerViewRotation;

	Controller->GetPlayerViewPoint(PlayerViewPoint, PlayerViewRotation);

	FVector ViewDirection = PlayerViewRotation.RotateVector(FVector::ForwardVector);

	ViewDirection += GetBulletSpreadOffset(FMath::RandRange(0.0f, GetCurrentBulletSpreadAngle()), PlayerViewRotation);

	SetAmmo(Ammo - 1);
	WeaponBarrel->Shot(PlayerViewPoint, ViewDirection, Controller);
}

float ARangeWeaponItem::GetCurrentBulletSpreadAngle() const
{
	float AngleInDegress = bIsAiming ? AimSpreadAngle : SpreadAngle;
	return FMath::DegreesToRadians(AngleInDegress);
}

FVector ARangeWeaponItem::GetBulletSpreadOffset(float Angle, FRotator ShotRotation)
{
	float SpreadSize = FMath::Tan(Angle);
	float RotationAngle = FMath::RandRange(0.0f, 2 * PI);

	float SpreadY = FMath::Cos(RotationAngle);
	float SpreadZ = FMath::Sin(RotationAngle);

	FVector Result = (ShotRotation.RotateVector(FVector::UpVector) * SpreadZ
		+ ShotRotation.RotateVector(FVector::RightVector) * SpreadY) * SpreadSize;

	return Result;
}

float ARangeWeaponItem::GetShotTimerInterval() const
{
	return 60.0f / RateOfFire;
}

float ARangeWeaponItem::PlayAnimMontage(UAnimMontage* AnimMontage)
{
	UAnimInstance* WeaponAnimInstance = WeaponMesh->GetAnimInstance();
	float Result = 0.0f;
	if (IsValid(WeaponAnimInstance))
	{
		Result = WeaponAnimInstance->Montage_Play(AnimMontage);
	}
	return Result;
}

void ARangeWeaponItem::StopAnimMontage(UAnimMontage* AnimMontage, float BlendOutTime /*= 0.0f*/)
{
	UAnimInstance* WeaponAnimInstance = WeaponMesh->GetAnimInstance();

	if (IsValid(WeaponAnimInstance))
	{
		WeaponAnimInstance->Montage_Stop(BlendOutTime, AnimMontage);
	}
}
