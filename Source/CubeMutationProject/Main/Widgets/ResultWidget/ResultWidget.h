// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ResultWidget.generated.h"

class UHowToPlayWidget;
/**
 * 
 */
UCLASS()
class CUBEMUTATIONPROJECT_API UResultWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void RestartButton();
	
	UFUNCTION(BlueprintCallable)
	void MenuButton(bool isRestart = false);

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> howToPlayWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* scoreText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* highscoreText = nullptr;
	
};
