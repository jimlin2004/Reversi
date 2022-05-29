// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance_chess.h"
#include "chess_character.h"
//#include "chess.h"

void UAnimInstance_chess::init()
{
	//this->chess = Cast<Achess>(GetOwningActor());
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("init"));
	this->chess = Cast<Achess_character>(TryGetPawnOwner());
	if (this->chess)
		this->is_black = this->chess->is_black;
	return;
}

void UAnimInstance_chess::flip()
{
	this->chess->flip();
	return;
}