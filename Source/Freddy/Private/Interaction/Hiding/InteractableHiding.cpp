// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/Hiding/InteractableHiding.h"

#include "Character/BaseCharacter.h"

AInteractableHiding::AInteractableHiding()
{
	HidingLocation = FVector(0, 0, 0);
}

void AInteractableHiding::OnInteract(AActor* Caller, EInteractionType InteractionType, EInteractorType InteractorType)
{
	Super::OnInteract(Caller, InteractionType, InteractorType);

	ABaseCharacter* InteractingCharacter = Cast<ABaseCharacter>(Caller);
	if (InteractingCharacter)
	{
		InteractingCharacter->SetHiding(GetAbsoluteHidingLocation());
	}
}

FVector AInteractableHiding::GetAbsoluteHidingLocation()
{
	return GetTransform().GetLocation() + HidingLocation;
}