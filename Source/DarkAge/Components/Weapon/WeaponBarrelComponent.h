// The DSP team

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WeaponBarrelComponent.generated.h"

USTRUCT(BlueprintType)
struct FDecalInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Decal info")
	UMaterialInterface* DecalMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Decal info")
	FVector DecalSize = FVector(5.0f, 5.0f, 5.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Decal info")
	float DecalLifeTime = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Decal info")
	float DecalFadeOutTime = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Decal info")
	float DecalFadeScreenSize = 0.001f;
};

class UNiagaraSystem;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DARKAGE_API UWeaponBarrelComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	void Shot(FVector ShotStart, FVector ShotDirection, AController* Controller);
		
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Barrel attributes")
	float FiringRange = 5000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Barrel attributes | Damage")
	float DamageAmount = 20.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Barrel attributes | VFX")
	UNiagaraSystem* MuzzleFlashFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Barrel attributes | VFX")
	UNiagaraSystem* TraceFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Barrel attributes | Decals")
	FDecalInfo DefaultDecalInfo;
		
};
