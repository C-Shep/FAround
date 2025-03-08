// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "mazePlayer.h"
#include "Components/BoxComponent.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PuzzleElement.h"
#include "GameFramework/Actor.h"
#include "Spikes.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCollideDetect, bool, collideActive);

/**
 * 
 */
UCLASS()
class FAROUND_API ASpikes : public APuzzleElement
{
	GENERATED_BODY()
	
public:
	ASpikes();
	UFUNCTION() virtual void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() virtual void OverlapEnd(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Attributes")
	float damageTimerMax;
	float damageTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Attributes")
	float damageSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Attributes")
	float damage;

	AActor* player;
	bool isTouchingPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBoxComponent* collisionBox;

	UPROPERTY(BlueprintAssignable, Category = "Custom")
	FCollideDetect OnCollided;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<APuzzleElement*> linkedElements;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> nameTags;
};
