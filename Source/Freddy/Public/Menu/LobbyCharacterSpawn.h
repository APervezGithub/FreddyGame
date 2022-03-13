// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LobbyCharacterSpawn.generated.h"

/**
 * Actor to hold a spawn position for a lobby character
 */
UCLASS()
class FREDDY_API ALobbyCharacterSpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	/** Sets default values for this actor's properties */
	ALobbyCharacterSpawn();

public:
	/** World position of character */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector Location;

	/** World rotation of character */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FRotator Rotation;
};
