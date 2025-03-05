// Fill out your copyright notice in the Description page of Project Settings.


#include "Spikes.h"

ASpikes::ASpikes()
{
	damageTimerMax = 1.f;
	damageTimer = 0.f;
	damage = 1;
	isTouchingPlayer = false;
}

void ASpikes::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (player == NULL)
	{
		player = OtherActor;
	}
	
	isTouchingPlayer = true;
}

void ASpikes::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	isTouchingPlayer = false;
}

void ASpikes::BeginPlay()
{
	Super::BeginPlay();
}

void ASpikes::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isTouchingPlayer)
	{
		if (damageTimer > 0)
		{
			damageTimer -= 1 * DeltaTime;
		}
		else {
			Cast<AMazePlayer>(player)->TakeDamage(damage);
			damageTimer = damageTimerMax;
		}
	}
}
