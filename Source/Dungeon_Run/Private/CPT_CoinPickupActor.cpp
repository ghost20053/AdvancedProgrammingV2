// Fill out your copyright notice in the Description page of Project Settings.


#include "CPT_CoinPickupActor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Kismet/GameplayStatics.h"

#include "C:\Program Files\Epic Games\UE_5.4\Engine\Plugins\FX\Niagara\Source\Niagara\Public\NiagaraFunctionLibrary.h"

// Sets default values
ACPT_CoinPickupActor::ACPT_CoinPickupActor()
{
	//Setting Up collider
	ColliderComponent = CreateDefaultSubobject<USphereComponent>("ColliderComponent");
	SetRootComponent(ColliderComponent);
	ColliderComponent->SetGenerateOverlapEvents(true);
	ColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	ColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ColliderComponent->OnComponentBeginOverlap.AddDynamic(
		this, &ACPT_CoinPickupActor::OnBeginOverlapComponentEvent
	);
	//Setting Static Mesh
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	MeshComponent->SetupAttachment(ColliderComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeshComponent->SetGenerateOverlapEvents(false);

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>("RotatingMovementComponent");
}

void ACPT_CoinPickupActor::OnBeginOverlapComponentEvent(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult
)
{
	if (!Cast<ACharacter>(OtherActor)) return;
	//Adding Sound Component
	if (PickSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this, PickSound, GetActorLocation(), VolumeMultiplier);
	}
	//Adding VFX Component
	if (OnPickupEffect)
	{
		const FVector Offset = GetActorUpVector() * PickEffectSpawnOffset;
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			this, OnPickupEffect, OtherActor->GetActorLocation() + Offset);
	}

	Destroy();
}
