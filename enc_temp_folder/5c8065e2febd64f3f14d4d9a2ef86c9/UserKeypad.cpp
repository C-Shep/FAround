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

void AUserKeypad::SubmitPasswordMulticast_Implementation()
{
	if (password.Num() == 4) {
		Cast<UFAroundGameInstance>(GetGameInstance())->BroadcastCodeServer(password[0], password[1], password[2], password[3]);
		password.Empty();
	}
}

void AUserKeypad::SubmitPassword_Implementation()
{
	SubmitPasswordMulticast();
}

void AUserKeypad::ButtonPressed(uint8 button) {
	if (button == 11) {
		SubmitPassword();
	}
	else if (button == 12) {
		BackspacePressed();
	}
	else if (password.Num() < 4) {
		password.Add(button);
		passwordBLUEPRINT.Empty();
		for (int i = 0; i < password.Num(); i++) {
			passwordBLUEPRINT.Add(int(password[i]));
		}
	}
}

void AUserKeypad::BackspacePressed() {
	if (password.Num() > 0) {

		password.RemoveAt(password.Num() - 1);
	}
}

int AUserKeypad::GetPasswordAtIndex(int index)
{
	if (password.Num() > index) {
		GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Yellow, FString::Printf(TEXT("%lld"), int(password[index])));
		return int(password[index]);
	}

	return 0;
}
