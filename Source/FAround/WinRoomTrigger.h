// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "WinRoomTrigger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGoodJobYouWin);

/**
 * 
 */
UCLASS()
class FAROUND_API AWinRoomTrigger : public ATriggerBox
{
	GENERATED_BODY()
	AWinRoomTrigger();

	UFUNCTION(BlueprintCallable)
	void onOverlap();

	UPROPERTY(BlueprintAssignable, Category = "Custom")
	FGoodJobYouWin OnGoodJobYouWin;
};
