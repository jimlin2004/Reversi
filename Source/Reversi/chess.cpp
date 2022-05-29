// Fill out your copyright notice in the Description page of Project Settings.


#include "chess.h"
#include "Misc/OutputDeviceNull.h"
#include "checkerboard.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
Achess::Achess()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->chess = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("chess"));
	//this->chess = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("chess"));
	this->set_is_black(false);
	this->is_flipping = false;
}

void Achess::set_is_black(bool val)
{
	this->is_black = val;
	return;
}

void Achess::flip()
{
	if (this->is_black)
		this->set_is_black(false);
	else
		this->set_is_black(true);
	return;
}

void Achess::reverse()
{
	if (!this->is_flipping)
	{
		this->is_flipping = true;
		FOutputDeviceNull ar;
		this->CallFunctionByNameWithArguments(TEXT("reverse"), ar, NULL, true);
		this->flip();
		return;
	}
}

void Achess::show_outline()
{
	this->chess->SetRenderCustomDepth(true);
	return;
}

void Achess::close_outline()
{
	this->chess->SetRenderCustomDepth(false);
	return;
}

// Called when the game starts or when spawned
void Achess::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> found_actor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), Acheckerboard::StaticClass(), found_actor);
	if (found_actor.Num() == 0)
		return;
	this->board = Cast<Acheckerboard>(found_actor[0]);
	this->chess->SetCustomDepthStencilValue(1);
}

// Called every frame
void Achess::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

