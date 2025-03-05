// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleElement.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPuzzleActive, bool, elementActive);

UCLASS()
class FAROUND_API APuzzleElement : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleElement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool GetActiveBool();
	void SetActiveBool(bool newBool);

	void ActivateElement();
	void DeactivateElement();

	void ToggleElement();

	UPROPERTY(BlueprintAssignable, Category = "Custom")
	FPuzzleActive OnElementActivated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	bool activeBool;
};
