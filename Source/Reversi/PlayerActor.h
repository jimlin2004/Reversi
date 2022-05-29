// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Camera/CameraComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerActor.generated.h"

UCLASS()
class REVERSI_API APlayerActor : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "player")
		UStaticMeshComponent* player;
	UPROPERTY(EditAnywhere, Category = "player")
		TSubclassOf<class APlayerActor> player_class;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* camera_component;

private:
	FVector move_distance;
	UFUNCTION()
		void move_x(float value);
	UFUNCTION()
		void move_y(float value);
};

