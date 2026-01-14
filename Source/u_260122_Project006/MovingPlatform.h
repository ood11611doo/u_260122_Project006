// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class U_260122_PROJECT006_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	AMovingPlatform();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform Settings")
	float Movespeed = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform Settings")
	float LerpTimer = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Settings")
	bool Pingpong = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Settings")
    float FadeLerpTimer = 0.5f;
	
	UPROPERTY(EditAnywhere, Category = "Position Settings")
	AActor* StartPoint;
	UPROPERTY(EditAnywhere, Category = "Position Settings")
    AActor* EndPoint;

protected:
	virtual void BeginPlay() override;

	void UpdatePlatform();

private:
	FTimerHandle MoveTimerHandle;

	float CurrentAlpha = 0.0f;
    bool MovingForward = true;
    bool IsResetting = false;
    bool IsGrowing = false;
    FVector OriginalScale;
    
    float GetSmoothedAlpha(float Alpha);
};
