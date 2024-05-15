// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectToSpawn.h"

// Sets default values
AObjectToSpawn::AObjectToSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	currentObject = CreateDefaultSubobject<UStaticMeshComponent>("CurrentObject");
	defaultSceneRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	
	if(currentObject && defaultSceneRoot != nullptr)
	{
		SetRootComponent(defaultSceneRoot);
		currentObject->SetupAttachment(defaultSceneRoot);
	}
	
}


void AObjectToSpawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	if(sourceMaterial != nullptr)
	{
		dynamicMaterial = currentObject->CreateDynamicMaterialInstance(0, sourceMaterial);
	}
	
}


// Called when the game starts or when spawned
void AObjectToSpawn::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void AObjectToSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

