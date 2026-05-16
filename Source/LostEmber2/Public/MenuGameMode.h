#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MenuGameMode.generated.h"

UCLASS()
class LOSTEMBER2_API AMenuGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMenuGameMode();

    virtual void BeginPlay() override;

protected:

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UUserWidget> MenuWidgetClass;
    UUserWidget* MenuWidgetInstance;
};