// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PuzzleElement.h"
#include "GameFramework/Actor.h"
#include "CollideDetector.generated.h"



UCLASS()
class FAROUND_API ACollideDetector : public APuzzleElement
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollideDetector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Collisions
	UFUNCTION() virtual void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() virtual void OverlapEnd(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBoxComponent* collisionBox;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<APuzzleElement*> linkedElements;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> nameTags;
};
