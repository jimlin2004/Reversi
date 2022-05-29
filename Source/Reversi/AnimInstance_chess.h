// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstance_chess.generated.h"

/**
 * 
 */
UCLASS()
class REVERSI_API UAnimInstance_chess : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
		void init();
	UFUNCTION(BlueprintCallable)
		void flip();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class Achess_character* chess;
		//class Achess* chess;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool is_black;
};
