// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseController.h"

#include "Character/BaseCharacter.h"
#include "Character/CameraTracer.h"
#include "Interaction/InteractionExecutor.h"
#include "Net/UnrealNetwork.h"

ABaseController::ABaseController()
{
	// Set turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create interaction executor
	InteractionExecutorRef = CreateDefaultSubobject<UInteractionExecutor>(TEXT("InteractionExecutor"));
}

void ABaseController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(InPawn);
	if (BaseCharacter)
	{
		BaseCharacter->CreateTracer();
		InteractionExecutorRef->Initialize(BaseCharacter->CameraTracerRef, BaseCharacter, BaseCharacter->CharacterInteractorType);
		InitializeExecutor();
	}
}

void ABaseController::InitializeExecutor_Implementation()
{
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetPawn());
	if (BaseCharacter)
	{
		InteractionExecutorRef->Initialize(BaseCharacter->CameraTracerRef, BaseCharacter, BaseCharacter->CharacterInteractorType);
		ExecutorInitialized = true;
	}
}

void ABaseController::SetupInputComponent()
{
    Super::SetupInputComponent();

	InputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ABaseController::PrimaryInteract);
	InputComponent->BindAction("SecondaryInteract", IE_Pressed, this, &ABaseController::SecondaryInteract);

	// 2 versions of the rotation bindings to handle different kinds of devices differently
	// "Turn" handles devices that provide an absolute delta, such as a mouse.
	// "Turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APlayerController::AddYawInput);
	InputComponent->BindAxis("TurnRate", this, &ABaseController::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APlayerController::AddPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &ABaseController::LookUpAtRate);
}

void ABaseController::TurnAtRate(float Rate)
{
	// Calculate delta for this frame from the rate information
	AddYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABaseController::LookUpAtRate(float Rate)
{
	// Calculate delta for this frame from the rate information
	AddPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool ABaseController::PossessNewCharacter_Validate(ABaseCharacter* NewCharacter)
{
	return true;
}

void ABaseController::PossessNewCharacter_Implementation(ABaseCharacter* NewCharacter)
{
	ABaseCharacter* PreviousPawn = Cast<ABaseCharacter>(GetPawn());
	if (PreviousPawn)
	{
		UnPossess();
		Possess(NewCharacter);
		PreviousPawn->Destroy();
	}
}

void ABaseController::PrimaryInteract()
{
	if (!ExecutorInitialized)
	{
		InitializeExecutor();
	}
	InteractionExecutorRef->InteractPressed(EInteractionType::Primary);
}

void ABaseController::SecondaryInteract()
{
	if (!ExecutorInitialized)
	{
		InitializeExecutor();
	}
	InteractionExecutorRef->InteractPressed(EInteractionType::Secondary);
}