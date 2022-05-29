// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerActor.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <Runtime/Engine/Classes/GameFramework/PlayerController.h>

// Sets default values
APlayerActor::APlayerActor()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	player = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("player"));
	camera_component = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
}

// Called when the game starts or when spawned
void APlayerActor::BeginPlay()
{
	Super::BeginPlay(); 

	//GetWorld()->SpawnActor<APlayerActor>(this->player_class, FVector(0.0f, 0.0f, 50.0f), FRotator(0.0f, 0.0f, 0.0f));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "Yes");
}

// Called every frame
void APlayerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!this->move_distance.IsZero())
	{
		SetActorLocation(GetActorLocation() + this->move_distance);
	}
	float mousex, mousey;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(mousex, mousey);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("r: %f  c: %f"), mousex, mousey));
}

// Called to bind functionality to input
void APlayerActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("mouse_x", this, &APlayerActor::move_x);
	PlayerInputComponent->BindAxis("moude_y", this, &APlayerActor::move_y);
}

void APlayerActor::move_x(float value)
{
	this->move_distance.X = value;
}

void APlayerActor::move_y(float value)
{
	this->move_distance.Y = value;
}
