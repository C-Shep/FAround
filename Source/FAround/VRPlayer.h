// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VRCharacter.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "VRPlayer.generated.h"

/**
 *
 */
UCLASS()
class FAROUND_API AVRPlayer : public AVRCharacter
{
	GENERATED_BODY()
public:
	AVRPlayer();

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
	void JumpFunc(const FInputActionValue& Value);

	// --- Input Actions ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* moveIA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* jumpIA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* interactIA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputMappingContext* inputMappingContext;


	//Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float playerHealth;

	//intensity of damage effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float damageProcessIntensity;

	//Speed at which the PP fades out
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float damageProcessFadeSpeed;

	void TakeDamage(const float damage);

	//Death
	float restartTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maxRestartTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bleedOut;

};
