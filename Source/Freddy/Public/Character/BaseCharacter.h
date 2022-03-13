// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interaction/InteractInterface.h"
#include "BaseCharacter.generated.h"

/**
 * Base class for character
 */

UCLASS()
class FREDDY_API ABaseCharacter : public ACharacter, public IInteractInterface
{
	GENERATED_BODY()

public:
	/** Sets default values */
	ABaseCharacter();

	/** Marks properties for replication */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Called every frame */
	virtual void Tick(float DeltaTime) override;

	/** Called to bind functionality to input */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called on server when interacted with */
	virtual void OnInteract(AActor* Caller, EInteractionType InteractionType, EInteractorType InteractorType) override;

	/** Called after successful interaction on all players */
	virtual void MultiToInteract(EInteractionType InteractionType, EInteractorType InteractorType) override;

	/** Called after successful interaction on all players */
	UFUNCTION(NetMulticast, Reliable)
	virtual void ReactToInteract(EInteractionType InteractionType, EInteractorType InteractorType);

	/** Called after successful interaction on all players, implemented in blueprints */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ReactToInteract_BP(EInteractionType InteractionType, EInteractorType InteractorType);

	/** Returns pointer to the actor's interactable component */
	virtual class UInteractableComponent* GetComp() override;

	/** Create camera tracer on client only */
	UFUNCTION(Client, Reliable)
	void CreateTracer();

	/** Sets the character to hide at the specified location */
	void SetHiding(FVector Location);

	/** Sets the character's name and replicates */
	void SetName(FString NewName);

	/** Shows the character's name if it is set to be shown */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowName();

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	/** Called when all components have been intialized */
	virtual void PostInitializeComponents() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** Called to replicate name */
	UFUNCTION()
	void OnRep_CharacterName();

public:
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* CameraRef;

	/** Camera tracer */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera)
	class UCameraTracer* CameraTracerRef;

	/** Interactable component */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Interaction)
	class UInteractableComponent* InteractableRef;

	/** Type of interactor of player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EInteractorType CharacterInteractorType;

protected:
	/** Whether the character can move */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool CanMove;

	/** Class for the camera tracer */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class UCameraTracer> CameraTracerType;

	/** Whether the character can camera trace */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool TracerEnabled;

	/** How far the camera traces */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TracerDistance;

	/** Whether the character's name should be shown */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool ShouldShowName;

	/** Name of player */
	UPROPERTY(ReplicatedUsing = OnRep_CharacterName, VisibleAnywhere, BlueprintReadOnly)
	FString CharacterName;
};

