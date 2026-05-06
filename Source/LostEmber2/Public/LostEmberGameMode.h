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

    UFUNCTION(BlueprintCallable)
    void RegisterLightActivated();

    UFUNCTION(BlueprintCallable)
    int32 GetActivatedLightCount() const { return ActivatedLightCount; }

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lights")
    int32 ActivatedLightCount;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lights")
    int32 TotalRequiredLights;
};