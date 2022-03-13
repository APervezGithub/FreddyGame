// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/InteractionExecutor.h"

#include "Character/CameraTracer.h"
#include "Interaction/InteractableComponent.h"
#include "Interaction/InteractInterface.h"
#include "Net/UnrealNetwork.h"

UInteractionExecutor::UInteractionExecutor()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractionExecutor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInteractionExecutor::Initialize(class UCameraTracer* CameraTracer_, AActor* CharacterRef_, EInteractorType ExecutorInteractorType_)
{
	CameraTracer = CameraTracer_;
	CharacterRef = CharacterRef_;
	ExecutorInteractorType = ExecutorInteractorType_;
}

void UInteractionExecutor::InteractPressed(EInteractionType InteractionType)
{
	if (CameraTracer)
	{
		InteractLocal(InteractionType);
		InteractServer(InteractionType, CameraTracer->FocusedActor);
	}
}

void UInteractionExecutor::InteractLocal(EInteractionType InteractionType)
{
	if (CameraTracer && CameraTracer->FocusedActor)
	{
		// Tell the focused actor it was interacted with
		IInteractInterface* Interface = Cast<IInteractInterface>(CameraTracer->FocusedActor);
		if (Interface && Interface->GetComp()->CanInteract(InteractionType))
		{
			Interface->CallerOnInteract(CharacterRef, InteractionType, ExecutorInteractorType);
		}
	}
}

bool UInteractionExecutor::InteractServer_Validate(EInteractionType InteractionType, AActor* FocusedActor)
{
	return true;
}

void UInteractionExecutor::InteractServer_Implementation(EInteractionType InteractionType, AActor* FocusedActor)
{
	if (FocusedActor && CharacterRef)
	{
		// Tell the focused actor it was interacted with
		IInteractInterface* Interface = Cast<IInteractInterface>(FocusedActor);
		if (Interface && Interface->GetComp()->CanInteract(InteractionType))
		{
			Interface->OnInteract(CharacterRef, InteractionType, ExecutorInteractorType);
		}
	}
}

void UInteractionExecutor::BeginPlay()
{
	Super::BeginPlay();
}