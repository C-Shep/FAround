// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonGetter.h"
#include "FAroundGameInstance.h"


// Sets default values
AButtonGetter::AButtonGetter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AButtonGetter::BeginPlay()
{
	Super::BeginPlay();
	
	delayTimer = 0.5f;
	triggered = false;

}

void AButtonGetter::Tick(float DeltaTime) {

	UFAroundGameInstance* instance = Cast<UFAroundGameInstance>(GetGameInstance());
	if (delayTimer > 0) {
		delayTimer -= DeltaTime;
	}
	else {
		if (!triggered) {
			instance->FindAllButtons(GetWorld());
			triggered = true;
		}
	}
	instance->checkForConnection(GetWorld());
}


