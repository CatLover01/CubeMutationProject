// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectToSpawn.generated.h"

UCLASS()
class CUBEMUTATIONPROJECT_API AObjectToSpawn : public AActor
{
	GENERATED_BODY()

public:
	// -- Components -- //
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* currentObject = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USceneComponent* defaultSceneRoot = nullptr;

	UPROPERTY(BlueprintReadOnly) // Edit Anywhere?
	class UMaterialInstanceDynamic* dynamicMaterial = nullptr;

	UPROPERTY(EditAnywhere)
	UMaterialInstance* sourceMaterial = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Scale = 0.f;
	
	int32 Multiplicator = 1;

	
public:	
	// Sets default values for this actor's properties
	AObjectToSpawn();
	virtual void OnConstruction(const FTransform& Transform) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void DestroyActor();
};
