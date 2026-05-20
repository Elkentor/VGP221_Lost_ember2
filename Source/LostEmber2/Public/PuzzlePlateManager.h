#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzlePlateManager.generated.h"

class APressurePlate;

UCLASS()
class LOSTEMBER2_API APuzzlePlateManager : public AActor
{
    GENERATED_BODY()

public:
    APuzzlePlateManager();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

	// 3 pressure plates to associate with the puzzle
    UPROPERTY(EditAnywhere, Category = "Puzzle")
    APressurePlate* Plate1;

    UPROPERTY(EditAnywhere, Category = "Puzzle")
    APressurePlate* Plate2;

    UPROPERTY(EditAnywhere, Category = "Puzzle")
    APressurePlate* Plate3;

	// Avoids checking the puzzle state multiple times after completion
    bool bPuzzleCompleted;

	// Looks at the state of the pressure plates and determines if the puzzle is solved
    void CheckPuzzleState();
};