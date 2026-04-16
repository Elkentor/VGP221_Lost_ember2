// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PuzzleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class LOSTEMBER2_API APuzzleGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	virtual void StartPlay() override;
};
