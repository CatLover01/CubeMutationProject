// Fill out your copyright notice in the Description page of Project Settings.


#include "HowToPlayWidget.h"

#include "NiagaraFunctionLibrary.h"
#include "UE5Coro.h"
#include "CubeMutationProject/Main/Character/MyCharacter.h"
#include "Kismet/GameplayStatics.h"

void UHowToPlayWidget::clickedFunction()
{
	if(hasStarted == false)
	{
		hasStarted = true;
		startButtonClicked();
	}
}

// happens when the HowToPlay button is clicked
UE5Coro::TCoroutine<> UHowToPlayWidget::startButtonClicked()
{
	UGameplayStatics::PlaySound2D(this, timerSound);
	timerText->SetText(FText::FromString("3"));
	co_await UE5Coro::Latent::Seconds(1.0);

	UGameplayStatics::PlaySound2D(this, timerSound);
	timerText->SetText(FText::FromString("2"));
	co_await UE5Coro::Latent::Seconds(1.0);

	UGameplayStatics::PlaySound2D(this, timerSound);
	timerText->SetText(FText::FromString("1"));
	co_await UE5Coro::Latent::Seconds(1.0);

	UGameplayStatics::PlaySound2D(this, beginExplosionSound);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, niagaraSystem, FVector(0));
	if(AMyCharacter* player = Cast<AMyCharacter>( UGameplayStatics::GetPlayerCharacter(this, 0)))
	{
		player->startingNewGame();
		this->SetVisibility(ESlateVisibility::Hidden);
		this->ClearGarbage();
		this->Destruct();
	}
}

void UHowToPlayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	check(IsValid(timerSound));
	check(IsValid(beginExplosionSound));
	check(IsValid(niagaraSystem))
	
}
