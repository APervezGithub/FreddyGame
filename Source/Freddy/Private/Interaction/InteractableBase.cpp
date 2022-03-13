// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/InteractableBase.h"

#include "Components/StaticMeshComponent.h"
#include "Interaction/InteractableComponent.h"

AInteractableBase::AInteractableBase()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	InteractableRef = CreateDefaultSubobject<UInteractableComponent>(TEXT("Interactable"));
}

void AInteractableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableBase::MultiToInteract(EInteractionType InteractionType, EInteractorType InteractorType)
{
	IInteractInterface::MultiToInteract(InteractionType, InteractorType);
	ReactToInteract(InteractionType, InteractorType);
}

void AInteractableBase::ReactToInteract_Implementation(EInteractionType InteractionType, EInteractorType InteractorType)
{
	ReactToInteract_BP(InteractionType, InteractorType);
}

UInteractableComponent* AInteractableBase::GetComp()
{
	return InteractableRef;
}

void AInteractableBase::BeginPlay()
{
	Super::BeginPlay();
	
}

