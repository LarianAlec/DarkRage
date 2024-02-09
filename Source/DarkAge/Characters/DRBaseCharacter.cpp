// The DSP team


#include "DRBaseCharacter.h"
#include "Components/CharacterComponents/CharacterAttributesComponent.h"
#include "GameFramework/CharacterMovementComponent.h"



ADRBaseCharacter::ADRBaseCharacter()
{
	CharacterAttributesComponent = CreateDefaultSubobject<UCharacterAttributesComponent>(TEXT("Character Attributes"));
}

void ADRBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	CharacterAttributesComponent->OnDeathEvent.AddUObject(this, &ADRBaseCharacter::OnDeath);
}


void ADRBaseCharacter::StartFire()
{
	UE_LOG(LogTemp, Warning, TEXT("ADRBaseCharacter::StartFire()"));
}

void ADRBaseCharacter::StopFire()
{
	UE_LOG(LogTemp, Warning, TEXT("ADRBaseCharacter::StopFire()"));
}

void ADRBaseCharacter::Reload()
{
	UE_LOG(LogTemp, Warning, TEXT("ADRBaseCharacter::Reload()"));
}

void ADRBaseCharacter::Punch()
{
	UE_LOG(LogTemp, Warning, TEXT("ADRBaseCharacter::Punch()"));
}

void ADRBaseCharacter::Menu()
{
	UE_LOG(LogTemp, Warning, TEXT("ADRBaseCharacter::Menu()"));
}

const UCharacterAttributesComponent* ADRBaseCharacter::GetCharacterAttributesComponent() const
{
	return CharacterAttributesComponent;
}

void ADRBaseCharacter::OnDeath()
{
	GetCharacterMovement()->DisableMovement();
	
}

