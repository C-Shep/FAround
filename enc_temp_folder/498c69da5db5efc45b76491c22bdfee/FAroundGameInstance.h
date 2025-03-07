// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzleTrigger.h"
#include "FAroundGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FAROUND_API UFAroundGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:

	TArray<APuzzleTrigger*> buttons;
	

public:

	void FindAllButtons(UWorld* world);

	void TriggerButton(int index);

	bool isServer = true;
};
