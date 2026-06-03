#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LostEmberGameMode.generated.h"

UCLASS()
class LOSTEMBER2_API ALostEmberGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ALostEmberGameMode();

    virtual void BeginPlay() override;
    virtual void StartPlay() override;
    virtual void Tick(float DeltaTime) override;

    // Lights / Puzzles
    UFUNCTION(BlueprintCallable, Category = "Lights")
    void RegisterLightActivated();

    UFUNCTION(BlueprintCallable, Category = "Lights")
    int32 GetActivatedLightCount() const { return ActivatedLightCount; }

    UFUNCTION(BlueprintCallable, Category = "Lights")
    int32 GetTotalRequiredLights() const { return TotalRequiredLights; }

    // Timer
    UFUNCTION(BlueprintCallable, Category = "Timer")
    float GetCurrentTime() const { return CurrentTime; }

    UFUNCTION(BlueprintCallable, Category = "Timer")
    float GetMaxTime() const { return MaxTime; }

    // Game State
    UFUNCTION(BlueprintCallable, Category = "GameState")
    bool IsGameOver() const { return bIsGameOver; }

    UFUNCTION(BlueprintCallable, Category = "GameState")
    bool IsWin() const { return bIsWin; }

    // HUD
    UPROPERTY(EditAnywhere, Category = "HUD")
    TSubclassOf<UUserWidget> GameHUDClass;

    UUserWidget* GameHUDInstance;

    // Doors
    UPROPERTY(EditAnywhere, Category = "Doors")
    TArray<AActor*> DoorsToOpen;

    // Win / Game Over UI
    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UUserWidget> WinWidgetClass;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UUserWidget> GameOverWidgetClass;

    UUserWidget* WinWidgetInstance;
    UUserWidget* GameOverWidgetInstance;

    // Game Over handling
    void HandleGameOver(bool bPlayerWon);

protected:

    // Lights / Puzzles
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lights")
    int32 ActivatedLightCount;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lights")
    int32 TotalRequiredLights;

    // Timer
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Timer")
    float MaxTime;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timer")
    float CurrentTime;

    // Game State
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameState")
    bool bIsGameOver;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameState")
    bool bIsWin;
};