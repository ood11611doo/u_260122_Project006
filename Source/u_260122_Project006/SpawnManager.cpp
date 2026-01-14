#include "SpawnManager.h"
#include "MovingPlatform.h"
#include "SpinningPlatform.h"
#include "Engine/World.h"
#include "Algo/RandomShuffle.h"

ASpawnManager::ASpawnManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();

	if (MovingObj && SpawnMoves.Num() >= 2)
	{
		TArray<AActor*> ShuffledLocations = SpawnMoves;
		Algo::RandomShuffle(ShuffledLocations);

		int32 ActualSpawnCount = FMath::Min(MoveSpawnCount, ShuffledLocations.Num());

		for (int32 i = 0; i < ActualSpawnCount; i++)
		{
			AActor* SelectedSpawnPoint = ShuffledLocations[i];
			
			FVector Location = SelectedSpawnPoint->GetActorLocation();
			FRotator Rotation = SelectedSpawnPoint->GetActorRotation();

			AMovingPlatform* NewPlatform = GetWorld()->SpawnActor<AMovingPlatform>(MovingObj, Location, Rotation);
			
			if (NewPlatform)
			{
				NewPlatform->Movespeed = FMath::RandRange(MovespeedMin, MovespeedMax);
				NewPlatform->Pingpong = FMath::RandBool();

				NewPlatform->StartPoint = SelectedSpawnPoint;

				AActor* RandomEnd;
				do {
					int32 RandomIdx = FMath::RandRange(0, SpawnMoves.Num() - 1);
					RandomEnd = SpawnMoves[RandomIdx];
				} while (RandomEnd == SelectedSpawnPoint);

				NewPlatform->EndPoint = RandomEnd;
			}
		}
	}

	if (SpinningObj && SpawnSpins.Num() > 0)
	{
		TArray<AActor*> ShuffledSpinLocations = SpawnSpins;
		Algo::RandomShuffle(ShuffledSpinLocations);

		int32 ActualSpinCount = FMath::Min(SpinSpawnCount, ShuffledSpinLocations.Num());

		for (int32 i = 0; i < ActualSpinCount; i++)
		{
			AActor* SelectedSpawnPoint = ShuffledSpinLocations[i];

			FVector Location = SelectedSpawnPoint->GetActorLocation();
			FRotator Rotation = SelectedSpawnPoint->GetActorRotation();

			ASpinningPlatform* NewSpinPlatform = GetWorld()->SpawnActor<ASpinningPlatform>(SpinningObj, Location, Rotation);

			if (NewSpinPlatform)
			{
				NewSpinPlatform->Spinspeed = FMath::RandRange(SpinspeedMin, SpinspeedMax);
                bool InvertSpin = FMath::RandBool();
                if (InvertSpin)
				{
					NewSpinPlatform->Spinspeed *= -1.f;
                }
				
				// Axis randomize disabled currently
				// uint8 RandomAxis = FMath::RandRange(0, 2);
				// NewSpinPlatform->RotationAxis = static_cast<ERotationAxis>(RandomAxis);
			}
		}
	}
}