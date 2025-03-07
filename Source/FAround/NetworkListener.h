// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "FAroundGameInstance.h"
#include "NetworkListener.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReceivedData, uint8, Data);

UCLASS()
class FAROUND_API ANetworkListener : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANetworkListener();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void ListenForConnections();
	void HandleConnectedSocket();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(BlueprintAssignable, Category = "Custom")
	FReceivedData OnReceivedData;

protected:
	FSocket* listenSocket;
	FSocket* connectionSocket;
	FIPv4Endpoint remoteAddressForConnection;
	UFAroundGameInstance* gameInstance;

	TArray<uint8> enteredPass;

};
