// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FreddyGameModeBase.generated.h"

/** Which phase the game is in */
UENUM(BlueprintType)
enum class EGamePhase : uint8
{
	None = 0,
	Pregame = 1,
	Game = 2
};

/**
 * Base class for main game mode
 */
UCLASS()
class FREDDY_API AFreddyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	/** Sets default values */
	AFreddyGameModeBase();

	/** Called when a new player logs in */
	virtual void PostLogin(APlayerController* NewPlayer) override;

	/** Creates a chaser character and sets it to the chaser controller */
	UFUNCTION(BlueprintCallable)
	void CreateChaser();

	/** Creates a ghost character and sets it to the target controller */
	UFUNCTION(BlueprintCallable)
	void CreateGhost(class ABaseController* TargetController);

protected:
	/** Called when the game starts */
	virtual void BeginPlay() override;

	/** Spawns a new character of specified class and sets it to the target controller */
	void CreateNewCharacter(TSubclassOf<class ABaseCharacter> CharacterClass, class ABaseController* TargetController);

	/** Starts the pre game phase */
	void StartPreGame();

	/** Starts the game phase */
	void StartGame();

	/** Selects a player controller to be the chaser */
	void SelectChaser();

public:
	/** Array of all players in game */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class ABaseController*> GamePlayers;

	/** Array of all players in game */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EGamePhase CurrentPhase;

protected:
	/** Class for chaser character */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class ABaseCharacter> ChaserClass;

	/** Controller that is/will be possessing chaser */
	class ABaseController* ChaserController;

	/** Class for ghost character */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class ABaseCharacter> GhostClass;

	/** Timer handle for timer to start game */
	FTimerHandle PreGameTimer;

	/** Length of pre game before starting by default */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float PreGameLength;
};
