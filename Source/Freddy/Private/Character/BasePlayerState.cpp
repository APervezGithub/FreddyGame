// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BasePlayerState.h"

#include "Game/EOSGameInstance.h"

ABasePlayerState::ABasePlayerState()
{

}

void ABasePlayerState::BeginPlay()
{
	Super::BeginPlay();

	UEOSGameInstance* EOSGameInstance = Cast<UEOSGameInstance>(GetGameInstance());
	if (EOSGameInstance)
	{
		if (EOSGameInstance->NameSet)
		{
			SetPlayerName(EOSGameInstance->PlayerName);
		}
		else
		{
			EOSGameInstance->SetName(GetPlayerName());
		}
	}
}