// The DSP team


#include "UI/PlayerHUDWidget.h"
#include "ReticleWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Characters/DRBaseCharacter.h"
#include "Components/CharacterComponents/CharacterAttributesComponent.h"
#include "AmmoWidget.h"

class UReticleWidget* UPlayerHUDWidget::GetReticleWidget()
{
	return WidgetTree->FindWidget<UReticleWidget>(ReticleWidgetName);
}

class UAmmoWidget* UPlayerHUDWidget::GetAmmoWidget()
{
	return WidgetTree->FindWidget<UAmmoWidget>(AmmoWidgetName);
}

float UPlayerHUDWidget::GetHealthPercent() const
{
	float Result = 1.0f;

	APawn* Pawn = GetOwningPlayerPawn();
	ADRBaseCharacter* Character = Cast<ADRBaseCharacter>(Pawn);
	if (IsValid(Character))
	{
		const UCharacterAttributesComponent* CharacterAttributes = Character->GetCharacterAttributesComponent();
		Result = CharacterAttributes->GetHealthPercent();
	}
	return Result;
}
