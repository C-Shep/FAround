// Fill out your copyright notice in the Description page of Project Settings.


#include "FAroundGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UFAroundGameInstance::FindAllButtons(UWorld * world)
{
	buttons.Empty();
	//TSubclassOf<APuzzleTrigger> classToFind;
	TArray<AActor*> foundActors;
	UGameplayStatics::GetAllActorsOfClass(world, APuzzleTrigger::StaticClass(), foundActors);

	for (int i = 0; i < foundActors.Num(); i++) {
		buttons.Add(Cast<APuzzleTrigger>(foundActors[i]));
	}

}

void UFAroundGameInstance::TriggerButton(int index) 
{
	buttons[index]->Trigger();
}