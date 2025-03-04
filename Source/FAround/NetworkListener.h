// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "NetworkListener.generated.h"

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

protected:
	FSocket* listenSocket;
	FSocket* connectionSocket;
	FIPv4Endpoint remoteAddressForConnection;

};
