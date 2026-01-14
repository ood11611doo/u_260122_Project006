#include "MovingPlatform.h"
#include "TimerManager.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AMovingPlatform::BeginPlay()
{
    Super::BeginPlay();
    OriginalScale = GetActorScale3D();

    GetWorldTimerManager().SetTimer(MoveTimerHandle, this, &AMovingPlatform::UpdatePlatform, 0.01f, true);
}

void AMovingPlatform::UpdatePlatform()
{
    if (!StartPoint || !EndPoint) return;

    float DeltaTime = 0.01f; 
    FVector StartPos = StartPoint->GetActorLocation();
    FVector EndPos = EndPoint->GetActorLocation();
    
    float Distance = FVector::Dist(StartPos, EndPos);
    
    if (Distance <= 0.0f) return;

    float AlphaChange = (Movespeed / Distance) * DeltaTime;

    if (!IsResetting)
    {
        if (MovingForward) 
            CurrentAlpha += AlphaChange;
        else 
            CurrentAlpha -= AlphaChange;

        CurrentAlpha = FMath::Clamp(CurrentAlpha, 0.0f, 1.0f);

        float SmoothedAlpha = FMath::InterpEaseInOut(0.0f, 1.0f, CurrentAlpha, 2.0f);
        FVector NewLocation = FMath::Lerp(StartPos, EndPos, SmoothedAlpha);
        
        SetActorLocation(NewLocation);

        if (CurrentAlpha >= 1.0f)
        {
            if (Pingpong) MovingForward = false;
            else IsResetting = true;
        }
        else if (CurrentAlpha <= 0.0f)
        {
            if (Pingpong) MovingForward = true;
        }
    }
    else
    {
        if (!IsGrowing)
        {
            FVector TargetScale = FVector::ZeroVector;
            FVector NewScale = FMath::VInterpTo(GetActorScale3D(), TargetScale, DeltaTime, 10.0f);
            SetActorScale3D(NewScale);

            if (NewScale.Size() < 0.05f)
            {
                SetActorLocation(StartPos);
                CurrentAlpha = 0.0f;
                IsGrowing = true; 
            }
        }
        else
        {
            FVector NewScale = FMath::VInterpTo(GetActorScale3D(), OriginalScale, DeltaTime, 10.0f);
            SetActorScale3D(NewScale);

            if (FVector::Dist(NewScale, OriginalScale) < 0.05f)
            {
                SetActorScale3D(OriginalScale);
                IsGrowing = false;
                IsResetting = false;
                MovingForward = true;
            }
        }
    }
}


