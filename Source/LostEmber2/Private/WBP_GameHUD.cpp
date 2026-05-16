#include "WBP_GameHUD.h"
#include "LostEmberGameMode.h"
#include "Kismet/GameplayStatics.h"

float UWBP_GameHUD::GetTimerPercent() const
{
    ALostEmberGameMode* GM = Cast<ALostEmberGameMode>(UGameplayStatics::GetGameMode(this));
    if (!GM) return 0.0f;

    return GM->GetCurrentTime() / GM->GetMaxTime();
}

FText UWBP_GameHUD::GetTimerText() const
{
    ALostEmberGameMode* GM = Cast<ALostEmberGameMode>(UGameplayStatics::GetGameMode(this));
    if (!GM) return FText::FromString("0:00");

    int Time = GM->GetCurrentTime();
    int Minutes = Time / 60;
    int Seconds = Time % 60;

    FString Text = FString::Printf(TEXT("%d:%02d"), Minutes, Seconds);
    return FText::FromString(Text);
}

FText UWBP_GameHUD::GetLightProgressText() const
{
    ALostEmberGameMode* GM = Cast<ALostEmberGameMode>(UGameplayStatics::GetGameMode(this));
    if (!GM) return FText::FromString("0 / 3");

    FString Text = FString::Printf(TEXT("%d / %d"),
        GM->GetActivatedLightCount(),
        GM->GetTotalRequiredLights()
    );

    return FText::FromString(Text);
}