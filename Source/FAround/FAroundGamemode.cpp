// Fill out your copyright notice in the Description page of Project Settings.


#include "FAroundGamemode.h"

#include "FAroundPlayerController.h"

AFAroundGamemode::AFAroundGamemode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	/* Use our custom Player-Controller Class */
	PlayerControllerClass = AFAroundPlayerController::StaticClass();
}

UClass* AFAroundGamemode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	AFAroundPlayerController* MyController = Cast<AFAroundPlayerController>(InController);

	if (MyController)
	{
		UClass * balls = MyController->GetPlayerPawnClass();
		return balls;
	}
	return DefaultPawnClass;
}

	

