// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleTrigger.h"
#include "KeypadTrigger.generated.h"

/**
 * 
 */
UCLASS()
class FAROUND_API AKeypadTrigger : public APuzzleTrigger
{
	GENERATED_BODY()
public:
	AKeypadTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Init vars
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<uint8> password;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TArray<int> enteredPassword;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int passLength;

	void RecieveBroadcast(TArray<uint8> enteredPassword);
	
};
