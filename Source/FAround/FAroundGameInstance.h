// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzleTrigger.h"
#include "KeypadTrigger.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
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

	UFUNCTION(Server, Reliable)
	virtual void BroadcastCodeServer(uint8 one, uint8 two, uint8 three, uint8 four);

	UFUNCTION(NetMulticast, Reliable)
	virtual void BroadcastCodeGame(uint8 one, uint8 two, uint8 three, uint8 four);

	virtual void BroadcastCode(const TArray<uint8> enteredPassword);

	void SendDataToDS(uint8 data);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool isServer = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isPlayer2Connected = false;
	UFUNCTION(BlueprintCallable)
	void checkForConnection(UWorld* world);
	ANetworkListener* networkListener;
	FSocket* connectedSocket;
	FSocket* listenerSocket;
};
