// Fill out your copyright notice in the Description page of Project Settings.


#include "chess_character.h"

#include "Components/SkeletalMeshComponent.h"
#include "Animation/Animinstance.h"

// Sets default values
Achess_character::Achess_character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//this->chess = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("chess"));
	this->is_black = false;
}

void Achess_character::set_is_black(bool val)
{
	this->is_black = val;
	return;
}

void Achess_character::flip()
{
	if (this->is_black)
		this->set_is_black(false);
	else
		this->set_is_black(true);
	return;
}

//void Achess_character::reverse()
//{
//	//UAnimInstance* instance = this->chess->GetAnimInstance();
//	UAnimInstance* instance = GetMesh()->GetAnimInstance();
//	if (!instance->Montage_IsPlaying(this->mg_chess))
//	{
//		if (this->is_black)
//		{
//			instance->Montage_Play(this->mg_chess);
//			instance->Montage_JumpToSection(FName("flip_to_white"), this->mg_chess);
//		}
//		else
//		{
//			instance->Montage_Play(this->mg_chess);
//			instance->Montage_JumpToSection(FName("flip_to_black"), this->mg_chess);
//		}
//		//this->flip();
//	}
//	return;
//}

void Achess_character::reverse()
{
	
}

// Called when the game starts or when spawned
void Achess_character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Achess_character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void Achess_character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

