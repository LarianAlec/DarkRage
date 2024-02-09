// The DSP team


#include "DRBaseCharacter.h"



ADRBaseCharacter::ADRBaseCharacter()
{

}

void ADRBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ADRBaseCharacter::Crouch()
{
	UE_LOG(LogTemp, Warning, TEXT("ADRBaseCharacter::Crouch()"))
}

void ADRBaseCharacter::StartFire()
{
	UE_LOG(LogTemp, Warning, TEXT("ADRBaseCharacter::StartFire()"))
}

void ADRBaseCharacter::StopFire()
{
	UE_LOG(LogTemp, Warning, TEXT("ADRBaseCharacter::StopFire()"))
}

void ADRBaseCharacter::Reload()
{
	UE_LOG(LogTemp, Warning, TEXT("ADRBaseCharacter::Reload()"))
}

void ADRBaseCharacter::Punch()
{
	UE_LOG(LogTemp, Warning, TEXT("ADRBaseCharacter::Punch()"))
}

void ADRBaseCharacter::Menu()
{
	UE_LOG(LogTemp, Warning, TEXT("ADRBaseCharacter::Menu()"))
}

