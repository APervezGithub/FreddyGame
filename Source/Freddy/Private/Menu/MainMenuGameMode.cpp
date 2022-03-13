// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/MainMenuGameMode.h"

#include "Character/BaseCharacter.h"
#include "Character/BasePlayerState.h"
#include "Menu/LobbyCharacterSpawn.h"
#include "Menu/LobbyCharacterSpawnLocations.h"
#include "Menu/MenuController.h"
#include "Menu/MainMenuGameState.h"

AMainMenuGameMode::AMainMenuGameMode()
{
	MaxPlayers = 4;
	MinAvailableIndex = 0;
}

void AMainMenuGameMode::AddPlayerToLobby(AMenuController* NewController)
{
	if (MinAvailableIndex == -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Lobby is full"));
		return;
	}
	if (LobbyPlayers.Contains(NewController))
	{
		return;
	}
	AMainMenuGameState* MainMenuGameState = GetWorld()->GetGameState<AMainMenuGameState>();
	if (MainMenuGameState && MainMenuGameState->SpawnLocations)
	{
		LobbyPlayers[MinAvailableIndex] = NewController;
		LobbyCharacters[MinAvailableIndex] = SpawnPlayer(MinAvailableIndex, NewController);
		MinAvailableIndex = -1;
		for (int MinIndex = 0; MinIndex < MaxPlayers; ++MinIndex)
		{
			if (LobbyPlayers[MinIndex] == nullptr)
			{
				MinAvailableIndex = MinIndex;
				break;
			}
		}
	}
}

void AMainMenuGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	LobbyPlayers.Init(nullptr, MaxPlayers);
	LobbyCharacters.Init(nullptr, MaxPlayers);
}

void AMainMenuGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (NewPlayer)
	{
		if (AMenuController* NewMenuController = Cast<AMenuController>(NewPlayer))
		{
			AddPlayerToLobby(NewMenuController);
		}
	}
}

ABaseCharacter* AMainMenuGameMode::SpawnPlayer(int PlayerIndex, AMenuController* NewController)
{
	AMainMenuGameState* MainMenuGameState = GetWorld()->GetGameState<AMainMenuGameState>();
	if (MainMenuGameState && MainMenuGameState->SpawnLocations)
	{
		TArray<ALobbyCharacterSpawn*> SpawnPositions = MainMenuGameState->SpawnLocations->SpawnPositions;
		if (PlayerIndex > SpawnPositions.Num())
		{
			UE_LOG(LogTemp, Warning, TEXT("Not enough spawn positions for the %dth index player"), PlayerIndex);
			return nullptr;
		}
		ALobbyCharacterSpawn* SpawnPoint = SpawnPositions[PlayerIndex];
		FVector Location = SpawnPoint->GetActorLocation();
		FRotator Rotation = SpawnPoint->GetActorRotation();
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ABaseCharacter* NewCharacter = GetWorld()->SpawnActor<ABaseCharacter>(CharacterClass.Get(), Location, Rotation, SpawnInfo);
		NewCharacter->SetName(NewController->GetPlayerState<ABasePlayerState>()->GetPlayerName());
		return NewCharacter;
	}
	return nullptr;
}