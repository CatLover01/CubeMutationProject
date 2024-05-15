// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "CubeMutationProject/Main/SaveGameObject/MySaveGame.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "CubeMutationProject/Main/FunctionLibraries/RandomNumberGeneration/RandomNumberGenerationLibrary.h"
#include "CubeMutationProject/Main/Objects/ObjectToSpawn.h"
#include "EnhancedInputComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "CubeMutationProject/CubeMutationProject.h"
#include "CubeMutationProject/Main/Widgets/ScoreWidget/ScoreWidget.h"
#include "UE5Coro.h"
#include "Internationalization/Text.h"


// --------------------------------- On Construct --------------------------------- //
AMyCharacter::AMyCharacter()
{
	// -- Setting Default Values for Character -- //

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	
	// -- Setting Components -- //
	cubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("MainMesh");
	cameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	followCamera = CreateDefaultSubobject<UCameraComponent>("MainCamera");

	if(cubeMesh != nullptr && cameraBoom != nullptr && followCamera != nullptr)
	{
		SetRootComponent(GetCapsuleComponent());
		cameraBoom->TargetArmLength = 400.f; // Default length
		followCamera->SetupAttachment(cameraBoom); // Follow Camera gets registered here automaticially
		cubeMesh->SetupAttachment(GetRootComponent()); // Attach to the Root
		cameraBoom->SetupAttachment(GetRootComponent()); // Attach to the Root
	}
	
}


// --------------------------------- Begin Play + OnPossessed --------------------------------- //
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(IsValid(saveObjectClass));
	check(!StaticMeshes.IsEmpty());
	check(IsValid(objectToSpawn));
	check(IsValid(clickingAction));
	check(IsValid(restartAction));
	check(IsValid(widgetCircleClass));
	check(IsValid(soundToPlay));
	check(IsValid(widgetScoreClass));
	check(IsValid(mutatingSoundToPlay));
	check(IsValid(particleEffect));

	CubeRotationTimeline();		// Making the cube rotation until the game ends
	
}


void AMyCharacter::Restart()
{
	Super::Restart();
	
	check(mappingContext);
	check(IsValid(widgetResultClass));
	check(IsValid(widgetHowToPlayClass));
	
	// Setting the Mapping Context for movement stuff
	if(APlayerController* playerController = Cast<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* inputSubsystem = playerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			inputSubsystem->AddMappingContext(mappingContext, 0);
		}
		playerController->SetShowMouseCursor(true);
	}
	else
	{
		if(GEngine != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, "Player Controller has failed to load!");
		}
	}

	// Creating the Enter Widget
	widgetHowToPlayObject = CreateWidget<UUserWidget>(GetWorld(), widgetHowToPlayClass);
	if(widgetHowToPlayObject != nullptr)
	{
		widgetHowToPlayObject->AddToViewport();
		qWidget = true;
	}
	
}

// --------------------------- End of stuff that happens at the beginning --------------------------------- //



// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Called after a certain amount of time (tickDelayAmount)
	if(GetWorld()->GetTime().GetRealTimeSeconds() - tickTimerLastDuration >= tickDelayAmount)
	{
		tickTimerLastDuration = GetWorld()->GetTime().GetRealTimeSeconds();
		if(isInGame == true)
		{
			SpawnActorRandomly();
		}
	}

	
	// Making sure that we update the Score every frame for a smooth transition
	if(widgetScoreObject != nullptr)
	{
		widgetScoreObject->scoreTextBlock->SetText(FText::AsNumber(previousScore));
	}
}


void AMyCharacter::SpawnActorRandomly()
{
	
	float floatInRangeY1 = URandomNumberGenerationLibrary::RandomFloatInRange(-450, 450, positionX, 25);
	float floatInRangeZ2 = URandomNumberGenerationLibrary::RandomFloatInRange(-200, 200, positionX + 1, 25);
	float floatInRangeScale = URandomNumberGenerationLibrary::RandomFloatInRange(0.5, 1.8, positionX + 2, 25);
	positionX += 3;
	// Make this save to be able to reload the player with this number to spawn random cubes again


	// Calculating FindLookAtRotation
	FRotator LookAtRot = FRotationMatrix::MakeFromX(followCamera->GetComponentLocation() - FVector(0.f, floatInRangeY1, floatInRangeZ2)).Rotator();
	FVector location(0, floatInRangeY1, floatInRangeZ2);
	FVector scale(floatInRangeScale, floatInRangeScale, floatInRangeScale);
	FTransform transform(LookAtRot, location, scale);
	
	
	FActorSpawnParameters actorParams;
	actorParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
	
	
	// Spawning the mesh and setting the multiplicator variable in the new actor
	if(AObjectToSpawn* newSpawnedActor = GetWorld()->SpawnActor<AObjectToSpawn>(objectToSpawn, transform, actorParams))
	{
		if(newSpawnedActor->currentObject->SetStaticMesh(StaticMeshes[objectStep]))
		{
			newSpawnedActor->Multiplicator = multiplicatorsArray[objectStep];
		}
	}
	
}


// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(clickingAction, ETriggerEvent::Started, this, &AMyCharacter::clickingFunction);
	EnhancedInputComponent->BindAction(restartAction, ETriggerEvent::Started, this, &AMyCharacter::restartFunction, false);
	
}


