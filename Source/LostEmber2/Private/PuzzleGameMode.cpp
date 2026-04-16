// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleGameMode.h"

void APuzzleGameMode::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	//display a debug message for five seconds. The -1 "Key" value indicates that we will be updating the same message next time we call this function again.
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("PuzzleGameMode StartPlay"));
}