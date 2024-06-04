// The DSP team

#pragma once

#include "CoreMinimal.h"
#include "Actors/Equipment/EquipableItem.h"
#include "RangeWeaponItem.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAmmoChanged, int32)
DECLARE_MULTICAST_DELEGATE(FOnReloadCompleted)

UENUM(BlueprintType)
enum class EWeaponFireMode : uint8 
{
	Single,
	FullAuto
};

class UAnimMontage;
class UWeaponBarrelComponent;
UCLASS(Blueprintable)
class DARKRAGE_API ARangeWeaponItem : public AEquipableItem
{
	GENERATED_BODY()
	
public:
	ARangeWeaponItem();

	void StartFire();

	void StopFire();

	void StartAim();

	void StopAim();

	void StartReload();

	void EndReload(bool bIsSuccess);

	void SuccessEndReload();

	int32 GetAmmo() const;

	int32 GetMaxAmmo() const;

	void SetAmmo(int32 NewAmmo);

	EAmunitionType GetAmmoType() const;

	bool CanShoot() const;

	float GetAimFOV() const;

	float GetAimMovementMaxSpeed() const;

	UWeaponBarrelComponent* GetWeaponBarrelComponent_Mutable();

	float GetCurrentBulletSpreadAngle() const;

	UAnimMontage* GetWeaponPunchMontage() const;

	UAnimMontage* GetCharacterPunchMontage() const;

	FOnAmmoChanged OnAmmoChanged;

	FOnReloadCompleted OnReloadComplete;

	USkeletalMeshComponent* GetSkeletalMesh() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWeaponBarrelComponent* WeaponBarrel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations | Weapon")
	UAnimMontage* WeaponFireMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations | Weapon")
	UAnimMontage* WeaponReloadMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations | Weapon")
	UAnimMontage* WeaponPunchMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations | Character")
	UAnimMontage* CharacterFireMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations | Character")
	UAnimMontage* CharacterReloadMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations | Character")
	UAnimMontage* CharacterPunchMontage;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Weapon | Parameters")
	EWeaponFireMode WeaponFireMode = EWeaponFireMode::Single;

	// Rate of fire on rounds per minute
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Weapon | Parameters", meta = (ClampMin = 1.0f, UIMin = 1.0f))
	float RateOfFire = 600.0f;

	// Bullet spread half angle in degrees
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Weapon | Parameters", meta = (ClampMin = 0.0f, UIMin = 0.0f, ClampMax = 5.0f, UIMax = 5.0f))
	float SpreadAngle = 2.0f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Weapon | Parameters | Aiming", meta = (ClampMin = 0.0f, UIMin = 0.0f, ClampMax = 2.0f, UIMax = 2.0f))
	float AimSpreadAngle = 0.25;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Weapon | Parameters | Aiming", meta = (ClampMin = 0.0f, UIMin = 0.0f, ClampMax = 250.0f, UIMax = 250.0f))
	float AimMovementMaxSpeed = 200.0f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Weapon | Parameters | Aiming", meta = (ClampMin = 0.0f, UIMin = 0.0f, ClampMax = 90.0f, UIMax = 90.0f))
	float AimFOV = 60.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Parameters | Ammo", meta = (ClampMin = 1, UIMin = 1))
	EAmunitionType AmmoType = EAmunitionType::None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Parameters | Ammo", meta = (ClampMin = 1, UIMin = 1))
	int32 MaxAmmo = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Parameters | Ammo")
	bool bAutoReload = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Parameters | Ammo", meta = (ClampMin = 0.7f, UIMin = 2.0f))
	float ReloadAnimationPlayRate = 1.0f;

private:
	int32 Ammo = 0;

	bool bIsReloading = false;

	bool bIsFiring = false;

	bool bIsAiming = false;

	void MakeShot();

	void OnShotTimerElapsed();

	float GetShotTimerInterval() const;

	float PlayAnimMontage(UAnimMontage* AnimMontage);

	void StopAnimMontage(UAnimMontage* AnimMontage, float BlendOutTime = 0.0f);

	FTimerHandle ShotTimer;

	FTimerHandle ReloadTimer;
};
