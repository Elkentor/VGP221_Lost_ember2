#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WBP_GameHUD.generated.h"

UCLASS()
class LOSTEMBER2_API UWBP_GameHUD : public UUserWidget
{
    GENERATED_BODY()

public:

    // Appelé par le Blueprint pour mettre à jour la barre
    UFUNCTION(BlueprintCallable, Category = "HUD")
    float GetTimerPercent() const;

    UFUNCTION(BlueprintCallable, Category = "HUD")
    FText GetTimerText() const;

    UFUNCTION(BlueprintCallable, Category = "HUD")
    FText GetLightProgressText() const;
};