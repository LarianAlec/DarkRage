// The DSP team


#include "Components/CharacterComponents/CharacterAttributesComponent.h"
#include "Characters/DRBaseCharacter.h"


UCharacterAttributesComponent::UCharacterAttributesComponent()
{

}


float UCharacterAttributesComponent::GetHealthPercent() const
{
	return Health / MaxHealth;
}

void UCharacterAttributesComponent::BeginPlay()
{
	Super::BeginPlay();

	checkf(GetOwner()->IsA<ADRBaseCharacter>(), TEXT("UCharacterAttributesComponent::BeginPlay() CharacterAttributesComponent must be used with ADRBaseCharacter"));
	CachedBaseCharacterOwner = StaticCast<ADRBaseCharacter*>(GetOwner());

	Health = MaxHealth;

	CachedBaseCharacterOwner->OnTakeAnyDamage.AddDynamic(this, &UCharacterAttributesComponent::OnTakeAnyDamage);
}

void UCharacterAttributesComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (!IsAlive())
	{
		return;
	}
	
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	UE_LOG(LogDamage, Warning, TEXT("UCharacterAttributesComponent::OnTakeAnyDamage %s recieved %.2f amount of damage from %s. Current Health: %2.f"), *CachedBaseCharacterOwner->GetName(), Damage, *DamageCauser->GetName(), Health);

	if (Health <= 0.0f)
	{
		UE_LOG(LogDamage, Warning, TEXT("UCharacterAttributesComponent::OnTakeAnyDamage character %s is killed by an actor %s"), *DamagedActor->GetName(), *DamageCauser->GetName());
		if (OnDeathEvent.IsBound())
		{
			OnDeathEvent.Broadcast();
		}
	}
}
