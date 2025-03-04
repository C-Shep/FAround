// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkListener.h"

// Sets default values
ANetworkListener::ANetworkListener()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANetworkListener::BeginPlay()
{
    FIPv4Address IPAddress;
    FIPv4Address::Parse(FString("0.0.0.0"), IPAddress);
    FIPv4Endpoint Endpoint(IPAddress, (uint16)8080);
    listenSocket = FTcpSocketBuilder(TEXT("TcpSocket")).AsReusable().BoundToEndpoint(Endpoint);
    if (!listenSocket->Listen(1))
        UE_LOG(LogTemp, Error, TEXT("Error listening"));
    Super::BeginPlay();
}

void ANetworkListener::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (listenSocket)
        listenSocket->Close();
    if (connectionSocket)
        connectionSocket->Close();
    Super::EndPlay(EndPlayReason);
}

// Called every frame
void ANetworkListener::Tick(float DeltaTime)
{
    ListenForConnections();
    HandleConnectedSocket();
    Super::Tick(DeltaTime);
}

void ANetworkListener::ListenForConnections() {
    TSharedRef remoteAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    bool pending;
    listenSocket->HasPendingConnection(pending);
    if (pending) {
        // Destroy old
        if (connectionSocket) {
            connectionSocket->Close();
            ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(connectionSocket);
        }
        connectionSocket = listenSocket->Accept(*remoteAddress, TEXT("Listener socket received connection"));
        UE_LOG(LogTemp, Warning, TEXT("Connection received"));
        if (connectionSocket != NULL) {
            remoteAddressForConnection = FIPv4Endpoint(remoteAddress);
        }
    }
}

void ANetworkListener::HandleConnectedSocket() {
    if (!connectionSocket)
        return;
    int dataSize = 1;
    TArray<uint8> receivedData;
    uint32 size;
    if (connectionSocket->HasPendingData(size)) {
        receivedData.Init(0, dataSize);
        int32 read = 0;
        connectionSocket->Recv(receivedData.GetData(), receivedData.Num(), read);
        char data = receivedData[0];
        if (data == 65) {
            UE_LOG(LogTemp, Warning, TEXT("A press from DS"));
        }
    }
}