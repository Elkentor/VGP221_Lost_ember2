#include "LostEmberGameMode.h"

ALostEmberGameMode::ALostEmberGameMode()
{
    ActivatedLightCount = 0;
    TotalRequiredLights = 3;
}

void ALostEmberGameMode::RegisterLightActivated()
{
    ActivatedLightCount++;
}