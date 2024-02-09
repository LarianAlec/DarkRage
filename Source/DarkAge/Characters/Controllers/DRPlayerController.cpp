// The DSP team


#include "DRPlayerController.h"
#include "Characters/DRBaseCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Input/DRCharacterInputConfig.h"
#include "EnhancedInputComponent.h"


void ADRPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	CachedBaseCharacter = Cast<ADRBaseCharacter>(InPawn);

}

void ADRPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (APlayerController* PlayerController = Cast<APlayerController>(this))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			checkf(IsValid(InputMapping), TEXT("ADRPlayerController::SetupInputComponent InputMapping must be valid!"));
			checkf(IsValid(InputActions), TEXT("ADRPlayerController::SetupInputComponent InputMapping must be valid!"));

			Subsystem->AddMappingContext(InputMapping, 0);

			UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

			EnhancedInputComponent->BindAction(InputActions->FireAction, ETriggerEvent::Started, this, &ADRPlayerController::PlayerStartFire);
			EnhancedInputComponent->BindAction(InputActions->FireAction, ETriggerEvent::Completed, this, &ADRPlayerController::PlayerStopFire);
			EnhancedInputComponent->BindAction(InputActions->AimAction, ETriggerEvent::Started, this, &ADRPlayerController::StartAiming);
			EnhancedInputComponent->BindAction(InputActions->AimAction, ETriggerEvent::Completed, this, &ADRPlayerController::StopAiming);
			EnhancedInputComponent->BindAction(InputActions->ReloadAction, ETriggerEvent::Started, this, &ADRPlayerController::Reload);
			EnhancedInputComponent->BindAction(InputActions->EquipNextItemAction, ETriggerEvent::Triggered, this, &ADRPlayerController::EquipNextItem);
			EnhancedInputComponent->BindAction(InputActions->EquipPreviousItemAction, ETriggerEvent::Triggered, this, &ADRPlayerController::EquipPreviousItem);
		}
	}
}


void ADRPlayerController::PlayerStartFire(const FInputActionValue& Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->StartFire();
	}
}

void ADRPlayerController::PlayerStopFire(const FInputActionValue& Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->StopFire();
	}
}

void ADRPlayerController::StartAiming(const FInputActionValue& Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->StartAiming();
	}
}

void ADRPlayerController::StopAiming(const FInputActionValue& Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->StopAiming();
	}
}

void ADRPlayerController::Reload(const FInputActionValue& Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->Reload();
	}
}

void ADRPlayerController::EquipNextItem(const FInputActionValue& Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->NextItem();
	}
}

void ADRPlayerController::EquipPreviousItem(const FInputActionValue& Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->PreviousItem();
	}
}

void ADRPlayerController::CreateAndInitializeWidgets()
{

}
