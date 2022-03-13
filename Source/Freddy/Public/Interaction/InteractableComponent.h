// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"

enum class EInteractionType : uint8;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FREDDY_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	/** Sets default values */
	UInteractableComponent();

	/** Called every frame */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Checks if the specified interaction type can be done */
	UFUNCTION(BlueprintCallable)
	bool CanInteract(EInteractionType InteractionType);

	/** Checks if the specified interaction type can be done */
	UFUNCTION(BlueprintCallable)
	void SetCanInteract(EInteractionType InteractionType, bool NewInteractable);

	/** Adds a new camera observer */
	void AddObserver(class UCameraTracer* CameraObserver);

	/** Removes a camera observer */
	void RemoveObserver(class UCameraTracer* CameraObserver);

	/** Updates all observers on this component's state */
	void UpdateObservers();

	/** Sets properties to be replicated */
	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;

protected:
	/** Called when the game starts */
	virtual void BeginPlay() override;

protected:
	/** Whether the object can be primary interacted with */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	bool PrimaryInteractable;

	/** Whether the object can be secondary interacted with */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	bool SecondaryInteractable;

	/** List of all observers of this interactable component */
	TArray<class UCameraTracer*> CameraObservers;
};
