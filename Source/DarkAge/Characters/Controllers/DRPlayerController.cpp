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

			EnhancedInputComponent->BindAction(InputActions->MoveAction, ETriggerEvent::Triggered, this, &ADRPlayerController::Move);
			EnhancedInputComponent->BindAction(InputActions->LookAction, ETriggerEvent::Triggered, this, &ADRPlayerController::Look);
			EnhancedInputComponent->BindAction(InputActions->JumpAction, ETriggerEvent::Started, this, &ADRPlayerController::Jump);
			EnhancedInputComponent->BindAction(InputActions->CrouchAction, ETriggerEvent::Started, this, &ADRPlayerController::Crouch);
			EnhancedInputComponent->BindAction(InputActions->FireAction, ETriggerEvent::Started, this, &ADRPlayerController::PlayerStartFire);
			EnhancedInputComponent->BindAction(InputActions->FireAction, ETriggerEvent::Completed, this, &ADRPlayerController::PlayerStopFire);
			EnhancedInputComponent->BindAction(InputActions->ReloadAction, ETriggerEvent::Started, this, &ADRPlayerController::Reload);
			EnhancedInputComponent->BindAction(InputActions->PunchAction, ETriggerEvent::Started, this, &ADRPlayerController::Punch);
			EnhancedInputComponent->BindAction(InputActions->MenuAction, ETriggerEvent::Started, this, &ADRPlayerController::Menu);
		}
	}
}

void ADRPlayerController::Move(const FInputActionValue& Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		const FVector2D MovementVector = Value.Get<FVector2D>();
		CachedBaseCharacter->MoveForward(MovementVector.Y);
		CachedBaseCharacter->MoveRight(MovementVector.X);
	}
}

void ADRPlayerController::Look(const FInputActionValue& Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		const FVector2D LookVector = Value.Get<FVector2D>();
		CachedBaseCharacter->LookUp(LookVector.Y);
		CachedBaseCharacter->Turn(LookVector.X);
	}
}

void ADRPlayerController::Jump(const FInputActionValue& Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->Jump();
	}
}

void ADRPlayerController::Crouch(const FInputActionValue& Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->Crouch();
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

void ADRPlayerController::Reload(const FInputActionValue& Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->Reload();
	}
}

void ADRPlayerController::Punch(const FInputActionValue& Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->Punch();
	}
}

void ADRPlayerController::Menu(const FInputActionValue& Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->Menu();
	}
}
