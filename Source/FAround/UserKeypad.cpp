// Fill out your copyright notice in the Description page of Project Settings.


#include "UserKeypad.h"
#include "FAroundGameInstance.h"

// Sets default values
AUserKeypad::AUserKeypad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUserKeypad::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUserKeypad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUserKeypad::SubmitPassword()
{
	if (password.Num() == 4) {
		Cast<UFAroundGameInstance>(GetGameInstance())->BroadcastCode(password);
		password.Empty();
	}
}

void AUserKeypad::ButtonPressed(uint8 button)
{
	if (password.Num() < 4) {
		password.Add(button);
	}
}

void AUserKeypad::BackspacePressed()
{
	if (password.Num() < 0){

		password.RemoveAt(password.Num() - 1);
	}
}

