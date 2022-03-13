// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "Character/CameraTracer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interaction/InteractableComponent.h"
#include "Net/UnrealNetwork.h"


ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Set controller rotation variables
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Allow character to move
	CanMove = true;
	
	// Set character interactor type
	CharacterInteractorType = EInteractorType::Runner;

	// Allow character to trace
	TracerEnabled = true;
	TracerDistance = 500.f;

	// Create camera
	CameraRef = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraRef->bUsePawnControlRotation = true;
	CameraRef->SetupAttachment(RootComponent);

	// Create interactable component
	InteractableRef = CreateDefaultSubobject<UInteractableComponent>(TEXT("Interactable"));
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseCharacter, CharacterName);
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);
}

void ABaseCharacter::OnInteract(AActor* Caller, EInteractionType InteractionType, EInteractorType InteractorType)
{
	IInteractInterface::OnInteract(Caller, InteractionType, InteractorType);
}

void ABaseCharacter::MultiToInteract(EInteractionType InteractionType, EInteractorType InteractorType)
{
	IInteractInterface::MultiToInteract(InteractionType, InteractorType);
	ReactToInteract(InteractionType, InteractorType);
}

void ABaseCharacter::ReactToInteract_Implementation(EInteractionType InteractionType, EInteractorType InteractorType)
{
	ReactToInteract_BP(InteractionType, InteractorType);
}

UInteractableComponent* ABaseCharacter::GetComp()
{
	return InteractableRef;
}

void ABaseCharacter::CreateTracer_Implementation()
{
	if (IsLocallyControlled())
	{
		// Create camera tracer
		if (CameraTracerRef)
		{
			CameraTracerRef->DestroyComponent();
		}
		CameraTracerRef = NewObject<UCameraTracer>(this, CameraTracerType.Get(), TEXT("NewCameraTracer"));
		CameraTracerRef->Initialize(TracerEnabled, TracerDistance, CameraRef, CharacterInteractorType);
		CameraTracerRef->RegisterComponent();
	}
}

void ABaseCharacter::SetHiding(FVector Location)
{

}

void ABaseCharacter::SetName(FString NewName)
{
	CharacterName = NewName;
	OnRep_CharacterName();
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	CreateTracer();
}

void ABaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	const UWorld* CurrentWorld = GetWorld();
	if (CurrentWorld && CurrentWorld->IsGameWorld()) // Check if this is being called in game
	{
		
	}
}

void ABaseCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f) && CanMove)
	{
		// Find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABaseCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f) && CanMove)
	{
		// Find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get right vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// Add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ABaseCharacter::OnRep_CharacterName()
{
	ShowName();
}