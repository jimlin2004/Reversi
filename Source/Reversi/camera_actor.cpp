// Fill out your copyright notice in the Description page of Project Settings.

#include "camera_actor.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
Acamera_actor::Acamera_actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	camera_comp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	camera_comp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void Acamera_actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Acamera_actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

