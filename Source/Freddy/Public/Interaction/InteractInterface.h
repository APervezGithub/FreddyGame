// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractInterface.generated.h"

/** Enumerator for types of interactions */
UENUM(BlueprintType)
enum class EInteractionType : uint8
{
	Primary = 0,
	Secondary = 1
};

/** Enumerator for types of interactors */
UENUM(BlueprintType)
enum class EInteractorType : uint8
{
	Runner = 0,
	Chaser = 1,
	Ghost = 2
};

/** Don't modify */
UINTERFACE(Blueprintable, MinimalAPI)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface that allows interaction
 */
class FREDDY_API IInteractInterface
{
	GENERATED_BODY()

public:
	/** Called on server when interacted with */
	virtual void OnInteract(AActor* Caller, EInteractionType InteractionType, EInteractorType InteractorType);

	/** Called on server when interacted with, implemented in blueprints */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnInteract_BP(AActor* Caller, EInteractionType InteractionType, EInteractorType InteractorType);

	/** Called immediately on calling client when interacted with */
	virtual void CallerOnInteract(AActor* Caller, EInteractionType InteractionType, EInteractorType InteractorType);

	/** Called immediately on calling client when interacted with, implemented in blueprints */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CallerOnInteract_BP(AActor* Caller, EInteractionType InteractionType, EInteractorType InteractorType);

	/** Called after successful interaction on all players. Should always call some multicast function.
		Since interfaces don't seem to support networked functions, this can't be multicast. */
	virtual void MultiToInteract(EInteractionType InteractionType, EInteractorType InteractorType);

	/** Called when interactable actor gains selection focus */
	virtual void StartFocus();

	/** Called when interactable actor gains selection focus, implemented in blueprints */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartFocus_BP();

	/** Called when interactable actor loses selection focus */
	virtual void EndFocus();

	/** Called when interactable actor gains selection focus, implemented in blueprints */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EndFocus_BP();

	/** Returns pointer to the actor's interactable component */
	virtual class UInteractableComponent* GetComp() = 0;

	// The return value of these functions should only be used in blueprints (probably UI)

	/** Returns name of interactable object */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FText GetName(EInteractorType InteractorType);

	/** Returns primary action according to interactor type */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FText GetPrimaryAction(EInteractorType InteractorType);

	/** Returns secondary action according to interactor type */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FText GetSecondaryAction(EInteractorType InteractorType);

};
