#include "SpinningPlatform.h"
#include "TimerManager.h"

ASpinningPlatform::ASpinningPlatform()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ASpinningPlatform::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(
        RotationTimerHandle, 
        this, 
        &ASpinningPlatform::UpdateRotation, 
        0.01f, 
        true
    );
}

void ASpinningPlatform::UpdateRotation()
{
    float RotationAmount = Spinspeed * 0.01f;
    FRotator NewRotation = FRotator::ZeroRotator;

    switch (RotationAxis)
    {
        case ERotationAxis::XAxis:
            NewRotation.Roll = RotationAmount;
            break;
        case ERotationAxis::YAxis:
            NewRotation.Pitch = RotationAmount;
            break;
        case ERotationAxis::ZAxis:
            NewRotation.Yaw = RotationAmount;
            break;
    }

    AddActorLocalRotation(NewRotation);
}