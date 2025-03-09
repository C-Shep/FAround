// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UserKeypad.generated.h"

UCLASS()
class FAROUND_API AUserKeypad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUserKeypad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<uint8> password;

	void SubmitPassword();
	void ButtonPressed(uint8 button);
	void BackspacePressed();

};
