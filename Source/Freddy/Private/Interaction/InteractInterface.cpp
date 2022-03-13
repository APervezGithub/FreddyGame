// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/InteractInterface.h"

#include "Interaction/InteractableComponent.h"
#include "Net/UnrealNetwork.h"

void IInteractInterface::OnInteract(AActor* Caller, EInteractionType InteractionType, EInteractorType InteractorType)
{
	Execute_OnInteract_BP(Cast<UObject>(this), Caller, InteractionType, InteractorType);
	MultiToInteract(InteractionType, InteractorType);
}

void IInteractInterface::CallerOnInteract(AActor* Caller, EInteractionType InteractionType, EInteractorType InteractorType)
{
	Execute_CallerOnInteract_BP(Cast<UObject>(this), Caller, InteractionType, InteractorType);
}

void IInteractInterface::MultiToInteract(EInteractionType InteractionType, EInteractorType InteractorType)
{
	// This should always be overriden
}

void IInteractInterface::StartFocus()
{
	Execute_StartFocus_BP(Cast<UObject>(this));
}

void IInteractInterface::EndFocus()
{
	Execute_EndFocus_BP(Cast<UObject>(this));
}