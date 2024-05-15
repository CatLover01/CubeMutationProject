// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NiagaraSystem.h"
#include "UE5Coro.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "HowToPlayWidget.generated.h"

/**
 * 
 */
UCLASS()
class CUBEMUTATIONPROJECT_API UHowToPlayWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> timerText = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> timerSound = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> beginExplosionSound = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> niagaraSystem = nullptr;
	
	bool hasStarted = false;


	
	UFUNCTION(BlueprintCallable)
	void clickedFunction();
	UE5Coro::TCoroutine<> startButtonClicked();

	virtual void NativeConstruct() override;
};
