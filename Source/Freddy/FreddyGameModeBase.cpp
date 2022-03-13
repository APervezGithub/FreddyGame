// Copyright Epic Games, Inc. All Rights Reserved.


#include "FreddyGameModeBase.h"

#include "Character/BaseCharacter.h"
#include "Character/BaseController.h"
#include "Character/BasePlayerState.h"

AFreddyGameModeBase::AFreddyGameModeBase()
{
	CurrentPhase = EGamePhase::None;
}

void AFreddyGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (NewPlayer)
	{
		if (ABaseController* NewBaseController = Cast<ABaseController>(NewPlayer))
		{
			GamePlayers.Emplace(NewBaseController);
			if (ABaseCharacter* NewCharacter = Cast<ABaseCharacter>(NewBaseController->GetPawn()))
			{
				NewCharacter->SetName(NewPlayer->GetPlayerState<ABasePlayerState>()->GetPlayerName());
			}
		}
	}
}

void AFreddyGameModeBase::CreateChaser()
{
	CreateNewCharacter(ChaserClass, ChaserController);
}

void AFreddyGameModeBase::CreateGhost(ABaseController* TargetController)
{
	CreateNewCharacter(GhostClass, TargetController);
}

void AFreddyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	StartPreGame();
}

void AFreddyGameModeBase::CreateNewCharacter(TSubclassOf<ABaseCharacter> CharacterClass, ABaseController* TargetController)
{
	if (TargetController)
	{
		FTransform NewTransform = TargetController->GetPawn()->GetTransform();
		FVector Location = NewTransform.GetLocation();
		FRotator Rotation = NewTransform.GetRotation().Rotator();
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ABaseCharacter* SpawnedCharacter = GetWorld()->SpawnActor<ABaseCharacter>(CharacterClass.Get(), Location, Rotation, SpawnInfo);
		SpawnedCharacter->SetName(TargetController->GetPlayerState<ABasePlayerState>()->GetPlayerName());
		TargetController->PossessNewCharacter(SpawnedCharacter);
	}
}

void AFreddyGameModeBase::StartPreGame()
{
	GetWorldTimerManager().SetTimer(PreGameTimer, this, &AFreddyGameModeBase::StartGame, PreGameLength, false, PreGameLength);
}

void AFreddyGameModeBase::StartGame()
{
	SelectChaser();
}

void AFreddyGameModeBase::SelectChaser()
{
	int SelectedIndex = FMath::RandRange(0, GamePlayers.Num() - 1);
	ChaserController = GamePlayers[SelectedIndex];
	CreateChaser();
}