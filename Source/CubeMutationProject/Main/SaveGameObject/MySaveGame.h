// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class UMySaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	float musicVolume = 0.f;

	UPROPERTY()
	float soundEffectVolume = 0.f;

	UPROPERTY()
	float highScore = 0.f;

	UPROPERTY()
	bool isFirstTimeJoining = false;

	UPROPERTY(EditAnywhere)
	FString playerName = "None";

	UPROPERTY()
	FString randomIDGuest = "";
	
};
