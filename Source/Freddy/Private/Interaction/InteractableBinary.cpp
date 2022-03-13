// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/InteractableBinary.h"
#include "Net/UnrealNetwork.h"

AInteractableBinary::AInteractableBinary()
{
	Toggled = false;
}

void AInteractableBinary::Toggle()
{
	Toggled = !Toggled;
}

void AInteractableBinary::OnRep_Toggled()
{
	OnRep_Toggled_BP();
}

void AInteractableBinary::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	DOREPLIFETIME(AInteractableBinary, Toggled);
}