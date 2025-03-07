// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzleTrigger.h"
#include "KeypadTrigger.h"
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
	TArray<AKeypadTrigger*> keypadItems;
	

public:

	void FindAllButtons(UWorld* world);

	void TriggerButton(int index);

	void BroadcastCode(TArray<uint8> enteredPassword);

	bool isServer = false;
};
