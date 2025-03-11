// Fill out your copyright notice in the Description page of Project Settings.


#include "WinRoomTrigger.h"
#include "FAroundGameInstance.h"

AWinRoomTrigger::AWinRoomTrigger() {

}

void AWinRoomTrigger::onOverlap()
{
	uint8 data = 253;
	UFAroundGameInstance* gameInstance = Cast<UFAroundGameInstance>(GetGameInstance());
	gameInstance->SendDataToDS(data);
}
