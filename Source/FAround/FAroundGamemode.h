// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FAroundGamemode.generated.h"

/**
 * 
 */
UCLASS()
class FAROUND_API AFAroundGamemode : public AGameModeBase{
	GENERATED_UCLASS_BODY()
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

};