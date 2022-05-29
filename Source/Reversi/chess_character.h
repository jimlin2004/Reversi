// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "chess_character.generated.h"

UCLASS()
class REVERSI_API Achess_character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	Achess_character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "chess")
		USkeletalMeshComponent* chess;*/

	void reverse();
	void set_is_black(bool val);

	UFUNCTION(BlueprintCallable)
		void flip();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool is_black;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UAnimMontage* mg_chess;
};
