// Fill out your copyright notice in the Description page of Project Settings.


#include "Spikes.h"
#include "Logging/LogMacros.h"

ASpikes::ASpikes()
{
	//Create collisionbox component
	collisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));

	//Finish collision box setup
	collisionBox->SetupAttachment(RootComponent);
	collisionBox->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	damageTimerMax = 1.f;
	damageTimer = 0.f;
	damageSpeed = 1.f;
	damage = 1;
	isTouchingPlayer = false;
}

void ASpikes::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//search for player
	if (OtherActor->ActorHasTag(nameTags[0]))
	{
		if (player == NULL)
		{
			player = OtherActor;
		}

		isTouchingPlayer = true;
	}
}

void ASpikes::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//search for player
	if (OtherActor->ActorHasTag(nameTags[0]))
	{
		isTouchingPlayer = false;
	}
}

void ASpikes::BeginPlay()
{
	Super::BeginPlay();

	collisionBox->OnComponentBeginOverlap.AddDynamic(this, &ASpikes::OverlapBegin);
	collisionBox->OnComponentEndOverlap.AddDynamic(this, &ASpikes::OverlapEnd);
}

void ASpikes::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isTouchingPlayer)
	{
		if (damageTimer > 0)
		{
			damageTimer -= damageSpeed * DeltaTime;
		}
		else {
			Cast<AMazePlayer>(player)->TakeDamage(damage);
			damageTimer = damageTimerMax;
		}
	}
}
