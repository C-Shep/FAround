// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollideDetector.h"
#include "mazePlayer.h"
#include "Spikes.generated.h"

/**
 * 
 */
UCLASS()
class FAROUND_API ASpikes : public ACollideDetector
{
	GENERATED_BODY()
	
public:
	ASpikes();
	virtual void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void OverlapEnd(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
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
};
