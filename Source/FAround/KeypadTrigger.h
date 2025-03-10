// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleTrigger.h"
#include "KeypadTrigger.generated.h"

/**
 * 
 */
UCLASS()
class FAROUND_API AKeypadTrigger : public APuzzleTrigger
{
	GENERATED_BODY()

public:
	AKeypadTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Init vars
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Replicated)
	TArray<uint8> password;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TArray<int> enteredPassword;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int passLength;

	void RecieveBroadcast(TArray<uint8> enteredPassword);

	UFUNCTION(Server,Reliable)
	virtual void RecieveBroadcastServer(uint8 one, uint8 two, uint8 three, uint8 four);

	UFUNCTION(NetMulticast, Reliable)
	virtual void RecieveBroadcastGame(uint8 one, uint8 two, uint8 three, uint8 four);

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;
	
	UFUNCTION(Server, Reliable)
	virtual void GeneratePasswordServer();

	UFUNCTION(NetMulticast, Reliable)
	virtual void PassPassword(uint8 one, uint8 two, uint8 three, uint8 four);

};
