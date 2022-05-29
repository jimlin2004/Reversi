// Fill out your copyright notice in the Description page of Project Settings.


#include "Hint_actor.h"

// Sets default values
AHint_actor::AHint_actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	hint_actor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("hint_actor"));
}

// Called when the game starts or when spawned
void AHint_actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHint_actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

