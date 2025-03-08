// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzleTrigger.h"
#include "KeypadTrigger.h"
#include "FAroundGameInstance.generated.h"

class ANetworkListener;

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

	void SendDataToDS(uint8 data);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool isServer = false;
	ANetworkListener* networkListener;
};
