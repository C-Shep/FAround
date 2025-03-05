// Fill out your copyright notice in the Description page of Project Settings.


#include "CollideDetector.h"

// Sets default values
ACollideDetector::ACollideDetector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	activatedTrigger = false;
	touchingActors = 0;

	//Create collisionbox component
	collisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));

	//Finish collision box setup
	collisionBox->SetupAttachment(RootComponent);
	collisionBox->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	touchingCorrect = false;
}

// Called when the game starts or when spawned
void ACollideDetector::BeginPlay()
{
	Super::BeginPlay();

	collisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACollideDetector::OverlapBegin);
	collisionBox->OnComponentEndOverlap.AddDynamic(this, &ACollideDetector::OverlapEnd);
	
}

// Called every frame
void ACollideDetector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//used in children
void ACollideDetector::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for (int i = 0; i < nameTags.Num(); i++)
	{
		if (OtherActor->ActorHasTag(nameTags[i]))
		{
			touchingCorrect = true;

			for (int j = 0; j < linkedElements.Num(); j++)
			{
				if (linkedElements[j] != NULL)
				{
					linkedElements[j]->ActivateElement();
				}
			}
		}
	}
}

void ACollideDetector::OverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	for (int i = 0; i < nameTags.Num(); i++)
	{
		if (OtherActor->ActorHasTag(nameTags[i]))
		{
			touchingCorrect = false;

			for (int j = 0; j < linkedElements.Num(); j++)
			{
				if (linkedElements[j] != NULL)
				{
					linkedElements[j]->DeactivateElement();
				}
			}
		}
	}
}