// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance_chess_black_top.h"

void UAnimInstance_chess_black_top::init()
{
	this->chess = Cast<Achess>(GetOwningActor());
	if (this->chess)
		this->is_black = this->chess->is_black;
	return;
}

void UAnimInstance_chess_black_top::flip()
{
	this->chess->flip();
	return;
}