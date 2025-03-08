// Fill out your copyright notice in the Description page of Project Settings.


#include "FAroundGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "NetworkListener.h"

void UFAroundGameInstance::FindAllButtons(UWorld * world)
{
	buttons.Empty();
	//TSubclassOf<APuzzleTrigger> classToFind;
	TArray<AActor*> foundActors;
	UGameplayStatics::GetAllActorsOfClass(world, APuzzleTrigger::StaticClass(), foundActors);

	for (int i = 0; i < foundActors.Num(); i++) {
		if (foundActors[i]->ActorHasTag("Button")) {
			buttons.Add(Cast<APuzzleTrigger>(foundActors[i]));
		}
		else if (foundActors[i]->ActorHasTag("Keypad")) {
			keypadItems.Add(Cast<AKeypadTrigger>(foundActors[i]));
		}
	}



}

void UFAroundGameInstance::TriggerButton(int index) 
{
	buttons[index]->Trigger();
}

void UFAroundGameInstance::BroadcastCode(TArray<uint8> enteredPassword)
{
	for (auto keypad : keypadItems) {
		keypad->RecieveBroadcast(enteredPassword);
	}
}

void UFAroundGameInstance::SendDataToDS(uint8 data) {
	if (networkListener != nullptr) {
		networkListener->SendData(data);
	}
}