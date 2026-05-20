#include "PuzzlePlateManager.h"
#include "LostEmberGameMode.h"
#include "PressurePlate.h"

APuzzlePlateManager::APuzzlePlateManager()
{
    PrimaryActorTick.bCanEverTick = true;
    bPuzzleCompleted = false;
}

void APuzzlePlateManager::BeginPlay()
{
    Super::BeginPlay();
}

void APuzzlePlateManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    CheckPuzzleState();
}

void APuzzlePlateManager::CheckPuzzleState()
{
    if (bPuzzleCompleted)
        return;

    if (!Plate1 || !Plate2 || !Plate3)
        return;

	// Looks at the state of the pressure plates and determines if the puzzle is solved
    if (Plate1->bIsActivated &&
        Plate2->bIsActivated &&
        Plate3->bIsActivated)
    {
        bPuzzleCompleted = true;

        UE_LOG(LogTemp, Warning, TEXT("PUZZLE 2 COMPLETED"));

		// call a function in the game mode to register that a light has been activated
        if (ALostEmberGameMode* GM = Cast<ALostEmberGameMode>(GetWorld()->GetAuthGameMode()))
        {
            GM->RegisterLightActivated();
        }
    }
}