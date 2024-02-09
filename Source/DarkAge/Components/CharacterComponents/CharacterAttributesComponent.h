// The DSP team

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterAttributesComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeathEventSignature)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DARKAGE_API UCharacterAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCharacterAttributesComponent();

	FOnDeathEventSignature OnDeathEvent;

	bool IsAlive() { return Health > 0; };

	float GetHealthPercent() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health", meta = (UIMin = 0.0f))
	float MaxHealth = 100.0f;

private:
	float Health = 0.0f;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	TWeakObjectPtr<class ADRBaseCharacter> CachedBaseCharacterOwner;
};
