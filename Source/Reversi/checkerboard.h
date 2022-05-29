// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/TextRenderComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "checkerboard.generated.h"



UCLASS()
class REVERSI_API Acheckerboard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Acheckerboard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "checkboard")
		UStaticMeshComponent* checkboard;
	UPROPERTY(EditAnywhere, Category = "chess")
		TSubclassOf<class Achess> chess_class;
	//UPROPERTY(EditAnywhere, Category = "chess")
	//	TSubclassOf<class Achess_character> chess_ch_class;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAudioComponent* sound_effect_component;
	UPROPERTY(EditAnywhere, Category = "hint_actor")
		TSubclassOf<class AHint_actor> hint_class;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo_render")
		UTextRenderComponent* combo_render;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "fire_component_1")
		UParticleSystemComponent* fire_component_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "fire_component_2")
		UParticleSystemComponent* fire_component_2;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "black_num")
		int black_num;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "white_num")
		int white_num;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "turn")
		bool is_black_round;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "status")
		bool is_running;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "combo")
		int combo;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "reverse_num")
		int reverse_num;

	void init_board();
	void hint();
	void clear_hint();
	std::pair<int*, int*> check_position(float x, float y);
	void place_chess(FVector location);
	void if_in_a_row(int col, int row);
	void get_where_can_place_chess();
	void reverse_chesses(int col, int row);
	void next_turn();
	void end_game();
	void update_chess_num(bool is_reverse);
	void init_combo();
	void show_combo();
	bool check_last_place();
	UFUNCTION(BlueprintCallable)
		bool check_is_running();
	UFUNCTION(BlueprintCallable)
		void clear_combo();

	TArray<FVector> chess_position[8];
	TArray<Achess*> chesses[8];
	//TArray<Achess_character*> chesses[8];
	TArray<AHint_actor*> hint_array;
	TMap<FString, TArray<std::pair<int, int>>> can_place_chess;  //後面為方向
	TMap<int, int> position_map_x;
	TMap<int, int> position_map_y;
	bool passed;
	std::pair<int, int> last_place;
};