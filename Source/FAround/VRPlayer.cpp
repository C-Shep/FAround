// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPlayer.h"
#include "PuzzleTrigger.h"
#include "PuzzleElement.h"
#include "Kismet/GameplayStatics.h"
#include "Logging/LogMacros.h"
#include "EnhancedInputSubsystems.h"
#include "FAroundGameInstance.h"

// Sets default values
AVRPlayer::AVRPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	playerHealth = 100.f;

	//intensity of post process damage effect
	damageProcessIntensity = 0;
	damageProcessFadeSpeed = 1;

	restartTimer = 0.f;
	maxRestartTimer = 2.f;
	bleedOut = false;
}

// Called when the game starts or when spawned
void AVRPlayer::BeginPlay()
{
	Super::BeginPlay();

	//Mapping context for movement
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(inputMappingContext, 0);
		}
	}
}

//move around
void AVRPlayer::Move(const FInputActionValue& Value)
{
	if (!bleedOut)
	{
		FVector2D moveVector = Value.Get<FVector2D>();


		//AddMovementInput(GetActorForwardVector(), moveVector.Y);
		//AddMovementInput(GetActorRightVector(), moveVector.X);
	}
}



//jump? idk if we wanna jump but why not
void AVRPlayer::JumpFunc(const FInputActionValue& Value)
{
	if (!bleedOut)
	{
		const bool jumpPressed = Value.Get<bool>();
		ACharacter::Jump();
	}
}

//Player take damage function
void AVRPlayer::TakeDamagePlayer(float damage)
{
	//reduce health by damage
	playerHealth -= damage;

	//set damage intensity to max
	damageProcessIntensity = 1.f;

	//if hp is less than or is 0, restart
	if (playerHealth <= 0.f)
	{
		bleedOut = true;
	}
}

// Called every frame
void AVRPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bleedOut)
	{
		if (restartTimer < maxRestartTimer)
		{
			damageProcessIntensity = 1.f;
			restartTimer += 1.f * DeltaTime;
		}
		else {
			Cast<UFAroundGameInstance>(GetGameInstance())->SendDataToDS(254);
			UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
		}
	}
	else {
		if (damageProcessIntensity > 0)
		{
			damageProcessIntensity -= damageProcessFadeSpeed * DeltaTime;
		}

	}
}

// Called to bind functionality to input
void AVRPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponenet = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponenet->BindAction(moveIA, ETriggerEvent::Triggered, this, &AVRPlayer::Move);
		EnhancedInputComponenet->BindAction(jumpIA, ETriggerEvent::Started, this, &AVRPlayer::JumpFunc);

	}
}