// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class REVERSI_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UCameraComponent* camera_comp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UCameraComponent* god_camera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UArrowComponent* camera_fristperson_location;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UArrowComponent* camera_godview_location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ACameraActor> camera_class;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ACamera_actor> camera_actor_class;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "hand")
		USkeletalMeshComponent* hand;
	void switch_camera();
	void lock_mouse_pos();
	void mouse_x(float val);
	void mouse_y(float val);
	void place_chess();
	APlayerController* playercontroller;
	FVector move_direction;
	bool is_frist_person = true;
	FVector mouse_pos;
	FVector2D viewport_size;
};
