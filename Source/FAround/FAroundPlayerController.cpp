// Fill out your copyright notice in the Description page of Project Settings.


#include "FAroundPlayerController.h"

#include "FAroundGameInstance.h"
#include "GameFramework/GameModeBase.h"
#include "Net/UnrealNetwork.h"

AFAroundPlayerController::AFAroundPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	/* Initialize The Values */
	PawnToUseA= NULL;
	PawnToUseB= NULL;

	/* Make sure the PawnClass is Replicated */
	bReplicates = true;
}

void AFAroundPlayerController::BeginPlay()
{
	Super::BeginPlay();

	DeterminePawnClass();
}

// Pawn Class
void AFAroundPlayerController::DeterminePawnClass_Implementation()
{
	if (IsLocalController()) //Only Do This Locally (NOT Client-Only, since Server wants this too!)
	{
		
		
		
		/* Use PawnA if the Text File tells us to */
		if (Cast<UFAroundGameInstance>(GetGameInstance())->isServer)
		{
			ServerSetPawn(PawnToUseA);
			return;
		}

		/* Otherwise, Use PawnB :) */
		ServerSetPawn(PawnToUseB);
		return;
	}
}

bool AFAroundPlayerController::ServerSetPawn_Validate(TSubclassOf<APawn> InPawnClass)
{
	return true;
}

void AFAroundPlayerController::ServerSetPawn_Implementation(TSubclassOf<APawn> InPawnClass)
{
	MyPawnClass = InPawnClass;

	/* Just in case we didn't get the PawnClass on the Server in time... */
	GetWorld()->GetAuthGameMode()->RestartPlayer(this);
}

// Replication
void AFAroundPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(AFAroundPlayerController, MyPawnClass);
}