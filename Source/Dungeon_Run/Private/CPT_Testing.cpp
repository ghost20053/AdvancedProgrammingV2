// Fill out your copyright notice in the Description page of Project Settings.


#include "CPT_Testing.h"

// Sets default values
ACPT_Testing::ACPT_Testing()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPT_Testing::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("TEsting C++"));
}

// Called every frame
void ACPT_Testing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

