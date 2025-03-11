// Fill out your copyright notice in the Description page of Project Settings.


#include "MazePlayer.h"
#include "PuzzleTrigger.h"
#include "PuzzleElement.h"
#include "Kismet/GameplayStatics.h"
#include "Logging/LogMacros.h"
#include "UserKeypad.h"
#include "FAroundGameInstance.h"

// Sets default values
AMazePlayer::AMazePlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//// Create a CameraComponent	
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(RootComponent);
	camera->SetRelativeLocation(FVector(0.f, 0.f, 50.f)); // Position the camera
	camera->bUsePawnControlRotation = true;

	interactionRange = 200.f;
	playerHealth = 100.f;

	//intensity of post process damage effect
	damageProcessIntensity = 0;
	damageProcessFadeSpeed = 1;

	restartTimer = 0.f;
	maxRestartTimer = 2.f;
	bleedOut = false;
}

// Called when the game starts or when spawned
void AMazePlayer::BeginPlay()
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
void AMazePlayer::Move(const FInputActionValue& Value)
{
	if (!bleedOut)
	{
		FVector2D moveVector = Value.Get<FVector2D>();
		AddMovementInput(GetActorForwardVector(), moveVector.Y);
		AddMovementInput(GetActorRightVector(), moveVector.X);
	}
}

//look around
void AMazePlayer::Look(const FInputActionValue& Value)
{
	if (!bleedOut)
	{
		FVector2D lookVector = Value.Get<FVector2D>();
		AddControllerYawInput(lookVector.X);
		AddControllerPitchInput(-lookVector.Y);
	}
}

//jump? idk if we wanna jump but why not
void AMazePlayer::JumpFunc(const FInputActionValue& Value)
{
	if (!bleedOut)
	{
		const bool jumpPressed = Value.Get<bool>();
		ACharacter::Jump();
	}
}

void AMazePlayer::Interact(const FInputActionValue& Value)
{
	const bool interactPressed = Value.Get<bool>();

	FVector ForwardVector = camera->GetForwardVector();

	FVector StartPoint = camera->GetComponentLocation();

	FVector EndPoint = StartPoint + (ForwardVector * interactionRange);

	FCollisionQueryParams Parameters;

	FHitResult hit;

	bool SuccessfulHit = false;

	//DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Red, true, -1.0f, 0, 5.f);

	//Temporary Interaction Code for Testing
	if (GetWorld()->LineTraceSingleByChannel(hit, StartPoint, EndPoint, ECC_Visibility, Parameters))
	{
		AActor* hitActor = hit.GetActor();

		//Door Interaction
		if (hitActor->ActorHasTag("PuzzleElementDebug"))
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit"));

			//If you interact with a puzzle element, do its blueprint function. Puzzle Triggers!!!!!!
			Cast<APuzzleElement>(hitActor)->ToggleElement();
		
		}

		if (hitActor->ActorHasTag("PuzzleTrigger")) 
		{
			
			ServerTrigger(hitActor);
		}

		if (hitActor->ActorHasTag("UserKeypad")) {
			if (hit.GetComponent()->ComponentHasTag("0")) {
				ServerKeypad(hitActor, 0);
			}
			if (hit.GetComponent()->ComponentHasTag("1")) {
				ServerKeypad(hitActor, 1);
			}
			if (hit.GetComponent()->ComponentHasTag("2")) {
				ServerKeypad(hitActor, 2);
			}
			if (hit.GetComponent()->ComponentHasTag("3")) {
				ServerKeypad(hitActor, 3);
			}
			if (hit.GetComponent()->ComponentHasTag("4")) {
				ServerKeypad(hitActor, 4);
			}
			if (hit.GetComponent()->ComponentHasTag("5")) {
				ServerKeypad(hitActor, 5);
			}
			if (hit.GetComponent()->ComponentHasTag("6")) {
				ServerKeypad(hitActor, 6);
			}
			if (hit.GetComponent()->ComponentHasTag("7")) {
				ServerKeypad(hitActor, 7);
			}
			if (hit.GetComponent()->ComponentHasTag("8")) {
				ServerKeypad(hitActor, 8);
			}
			if (hit.GetComponent()->ComponentHasTag("9")) {
				ServerKeypad(hitActor, 9);
			}
			if (hit.GetComponent()->ComponentHasTag("enter")) {
				ServerKeypad(hitActor, 11);
			}
			if (hit.GetComponent()->ComponentHasTag("backspace")) {
				ServerKeypad(hitActor, 12);
			}
		}
	}
}

//Player take damage function
void AMazePlayer::TakeDamagePlayer(float damage)
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
	uint8 hp = playerHealth;
	if (hp < 0) {
		hp = 0;
	}
	Cast<UFAroundGameInstance>(GetGameInstance())->SendDataToDS(hp);
}

// Called every frame
void AMazePlayer::Tick(float DeltaTime)
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
			UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false,FString("listen"));
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
void AMazePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponenet = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponenet->BindAction(moveIA, ETriggerEvent::Triggered, this, &AMazePlayer::Move);
		EnhancedInputComponenet->BindAction(lookIA, ETriggerEvent::Triggered, this, &AMazePlayer::Look);
		EnhancedInputComponenet->BindAction(jumpIA, ETriggerEvent::Started, this, &AMazePlayer::JumpFunc);
		EnhancedInputComponenet->BindAction(interactIA, ETriggerEvent::Started, this, &AMazePlayer::Interact);
	}
}

void AMazePlayer::ServerTrigger_Implementation(AActor* button)
{
	Cast<APuzzleTrigger>(button)->Trigger();
}

void AMazePlayer::ServerKeypad_Implementation(AActor* button, uint8 buttonKey)
{
	KeypadMulticast(button, buttonKey);

}

void AMazePlayer::KeypadMulticast_Implementation(AActor* button, uint8 buttonKey) {
	Cast<AUserKeypad>(button)->ButtonPressed(buttonKey);
}
