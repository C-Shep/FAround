// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleElement.h"

// Sets default values
APuzzleElement::APuzzleElement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APuzzleElement::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APuzzleElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APuzzleElement::GetActiveBool()
{
	return activeBool;
}

void APuzzleElement::SetActiveBool(bool newBool)
{
	activeBool = newBool;
}

void APuzzleElement::ActivateElement() {

	if (!activeBool) {
		OnElementActivated.Broadcast(true);
	}
		SetActiveBool(true);

}

void APuzzleElement::DeactivateElement() {

	if (activeBool) {
		OnElementActivated.Broadcast(false);
	}
	SetActiveBool(false);

}

void APuzzleElement::ToggleElement() {

	if (!activeBool) {
		OnElementActivated.Broadcast(true);
		SetActiveBool(true);
	}
	else {
		OnElementActivated.Broadcast(false);
		SetActiveBool(false);
	}

}