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
    gameInstance = Cast<UFAroundGameInstance>(GetGameInstance());
    if (gameInstance->listenerSocket != nullptr) {
        listenSocket = gameInstance->listenerSocket;
    }
    else {
        FIPv4Address IPAddress;
        FIPv4Address::Parse(FString("0.0.0.0"), IPAddress);
        FIPv4Endpoint Endpoint(IPAddress, (uint16)8080);
        listenSocket = FTcpSocketBuilder(TEXT("TcpSocket")).AsReusable().BoundToEndpoint(Endpoint);
        if (!listenSocket->Listen(1))
            UE_LOG(LogTemp, Error, TEXT("Error listening"));
    }
    gameInstance->networkListener = this;
    if (gameInstance->connectedSocket != nullptr) {
        connectionSocket = gameInstance->connectedSocket;
    }
    Super::BeginPlay();
}

void ANetworkListener::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (EndPlayReason == EEndPlayReason::EndPlayInEditor || EndPlayReason == EEndPlayReason::Quit) {
        if (listenSocket)
            listenSocket->Close();
        if (connectionSocket) {
            uint8 data = 255;
            int32 sentData;
            connectionSocket->Send(&data, 1, sentData);
            connectionSocket->Close();
        }
    }
    else {
        if (listenSocket)
            gameInstance->listenerSocket = listenSocket;
        if (connectionSocket)
            gameInstance->connectedSocket = connectionSocket;
    }
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
    do {
        listenSocket->HasPendingConnection(pending);
        if (pending) {
            // Destroy old
            if (connectionSocket) {
                connectionSocket->Close();
                ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(connectionSocket);
            }
            connectionSocket = listenSocket->Accept(*remoteAddress, TEXT("Listener socket received connection"));
            gameInstance->connectedSocket = connectionSocket;
            UE_LOG(LogTemp, Warning, TEXT("Connection received"));
            if (connectionSocket != NULL) {
                remoteAddressForConnection = FIPv4Endpoint(remoteAddress);
            }
        }
    } while (pending);
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
        uint8 data = receivedData[0];
        OnReceivedData.Broadcast(data);


        if (data >= 100) {

            switch (data) {

            case 110:
                if (enteredPass.Num() > 0) {
                    enteredPass.RemoveAt(enteredPass.Num() - 1,EAllowShrinking::Yes);
                }
                break;
            case 111:
                if (enteredPass.Num() == 4) {

                  

                    gameInstance->BroadcastCode(enteredPass);
                    enteredPass.Empty();
                }
                break;
            default:
                if (enteredPass.Num() < 4) {
                    enteredPass.Add(data - 100);
                }
                break;
            }

        }
        else {
            gameInstance->TriggerButton(data);
        }
    }
}

void ANetworkListener::SendData(uint8 data) {
    if (connectionSocket) {
        int32 bytesSent = 0;
        connectionSocket->Send(&data, 1, bytesSent);
        if (bytesSent == 0) {
            GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Failed to send message to DS"));
        }
    }
    else {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("No connected DS"));
    }
}