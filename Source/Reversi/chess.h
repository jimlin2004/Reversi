// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "checkerboard.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "chess.generated.h"

UCLASS()
class REVERSI_API Achess : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Achess();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "chess")
		UStaticMeshComponent* chess;
		//USkeletalMeshComponent* chess;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "board")
		Acheckerboard* board;

	void reverse();
	void set_is_black(bool val);
	void show_outline();
	void close_outline();

	UFUNCTION(BlueprintCallable)
		void flip();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool is_black;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool is_flipping;
};
