
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "FAroundPlayerController.generated.h"
UCLASS()
class FAROUND_API AFAroundPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/* Constructor */
	AFAroundPlayerController(const FObjectInitializer& ObjectInitializer);

	FORCEINLINE UClass* GetPlayerPawnClass() { return MyPawnClass; }

protected:
	/* Return The Correct Pawn Class Client-Side */
	UFUNCTION(Reliable, Client)
	void DeterminePawnClass();
	virtual void DeterminePawnClass_Implementation();

	/* Use BeginPlay to start the functionality */
	virtual void BeginPlay() override;

	/* Set Pawn Class On Server For This Controller */
	UFUNCTION(Reliable, Server, WithValidation)
	virtual void ServerSetPawn(TSubclassOf<APawn> InPawnClass);
	virtual void ServerSetPawn_Implementation(TSubclassOf<APawn> InPawnClass);
	virtual bool ServerSetPawn_Validate(TSubclassOf<APawn> InPawnClass);

	/* Actual Pawn class we want to use */
	UPROPERTY(Replicated)
	TSubclassOf<APawn> MyPawnClass;

	/* First Pawn Type To Use */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "My Controller")
	TSubclassOf<APawn> PawnToUseMaze;

	/* Second Pawn Type To Use */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "My Controller")
	TSubclassOf<APawn> PawnToUseControlRoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "My Controller")
	TSubclassOf<APawn> PawnToUseVR;
};