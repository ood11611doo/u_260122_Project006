// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

UCLASS()
class U_260122_PROJECT006_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn objects")
    TSubclassOf<AActor> MovingObj;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn objects")
    TSubclassOf<AActor> SpinningObj;
	
	UPROPERTY(EditAnywhere, Category = "Spawn - Moving setting")
	float MovespeedMin = 150.0f;
	UPROPERTY(EditAnywhere, Category = "Spawn - Moving setting")
    float MovespeedMax = 300.f;

	UPROPERTY(EditAnywhere, Category = "Spawn - Spin setting")
    float SpinspeedMin = 50.0f;
    UPROPERTY(EditAnywhere, Category = "Spawn - Spin setting")
    float SpinspeedMax = 100.f;
	
	UPROPERTY(EditAnywhere, Category = "Spawn Locations")
    int MoveSpawnCount = 3;
	UPROPERTY(EditAnywhere, Category = "Spawn Locations")
    int SpinSpawnCount = 2;
	UPROPERTY(EditAnywhere, Category = "Spawn Locations")
    TArray<AActor*> SpawnMoves;
	UPROPERTY(EditAnywhere, Category = "Spawn Locations")
    TArray<AActor*> SpawnSpins;

protected:
	virtual void BeginPlay() override;
};
