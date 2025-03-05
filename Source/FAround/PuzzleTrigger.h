// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleElement.h"
#include "PuzzleTrigger.generated.h"

UCLASS()
class FAROUND_API APuzzleTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleTrigger();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<APuzzleElement*> triggeredElements;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool toggle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float activeTimerMax;

	float activeTimer;
	
	bool triggerState;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Trigger();

	void ActivateLinkedElements();

	void DeactivateLinkedElements();

};
