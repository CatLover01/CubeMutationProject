// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RandomNumberGenerationLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CUBEMUTATIONPROJECT_API URandomNumberGenerationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static const unsigned int RandomNumber( int positionX,  unsigned int seed);
	static const int RandomNumberInRange( int min,  int max,  int positionX,  unsigned int seed);
	static const float RandomFloat(int positionX, unsigned int seed);
	static const float RandomFloatInRange(float min, float max, int positionX, unsigned int seed);
};
