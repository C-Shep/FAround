// Fill out your copyright notice in the Description page of Project Settings.


#include "KeypadTrigger.h"
#include "Net/UnrealNetwork.h"
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
	
	GeneratePasswordServer();
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

void AKeypadTrigger::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	DOREPLIFETIME(AKeypadTrigger, password);
}

void AKeypadTrigger::PassPassword_Implementation(uint8 one, uint8 two, uint8 three, uint8 four)
{
	password = { one,two,three,four };
}

void AKeypadTrigger::GeneratePasswordServer_Implementation()
{
	TArray<uint8> newPassword{ 0,0,0,0 };

	//generate random password
	for (int i = 0; i < passLength; i++)
	{
		int passMin = 0;
		int passMax = 9;
		newPassword[i] = FMath::RandRange(passMin, passMax);
	}

	PassPassword(newPassword[0], newPassword[1], newPassword[2], newPassword[3]);
}

void AKeypadTrigger::RecieveBroadcastServer_Implementation(uint8 one, uint8 two, uint8 three, uint8 four)
{
	RecieveBroadcastGame(one, two, three, four);
}

void AKeypadTrigger::RecieveBroadcastGame_Implementation(uint8 one, uint8 two, uint8 three, uint8 four)
{
	TArray<uint8> enteredPassword{ one,two,three,four };

	if (enteredPassword == password)
	{
		//activate everything
		ActivateLinkedElements();
	}
	else {	//if wrong...
		DeactivateLinkedElements();
	}
}
