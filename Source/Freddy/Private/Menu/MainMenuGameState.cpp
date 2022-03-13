// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/MainMenuGameState.h"

#include "Kismet/GameplayStatics.h"
#include "Menu/MainMenuGameMode.h"
#include "Menu/MenuController.h"
#include "Menu/LobbyCharacterSpawnLocations.h"

AMainMenuGameState::AMainMenuGameState()
{
	
}

void AMainMenuGameState::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALobbyCharacterSpawnLocations::StaticClass(), FoundActors);
	if (FoundActors.Num() > 0)
	{
		ALobbyCharacterSpawnLocations* FoundSpawnLocations = Cast<ALobbyCharacterSpawnLocations>(FoundActors[0]);
		if (FoundSpawnLocations)
		{
			SpawnLocations = FoundSpawnLocations;
			if (GetWorld()->GetAuthGameMode())
			{
				AMainMenuGameMode* AuthGameMode = Cast<AMainMenuGameMode>(GetWorld()->GetAuthGameMode());
				AMenuController* AuthMenuController = Cast<AMenuController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
				if (AuthGameMode && AuthMenuController)
				{
					AuthGameMode->AddPlayerToLobby(AuthMenuController);
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No spawn locations actor found"));
	}
}