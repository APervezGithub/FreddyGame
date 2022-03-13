// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LobbyCharacterSpawnLocations.generated.h"

/**
 * Actor to hold spawn positions for lobby characters
 */
UCLASS()
class FREDDY_API ALobbyCharacterSpawnLocations : public AActor
{
	GENERATED_BODY()
	
public:	
	/** Sets default values for this actor's properties */
	ALobbyCharacterSpawnLocations();

public:
	/** Array of lobby character spawn points */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowedClasses = "LobbyCharacterSpawn"))
	TArray<class ALobbyCharacterSpawn*> SpawnPositions;

};
