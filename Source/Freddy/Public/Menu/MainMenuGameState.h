// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MainMenuGameState.generated.h"

/**
 * Base class for main menu game state
 */
UCLASS()
class FREDDY_API AMainMenuGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	/** Sets default values */
	AMainMenuGameState();

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ALobbyCharacterSpawnLocations* SpawnLocations;
};
