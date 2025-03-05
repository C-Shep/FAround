// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleTrigger.h"

// Sets default values
APuzzleTrigger::APuzzleTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APuzzleTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APuzzleTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (!toggle) {
		if (activeTimer > 0) {
			activeTimer -= DeltaTime;
		}
		else {
			if (triggerState) {
				DeactivateLinkedElements();
			}
		}
	}

}

void APuzzleTrigger::Trigger() 
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Some debug message!"));
	if (toggle) {
		if (triggerState) {
			DeactivateLinkedElements();
		}
		else {
			ActivateLinkedElements();
		}
	}
	else {
		if (activeTimer <= 0) {
			ActivateLinkedElements();
			activeTimer = activeTimerMax;
		}
	}
}

void APuzzleTrigger::ActivateLinkedElements()
{
	triggerState = true;
	for (int i = 0; i < triggeredElements.Num(); i++) {
		triggeredElements[i]->ActivateElement();
	}

}

void APuzzleTrigger::DeactivateLinkedElements()
{
	triggerState = false;
	for (int i = 0; i < triggeredElements.Num(); i++) {
		triggeredElements[i]->DeactivateElement();
	}

}

 