// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "UE5Coro/Coroutine.h"
#include "MyCharacter.generated.h"



UCLASS()
class CUBEMUTATIONPROJECT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()
	
	// DO NOT CHANGE
	float tickTimerLastDuration = 0.f;
	float tickDelayAmount = 0.04f;
	int positionX = 0;
	float distanceLineTrace = 5000.f; // just making sure it's big enough
	
	FVector2d circleWidgetSize{80.0, 80.0};
	
	float number = 2.f;
	
	
	TArray<int32> arrayNumbersToSwitchMeshes{1600, 4000, 18000, 42000, 82000, 145000, 240000,
		370000, 650000, 1100000, 1750000, 2800000, 4500000, 7500000, 11500000, 100000000};

	TArray<int32> arrayNumberToSwitchObjects{2000, 5000, 20000, 52000, 95000, 160000, 250000,
		390000, 670000, 1200000, 1800000, 2900000, 4800000, 7900000, 12000000, 100000000};
	
	TArray<int16> multiplicatorsArray{1, 2, 3, 5, 8, 12, 16, 22, 32, 46, 64, 85, 105, 135, 180, 250};

	TArray<int16> ownMultiArray{1, 2, 3, 5, 8, 12, 16, 22, 32, 46, 64, 90, 115, 150, 200, 280};

protected:
	UPROPERTY(BlueprintReadOnly)
	FVector defaultScale{0.5775, 0.5775, 0.5775};

protected:
	UPROPERTY(BlueprintReadOnly)
	FRotator defaultRotator{250.0, 70.0, 110.0};

private:
	bool Values = false;
public:
	bool isInGame = false;
private:
	bool qWidget = false;
	bool firstTimeInGame = false;
	float newCValueStick = 1.0f;


	// -- Class and Object References -- //
	UPROPERTY(EditAnywhere, Category = "SaveGameObject")
	TSubclassOf<class UMySaveGame> saveObjectClass = nullptr;
	// TObjectPtr<EnterWidget> EnterWidgetRef = nullptr
	// TObjectPtr<CircleWidget> CircleWidget = nullptr 
	// TObjectPtr<WDGScore> widgetScore = nullptr;
	// TObjectPtr<ObjectToSpawm> objectToSpawn = nullptr;

	
protected:
	// -- Actors -- //
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> objectToSpawn = nullptr;

	UPROPERTY(EditAnywhere)
	TArray<class UStaticMesh*> StaticMeshes = {};
			// ** Check if the size of the array is 0, kinda like a nullptr check **

	
	// -- Components -- //
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sounds")
	USoundBase* soundToPlay = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sounds")
	USoundBase* mutatingSoundToPlay = nullptr;
	
	// -- Widgets -- //
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> widgetResultClass = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UUserWidget> widgetResultObject = nullptr;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> widgetHowToPlayClass = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UUserWidget> widgetHowToPlayObject = nullptr;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> widgetCircleClass = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UUserWidget> widgetCircleObject = nullptr;

	// Not Accesible
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UScoreWidget> widgetScoreClass = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<class UScoreWidget> widgetScoreObject = nullptr;

	int positionTextScaling = 0;
	// Not Accesible

	
	// -- Components -- //
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class UStaticMeshComponent> cubeMesh = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Components")
	TObjectPtr<class USpringArmComponent> cameraBoom = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Components")
	TObjectPtr<class UCameraComponent> followCamera = nullptr;


	// -- Input Action or Input Mapping Context -- //
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputMappingContext> mappingContext = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> clickingAction = nullptr;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> restartAction = nullptr;


	// -- Variables -- //
	UPROPERTY(EditAnywhere)
	FString playerName = "";

	UPROPERTY(EditAnywhere)
	FString IDGuest = "";

	UPROPERTY(EditAnywhere)
	FString publicUid = "";

	UPROPERTY()
	FString slotName = "MyCustomSlot1";

	UPROPERTY(BlueprintReadWrite)
	float score = 0.f;
	
	UPROPERTY(BlueprintReadWrite)
	float previousScore = 0.f;

	UPROPERTY(BlueprintReadOnly)
	float soundEffectMultiplayer = 1.0f;

	UPROPERTY(BlueprintReadWrite)
	int32 mutate = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 staticMeshStep = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 objectStep = 0;

	UPROPERTY(BlueprintReadWrite)
	float highScore = 0.f;

	UPROPERTY(BlueprintReadWrite)
	float savedNotScore = 0.f;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* particleEffect = nullptr;
	
	
	// Custom Timer for setting the Saved Score to 0
	FTimerHandle timerSavedScore;
	
public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual  void Restart() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void SpawnActorRandomly();
	void DestroyObjectToSpawn(class AObjectToSpawn* objectHit);

public:
	// Functions for Action Binding
	void clickingFunction();
	void restartFunction(bool isRestartEvent);
	void restartFunctionTimer();

	void mutatingCustom();
	
	UE5Coro::TCoroutine<> TextScaleChanger();
	void ActualChangeTextScale(float size);

	void startingNewGame();
	
protected:
	// ImplementableEvent made in BP
	
	UFUNCTION(BlueprintImplementableEvent)
	void CubeRotationTimeline();

	UFUNCTION(BlueprintImplementableEvent)
	void LerpingValues();

	UFUNCTION(BlueprintImplementableEvent)
	void SizeChanger();

	UFUNCTION(BlueprintCallable)
	void spawningWidget();

	UFUNCTION(BlueprintCallable)
	void PlaySoundEffect();
};