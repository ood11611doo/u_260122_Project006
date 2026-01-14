// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpinningPlatform.generated.h"

UENUM(BlueprintType)
enum class ERotationAxis : uint8
{
	XAxis	UMETA(DisplayName = "X Axis"),
	YAxis	UMETA(DisplayName = "Y Axis"),
	ZAxis	UMETA(DisplayName = "Z Axis")
};

UCLASS()
class U_260122_PROJECT006_API ASpinningPlatform : public AActor
{
	GENERATED_BODY()
	
public:
	ASpinningPlatform();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform Settings")
	float Spinspeed = 180.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform Settings")
    ERotationAxis RotationAxis = ERotationAxis::ZAxis;
	
protected:
	virtual void BeginPlay() override;

    void UpdateRotation();
private:
	FTimerHandle RotationTimerHandle;
};
