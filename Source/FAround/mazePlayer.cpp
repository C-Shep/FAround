// Fill out your copyright notice in the Description page of Project Settings.


#include "MazePlayer.h"
#include "PuzzleTrigger.h"
#include "PuzzleElement.h"
#include "Logging/LogMacros.h"

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
	FVector2D moveVector = Value.Get<FVector2D>();

	AddMovementInput(GetActorForwardVector(), moveVector.Y);
	AddMovementInput(GetActorRightVector(), moveVector.X);
}

//look around
void AMazePlayer::Look(const FInputActionValue& Value)
{
	FVector2D lookVector = Value.Get<FVector2D>();
	AddControllerYawInput(lookVector.X);
	AddControllerPitchInput(-lookVector.Y);
}

//jump? idk if we wanna jump but why not
void AMazePlayer::JumpFunc(const FInputActionValue& Value)
{
	const bool jumpPressed = Value.Get<bool>();

	ACharacter::Jump();
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
			Cast<APuzzleElement>(hitActor)->ActivateElement();
		
		}

		if (hitActor->ActorHasTag("PuzzleTrigger")) 
		{
			Cast<APuzzleTrigger>(hitActor)->Trigger();
		}
	}
}

// Called every frame
void AMazePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

