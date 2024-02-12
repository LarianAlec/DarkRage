// The DSP team


#include "Components/Weapon/WeaponBarrelComponent.h"
#include "DarkRageTypes.h"
#include "Engine/World.h"
#include "Engine/DamageEvents.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "Engine/DamageEvents.h"


void UWeaponBarrelComponent::Shot(FVector ShotStart, FVector ShotDirection, AController* Controller)
{
	FVector MuzzleLocation = GetComponentLocation();
	FVector ShotEnd = ShotStart + FiringRange * ShotDirection;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), MuzzleFlashFX, MuzzleLocation, GetComponentRotation());

	FHitResult ShotResult;
	if (GetWorld()->LineTraceSingleByChannel(ShotResult, ShotStart, ShotEnd, ECC_Bullet))
	{
		ShotEnd = ShotResult.ImpactPoint;
		AActor* HitActor = ShotResult.GetActor();
		if (IsValid(HitActor))
		{
			//HitActor->TakeDamage(DamageAmount, FDamageEvent{}, Controller, GetOwner());
			FPointDamageEvent PointDamageEvent = FPointDamageEvent(DamageAmount, ShotResult, ShotDirection, nullptr);
			HitActor->TakeDamage(DamageAmount, PointDamageEvent, Controller, GetOwner());
		}

		//DrawDebugSphere(GetWorld(), ShotEnd, 10.0f, 24, FColor::Red, false, 1.0f);
		UDecalComponent* DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DefaultDecalInfo.DecalMaterial, DefaultDecalInfo.DecalSize, ShotResult.ImpactPoint, ShotResult.ImpactNormal.ToOrientationRotator());
		if (IsValid(DecalComponent))
		{
			DecalComponent->SetFadeOut(DefaultDecalInfo.DecalLifeTime, DefaultDecalInfo.DecalFadeOutTime);
			DecalComponent->SetFadeScreenSize(DefaultDecalInfo.DecalFadeScreenSize);
		}
	}

	UNiagaraComponent* TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, MuzzleLocation, GetComponentRotation());
	TraceFXComponent->SetVectorParameter(FXParamTraceEnd, ShotEnd);

}

