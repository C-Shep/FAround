// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "MazePlayer.generated.h"

UCLASS()
class FAROUND_API AMazePlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMazePlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// --- Movement Functions ---
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void JumpFunc(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);

	// --- Input Actions ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* moveIA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* lookIA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* jumpIA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* interactIA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputMappingContext* inputMappingContext;

	// --- Camera ---

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* camera;

	//Interaction Range
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float interactionRange;

	//Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float playerHealth;

	void TakeDamage(const float damage);

//	UFUNCTION(BlueprintCallable) float GetHealth();
};
