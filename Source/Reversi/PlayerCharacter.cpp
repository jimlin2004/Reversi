// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "camera_actor.h"
#include "checkerboard.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	camera_fristperson_location = CreateDefaultSubobject<UArrowComponent>(TEXT("CameraRShoulderLocation"));
	camera_godview_location = CreateDefaultSubobject<UArrowComponent>(TEXT("CameraOriginLocation"));
	camera_comp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	hand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("hand"));
	camera_fristperson_location->SetupAttachment(GetMesh());
	camera_godview_location->SetupAttachment(GetMesh());
	camera_comp->SetupAttachment(GetMesh());
	hand->SetupAttachment(GetMesh());
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	this->playercontroller = UGameplayStatics::GetPlayerController(this, 0);
	//初始化鏡頭
	/*camera_comp->SetWorldLocation(FVector(0, 0, 2000));
	camera_comp->SetWorldRotation(FRotator(270, 0, 0));
	camera_comp->SetRelativeLocation(camera_fristperson_location->GetRelativeLocation());
	camera_comp->SetWorldRotation(FRotator(0, 180, 0));*/
	this->switch_camera();
	this->mouse_pos.Z = 470.0f;
	GEngine->GameViewport->GetViewportSize(this->viewport_size);
	this->viewport_size.X = this->viewport_size.X / 2;
	this->viewport_size.Y = this->viewport_size.Y / 2;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!this->move_direction.IsZero())
	{
		SetActorLocation(GetActorLocation() + this->move_direction);
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("switch_camera", IE_Pressed, this, &APlayerCharacter::switch_camera);
	PlayerInputComponent->BindAxis("mouse_x", this, &APlayerCharacter::mouse_y);
	PlayerInputComponent->BindAxis("mouse_y", this, &APlayerCharacter::mouse_x);
	PlayerInputComponent->BindAction("lock_mouse_pos", IE_Pressed, this, &APlayerCharacter::lock_mouse_pos);
	PlayerInputComponent->BindAction("place_chess", IE_Pressed, this, &APlayerCharacter::place_chess);
}

//-------------------以下為輸入動作(input)-------------------------

void APlayerCharacter::switch_camera()
{
	TArray<AActor*> found_actor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), Acamera_actor::StaticClass(), found_actor);
	if (found_actor.Num() == 0)
		return ;
	else
	{
		if (this->is_frist_person)
		{
			this->is_frist_person = false;
			this->playercontroller->SetViewTarget(found_actor[0]);
		}
		else
		{
			this->is_frist_person = true;
			this->playercontroller->SetViewTarget(this);
		}
	}
}

void APlayerCharacter::lock_mouse_pos()
{
	this->playercontroller->SetMouseLocation(this->viewport_size.X, this->viewport_size.Y);
}

void APlayerCharacter::mouse_x(float val)
{
	this->move_direction.X = val * 20;
}

void APlayerCharacter::mouse_y(float val)
{
	this->move_direction.Y = val * 20;
}

void APlayerCharacter::place_chess()
{
	TArray<AActor*> found_board;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), Acheckerboard::StaticClass(), found_board);
	Acheckerboard* board_check = Cast<Acheckerboard>(found_board[0]);
	if (board_check != nullptr && found_board.Num() != 0)
	{
		board_check->place_chess(GetActorLocation());
	}
	//FVector v = GetActorLocation();
}
