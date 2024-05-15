// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UE5Coro/Coroutine.h"
#include "ScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class CUBEMUTATIONPROJECT_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool check = true;
	
	bool isWorking = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 seconds = 15;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 minutes = 2;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* particleEffect = nullptr;

	bool hasStartedAsync = false;
	
public:
	// BINDING widgets here
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* scoreTextBlock = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* mutateButton = nullptr;

	
public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	UE5Coro::TCoroutine<> tickTimer1();
	
	virtual void NativeConstruct() override; 
	
	UFUNCTION(BlueprintImplementableEvent)
	void AddText();

	UFUNCTION(BlueprintImplementableEvent)
	void clickFunction();
};
