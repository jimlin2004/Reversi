// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "camera_actor.generated.h"

UCLASS()
class REVERSI_API Acamera_actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Acamera_actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UCameraComponent* camera_comp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "camera")
		TSubclassOf<class ACameraActor> camera_class;
};
