// Fill out your copyright notice in the Description page of Project Settings.


#include "KeypadTrigger.h"
#include "Math.h"

AKeypadTrigger::AKeypadTrigger()
{
	//Length of the password
	passLength = 4;

	password.SetNum(passLength);
}

void AKeypadTrigger::BeginPlay()
{
	Super::BeginPlay();

	//generate random password
	for (int i = 0; i < passLength; i++)
	{
		int passMin = 0;
		int passMax = 9;
		password[i] = FMath::RandRange(passMin, passMax);
	}
}

void AKeypadTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKeypadTrigger::RecieveBroadcast(TArray<uint8> enteredPassword)
{
	if (enteredPassword == password)
	{
		//activate everything
		ActivateLinkedElements();
	}
	else {	//if wrong...
		DeactivateLinkedElements();
	}
}