// ------------------ When the player click on the screen ------------------ //
void AMyCharacter::clickingFunction()
{
	if(widgetCircleObject = CreateWidget(GetWorld(), widgetCircleClass))
	{
		if (APlayerController* playerController = Cast<APlayerController>(GetController()))
		{
			// Setting 2D stuff
			FVector2d mousePosition;
			if (playerController->GetMousePosition(mousePosition.X, mousePosition.Y))
			{
				widgetCircleObject->SetPositionInViewport(mousePosition);
				widgetCircleObject->SetDesiredSizeInViewport(circleWidgetSize);
				widgetCircleObject->SetAlignmentInViewport(FVector2d{0.5, 0.5}); // Anchor to the middle -> DO NOT CHANGE
				widgetCircleObject->AddToViewport();
			}

			// Line Trace in the World
			FVector worldLocation;
			FVector worldDirection;
			if(playerController->DeprojectMousePositionToWorld(worldLocation, worldDirection))
			{
				FHitResult resultTrace;																
				if (GetWorld()->LineTraceSingleByChannel(resultTrace, worldLocation, (worldDirection * distanceLineTrace ) + worldLocation, ClickTrace))
				{
					if(AObjectToSpawn* objectHit = Cast<AObjectToSpawn>(resultTrace.GetActor()))
					{
						DestroyObjectToSpawn(objectHit);
					}
				}
			}
		}
	}
}

void AMyCharacter::DestroyObjectToSpawn(AObjectToSpawn* objectHit)
{
	// Heavy Calculation
	previousScore = score;
	float inBetweenScore = (100 * ownMultiArray[mutate] * objectHit->Multiplicator) * (number / (objectHit->GetActorScale3D().X * number));
	score = score + inBetweenScore;

	if(savedNotScore < score)
	{
		savedNotScore = score;
	}

	if(score > highScore)
	{
		highScore = score;
	}

	// BP Functions
	TextScaleChanger();
	LerpingValues();

	
	// Calculate if we need to change the static mesh and the object variable
	if(score >= arrayNumbersToSwitchMeshes[staticMeshStep])
	{
		mutatingCustom();
		cubeMesh->SetStaticMesh(StaticMeshes[staticMeshStep]);
	}

	if(score >= arrayNumberToSwitchObjects[objectStep])
	{
		objectStep++;
	}

	
	// BP Functions
	SizeChanger();
	objectHit->DestroyActor();
	

	// Cute Click Sound
	UGameplayStatics::PlaySound2D(this, soundToPlay, soundEffectMultiplayer, 1, 0);
}
// ------------------ END of the player click on the screen function ------------------ //


// Handeling mutation
void AMyCharacter::mutatingCustom()
{
	if(widgetScoreObject != nullptr && widgetScoreObject->mutateButton != nullptr)
	{
		widgetScoreObject->mutateButton->SetVisibility(ESlateVisibility::Visible);
	}
}



void AMyCharacter::restartFunction(bool isRestartEvent)
{
	if((isInGame == true || isRestartEvent == true) && GetWorld() != nullptr)
	{
		isInGame = false;
		score = 0.f;
		previousScore = 0.f;
		staticMeshStep = 0;
		objectStep = 0;
		mutate = 0;

		// Setup Result widget
		GetWorld()->GetGameViewport()->RemoveAllViewportWidgets();
		if(widgetResultObject = CreateWidget(GetWorld(), widgetResultClass))
		{
			widgetResultObject->AddToViewport();
		}
		// Cool stuff here
		UGameplayStatics::PlaySound2D(this, mutatingSoundToPlay);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, particleEffect, FVector(0));

		
		TArray<AActor*> actorsFound;
		UGameplayStatics::GetAllActorsOfClass(this, objectToSpawn, actorsFound);
		for(auto actor : actorsFound)
		{
			actor->Destroy();
		}

		cubeMesh->SetStaticMesh(StaticMeshes[0]);
		
		GetWorld()->GetTimerManager().SetTimer(timerSavedScore, this, &AMyCharacter::restartFunctionTimer, 0.2);
	}
}

void AMyCharacter::restartFunctionTimer()
{
	savedNotScore = 0.f;
	GetWorldTimerManager().ClearTimer(timerSavedScore);
}


// ------------------ Coroutines Stuff ------------------ //
UE5Coro::TCoroutine<> AMyCharacter::TextScaleChanger()
{
	if(widgetScoreObject != nullptr)
	{
		for(int i{0}; i < 11; i++)
		{
			ActualChangeTextScale(81.0);
			co_await UE5Coro::Latent::Seconds(URandomNumberGenerationLibrary::RandomFloatInRange(0.03, 0.08, positionTextScaling, 40));
			positionTextScaling++;
			
			ActualChangeTextScale(75.0);
			co_await UE5Coro::Latent::Seconds(URandomNumberGenerationLibrary::RandomFloatInRange(0.03, 0.08, positionTextScaling, 40));
			positionTextScaling++;
		}
	}
	
}

void AMyCharacter::ActualChangeTextScale(float size)
{
	FSlateFontInfo fontInfo = widgetScoreObject->scoreTextBlock->GetFont();
    	fontInfo.Size = size;
    	widgetScoreObject->scoreTextBlock->SetFont(fontInfo);
}

// ------------------ End coroutine stuff ------------------ //



void AMyCharacter::spawningWidget()
{
	cubeMesh->SetStaticMesh(StaticMeshes[mutate]);
}

void AMyCharacter::PlaySoundEffect()
{
	UGameplayStatics::PlaySound2D(this, mutatingSoundToPlay, soundEffectMultiplayer);
}

void AMyCharacter::startingNewGame()
 {
	isInGame = true;

	if(widgetScoreObject = CreateWidget<UScoreWidget>(GetWorld(), widgetScoreClass))
	{
		widgetScoreObject->AddToViewport();
	}
 }
