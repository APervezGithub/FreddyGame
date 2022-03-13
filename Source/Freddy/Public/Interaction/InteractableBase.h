// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/InteractInterface.h"
#include "InteractableBase.generated.h"

/**
 * Base class for interactable actors
 */

UCLASS()
class FREDDY_API AInteractableBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:
	/** Sets default values for this actor's properties */
	AInteractableBase();

	/** Called every frame */
	virtual void Tick(float DeltaTime) override;

	/** Called after successful interaction on all players */
	void MultiToInteract(EInteractionType InteractionType, EInteractorType InteractorType) override;

	/** Called after successful interaction on all players */
	UFUNCTION(NetMulticast, Reliable)
	virtual void ReactToInteract(EInteractionType InteractionType, EInteractorType InteractorType);

	/** Called after successful interaction on all players, implemented in blueprints */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ReactToInteract_BP(EInteractionType InteractionType, EInteractorType InteractorType);

	/** Returns pointer to the actor's interactable component */
	virtual class UInteractableComponent* GetComp() override;

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

public:
	/** Static mesh representation of actor */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Mesh;

	/** Interactable component */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Interaction)
	class UInteractableComponent* InteractableRef;
};
