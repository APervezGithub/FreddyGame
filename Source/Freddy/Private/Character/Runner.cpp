// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Runner.h"

#include "Camera/CameraComponent.h"
#include "Character/BaseController.h"
#include "Character/Chaser.h"
#include "Components/SpotLightComponent.h"
#include "Freddy/FreddyGameModeBase.h"
#include "Net/UnrealNetwork.h"

ARunner::ARunner():ABaseCharacter()
{
	// Set character interactor type
	CharacterInteractorType = EInteractorType::Runner;

	FlashlightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("Flash Light"));
	FlashlightComponent->SetupAttachment(CameraRef);
}

void ARunner::OnInteract(AActor* Caller, EInteractionType InteractionType, EInteractorType InteractorType)
{
	ABaseCharacter::OnInteract(Caller, InteractionType, InteractorType);
	switch (InteractorType)
	{
		case EInteractorType::Chaser:
		{
			switch (InteractionType)
			{
				case EInteractionType::Primary:
				{
					BecomeHaunted();
					break;
				}
				case EInteractionType::Secondary:
				{
					CanMove = false;
					break;
				}
			}
			break;
		}
	}
}

void ARunner::MultiToInteract(EInteractionType InteractionType, EInteractorType InteractorType)
{
	ABaseCharacter::MultiToInteract(InteractionType, InteractorType);
}

void ARunner::ReactToInteract_Implementation(EInteractionType InteractionType, EInteractorType InteractorType)
{
	ABaseCharacter::ReactToInteract_Implementation(InteractionType, InteractorType);
}

void ARunner::BecomeHaunted()
{
	AFreddyGameModeBase* GameMode = Cast<AFreddyGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		ABaseController* GhostController = Cast<ABaseController>(GetController());
		if (GhostController)
		{
			GameMode->CreateGhost(GhostController);
		}
	}
}