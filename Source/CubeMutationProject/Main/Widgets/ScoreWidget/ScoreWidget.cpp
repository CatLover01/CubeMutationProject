// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"

#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "CubeMutationProject/Main/Character/MyCharacter.h"
#include "UE5Coro.h"
#include "Components/Button.h"

// Called on creating the widget
void UScoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	check(particleEffect);

	// Adding the custom implemented event to be called when the button is clicked
	if(mutateButton != nullptr)
	{
		mutateButton->OnClicked.AddUniqueDynamic(this, &UScoreWidget::clickFunction);
	}
	
}



void UScoreWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	
	
	// Running ONCE every 1 second
	if(hasStartedAsync == false)
	{
		tickTimer1();
		hasStartedAsync = true;
	}
}

UE5Coro::TCoroutine<> UScoreWidget::tickTimer1()
{
	co_await UE5Coro::Latent::Seconds(1.0);
	
	if(isWorking == true)
	{
		seconds -= 1;
		if(seconds < 0)
		{
			minutes -= 1;
			seconds = 59;
		}

		if(!(minutes == 0 && seconds == 0))
		{
			AddText();
		}
		else
		{
			AddText();
			isWorking = false;

			co_await UE5Coro::Latent::Seconds(0.2); // Small delay for the final scene!
			
			if(AMyCharacter* playerCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
			{
            		playerCharacter->isInGame = false;
            		playerCharacter->restartFunction(true);
			}
		}
		
		hasStartedAsync = false;
	}
}
