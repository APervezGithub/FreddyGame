// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

/**
 * Base class for main menu game mode
 */
UCLASS()
class FREDDY_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	/** Sets default values */
	AMainMenuGameMode();

	/** Adds a player to the array at the lowest available index */
	void AddPlayerToLobby(class AMenuController* NewController);

protected:
	/** Called when game mode starts */
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	/** Called when a new player logs in */
	virtual void PostLogin(APlayerController* NewPlayer) override;

	/** Spawns a new player character in the lobby */
	class ABaseCharacter* SpawnPlayer(int PlayerIndex, class AMenuController* NewController);

public:
	/** Limit of how many players can be in the lobby */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int MaxPlayers;

protected:
	/** Class for chaser character */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class ABaseCharacter> CharacterClass;

	/** Array of all players in the lobby */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class AMenuController*> LobbyPlayers;

	/** Array of all characters in the lobby */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class ABaseCharacter*> LobbyCharacters;

	/** Lowest lobby index that does not have a player in it */
	int MinAvailableIndex;

};
