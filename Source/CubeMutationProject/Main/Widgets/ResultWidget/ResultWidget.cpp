// Fill out your copyright notice in the Description page of Project Settings.


#include "ResultWidget.h"

#include "CubeMutationProject/Main/Widgets/HowToPlayWidget/HowToPlayWidget.h"

void UResultWidget::RestartButton()
{
	MenuButton(true);
}

void UResultWidget::MenuButton(bool isRestart)
{
	if(howToPlayWidget != nullptr)
	{
		if(UHowToPlayWidget* widget = CreateWidget<UHowToPlayWidget>(GetWorld(), howToPlayWidget))
		{
			widget->AddToViewport();

			if(isRestart == true)
			{
				widget->clickedFunction(); // making sure we start the countdown instantly OnRestart (re-Play the game)
			}
			
			this->SetVisibility(ESlateVisibility::Hidden);
			this->ClearGarbage();
			this->Destruct();
		}
	}
}
