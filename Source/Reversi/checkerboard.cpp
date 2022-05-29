// Fill out your copyright notice in the Description page of Project Settings.


#include "checkerboard.h"
#include "chess.h"
#include "chess_character.h"
#include "Hint_actor.h"
#include "Components/AudioComponent.h"
#include "Components/TextRenderComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include <utility>

#define PositionString(row, col) (FString::Printf(TEXT("%d-%d"), row, col))
//¥ýrow¦Acol

// Sets default values
Acheckerboard::Acheckerboard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	checkboard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("checkboard"));
	sound_effect_component = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundEffectComponent"));
	combo_render = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Combo_render"));
	fire_component_1 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("fire_component_1"));
	fire_component_2 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("fire_component_2"));

	float m = 700.0f, n = -700.0f;
	//init board
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			this->chess_position[i].Emplace(FVector(m, n, 380.0f));
			n += 200.0f;
			this->chesses[i].Emplace(nullptr);
		}
		m -= 200.0f;
		n = -700.0f;
	}
	this->position_map_x = {
		{700, 0}, {600, -1}, {500, 1}, {400, -1},
		{300, 2}, {200, -1}, {100, 3}, {0, -1}, 
		{-100, 4}, {-200, -1}, {-300, 5}, {-400, -1},
		{-500, 6}, {-600, -1}, {-700, 7}
	};
	this->position_map_y = {
		{700, 7}, {600, -1}, {500, 6}, {400, -1},
		{300, 5}, {200, -1}, {100, 4}, {0, -1},
		{-100, 3}, {-200, -1}, {-300, 2}, {-400, -1},
		{-500, 1}, {-600, -1}, {-700, 0}
	};

	this->is_black_round = true;
	this->passed = false;
	this->is_running = false;
	this->black_num = 2;
	this->white_num = 2;
	this->combo = 0;
	this->reverse_num = 0;
	this->last_place = { -1, -1 };
}

void Acheckerboard::init_board()
{
	UWorld* World = GetWorld();
	this->chesses[3][3] = World->SpawnActor<Achess>(this->chess_class, this->chess_position[3][3], FRotator(0.0f, 0.0f, 0.0f));
	this->chesses[3][4] = World->SpawnActor<Achess>(this->chess_class, this->chess_position[3][4], FRotator(180.0f, 0.0f, 0.0f));
	this->chesses[4][3] = World->SpawnActor<Achess>(this->chess_class, this->chess_position[4][3], FRotator(180.0f, 0.0f, 0.0f));
	this->chesses[4][4] = World->SpawnActor<Achess>(this->chess_class, this->chess_position[4][4], FRotator(0.0f, 0.0f, 0.0f));
	this->chesses[3][4]->set_is_black(true);
	this->chesses[4][3]->set_is_black(true);
}

void Acheckerboard::if_in_a_row(int row, int col)
{
	if (this->chesses[row][col] != nullptr)
		return;
	bool is_first_time_flag = true;
	bool can_in_a_row;
	std::pair<int, int> directions[8] = { {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1} };
	for (std::pair<int, int> d : directions)
	{
		int x, y;
		can_in_a_row = false;
		for (int n = 1; n < 8; n++)
		{
			x = (d.first * n) + col;
			y = (d.second * n) + row;
			if ( (x >= 8) || (x < 0) || (y >= 8) || (y < 0) )
				break;
			if (this->chesses[y][x] != nullptr)
			{
				if (this->is_black_round)
				{
					if (!this->chesses[y][x]->is_black)
					{
						if (!can_in_a_row)
							can_in_a_row = true;
						continue;
					}
					else if (this->chesses[y][x]->is_black)
					{
						if (can_in_a_row)
						{
							if (is_first_time_flag)
							{
								this->can_place_chess.Add(PositionString(row, col), { d });
								is_first_time_flag = false;
								break;
							}
							else
							{
								this->can_place_chess[PositionString(row, col)].Add(d);
								break;
							}
						}
						else
							break;
					}
				}
				else
				{
					if (this->chesses[y][x]->is_black)
					{
						if (!can_in_a_row)
							can_in_a_row = true;
						continue;
					}
					else if (!this->chesses[y][x]->is_black)
					{
						if (can_in_a_row)
						{
							if (is_first_time_flag)
							{
								this->can_place_chess.Add(PositionString(row, col), { d });
								is_first_time_flag = false;
								can_in_a_row = false;
								break;
							}
							else
							{
								this->can_place_chess[PositionString(row, col)].Add(d);
								can_in_a_row = false;
								break;
							}
						}
						else
							break;
					}
				}
			}
			else
				break;
		}
	}
}

void Acheckerboard::get_where_can_place_chess()
{
	this->can_place_chess.Empty();
	for (unsigned i = 0; i < 8; i++)
	{
		for (unsigned j = 0; j < 8; j++)
		{
			this->if_in_a_row(i, j);
		}
	}
	return;
}

void Acheckerboard::hint()
{
	TArray<FString> pos_split;
	int x, y;
	UWorld* world = GetWorld();
	for (TPair<FString, TArray<std::pair<int, int>>>& pos : this->can_place_chess)
	{
		pos.Key.ParseIntoArray(pos_split, TEXT("-"), true);
		LexFromString(x, *pos_split[1]);
		LexFromString(y, *pos_split[0]);
		this->hint_array.Emplace(world->SpawnActor<AHint_actor>(this->hint_class, this->chess_position[y][x], FRotator(0, 0, 0)));
	}
	return;
}

void Acheckerboard::clear_hint()
{
	if (this->hint_array.Num() != 0)
	{
		for (AHint_actor* actor : this->hint_array)
		{
			actor->Destroy();
		}
	}
	this->hint_array.Empty();
	return;
}

int num_round(float val)
{
	if (val >= 0)
	{
		int hundreds_digit = val / 100;
		int left = (hundreds_digit) * 100;
		int right = (hundreds_digit + 1) * 100;
		if ((val - left) >= (right - val))
			return right;
		else
			return left;
	}
	else
	{
		int hundreds_digit = val / 100;
		int left = (hundreds_digit - 1) * 100;
		int right = (hundreds_digit) * 100;
		if ((val - left) < (right - val))
			return left;
		else
			return right;
	}
}

std::pair<int*, int*> Acheckerboard::check_position(float x, float y)
{
	int x_round = num_round(x);
	int y_round = num_round(y);
	int* x_ptr = this->position_map_x.Find(x_round);
	int* y_ptr = this->position_map_y.Find(y_round);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("r: %d  c: %d"), *x_ptr, *y_ptr));
	return { x_ptr, y_ptr };
}

void Acheckerboard::update_chess_num(bool is_reverse)
{
	/*TArray<AActor*> found_chess;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), Achess::StaticClass(), found_chess);
	this->black_num = 0;
	this->white_num = 0;
	Achess* chess;
	for (AActor* actor : found_chess)
	{
		chess = Cast<Achess>(actor);
		if (chess != nullptr)
		{
			if (chess->is_black)
				this->black_num++;
			else
				this->white_num++;
		}
	}*/
	if (this->is_black_round)
	{			
		this->black_num++;
		if (is_reverse)
			this->white_num--;
	}
	else
	{
		this->white_num++;
		if (is_reverse)
			this->black_num--;
	}
	return;
}

void Acheckerboard::reverse_chesses(int row, int col)
{
	this->is_running = true;
	this->reverse_num = 0;
	TArray<std::pair<int, int>>* directions = this->can_place_chess.Find(PositionString(row, col));
	if (!directions)
		return;
	int x, y;
	for (std::pair<int, int> d : *directions)
	{
		for (int n = 1; n < 8; n++)
		{
			x = (d.first * n) + col;
			y = (d.second * n) + row;
			if (x < 0 || x >= 8 || y < 0 || y >= 8)
				break;
			if (this->chesses[y][x] != nullptr)
			{
				if (this->chesses[row][col]->is_black != this->chesses[y][x]->is_black)
				{
					this->reverse_num++;
					this->chesses[y][x]->reverse();
					this->update_chess_num(true);
					this->combo++;
					this->show_combo();
				}
				else
					break;
			}
		}
	}
	return;
}

void Acheckerboard::end_game()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "End Game");
	return;
}

void Acheckerboard::next_turn()
{
	this->is_black_round = !this->is_black_round;
	this->get_where_can_place_chess();
	if (this->can_place_chess.Num() == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "pass");
		if (this->passed)
			this->end_game();
		else
		{
			this->passed = true;
			this->next_turn();
		}
	}
	else
	{
		this->passed = false;
		this->hint();
	}
	//this->update_chess_num();
	//this->clear_combo();
	return;
}

bool Acheckerboard::check_is_running()
{
	/*if (this->reverse_num != 0)
		return true;
	else
		return false;*/
	return (this->reverse_num != 0) ? true : false;
}

bool Acheckerboard::check_last_place()
{
	/*if (this->last_place.first == -1 && this->last_place.second == -1)
		false;*/
	return (this->last_place.first == -1 && this->last_place.second == -1) ? false : true;
}

void Acheckerboard::place_chess(FVector location)
{
	if (this->check_is_running())
		return;
	float x = location.X;
	float y = location.Y;
	if (x > 750 || x < -750 || y > 750 || y < -750)
		return ;
	std::pair<int*, int*> pos = this->check_position(x, y);
	//if (this->check_last_place())
	//	this->chesses[this->last_place.first][this->last_place.second]->close_outline();
	//this->last_place = { *pos.first, *pos.second };
	if (pos.first != nullptr && pos.second != nullptr && *pos.first != -1 && *pos.second != -1)
	{
		if (this->chesses[*pos.first][*pos.second] == nullptr)
		{
			if (this->is_black_round)
			{
				if (!this->can_place_chess.Find(PositionString(*pos.first, *pos.second)))
					return;
				if (this->check_last_place())
					this->chesses[this->last_place.first][this->last_place.second]->close_outline();
				this->last_place = { *pos.first, *pos.second };
				this->clear_hint();
				this->chesses[*pos.first][*pos.second] = GetWorld()->SpawnActor<Achess>(this->chess_class, this->chess_position[*pos.first][*pos.second], FRotator(180, 0, 0));
				this->chesses[*pos.first][*pos.second]->is_black = true;
				this->chesses[this->last_place.first][this->last_place.second]->show_outline();
				this->update_chess_num(false);
				this->sound_effect_component->Play();
				this->reverse_chesses(*pos.first, *pos.second);
				//this->is_black_round = false;
				this->next_turn();
			}
			else
			{
				if (!this->can_place_chess.Find(PositionString(*pos.first, *pos.second)))
					return;
				if (this->check_last_place())
					this->chesses[this->last_place.first][this->last_place.second]->close_outline();
				this->last_place = { *pos.first, *pos.second };
				this->clear_hint();
				this->chesses[*pos.first][*pos.second] = GetWorld()->SpawnActor<Achess>(this->chess_class, this->chess_position[*pos.first][*pos.second], FRotator(0, 0, 0));
				this->chesses[*pos.first][*pos.second]->is_black = false;
				this->chesses[this->last_place.first][this->last_place.second]->show_outline();
				this->update_chess_num(false);
				this->sound_effect_component->Play();
				this->reverse_chesses(*pos.first, *pos.second);
				//this->is_black_round = true;
				this->next_turn();
			}	
		}
	}
	else
		return ;
}

void Acheckerboard::init_combo() 
{
	this->combo_render->SetRelativeLocation(FVector(-800, 1000, 150));
	this->combo_render->SetRelativeRotation(FRotator(90, 180, 0));
	//this->combo_render->SetTextRenderColor(FColor(108, 117, 125, 0));
	this->combo_render->SetTextRenderColor(FColor(89, 13, 34, 0));
	this->combo_render->SetRelativeScale3D(FVector(10, 10, 10));
	this->combo_render->SetText(TEXT(""));

	this->fire_component_1->SetRelativeLocation(FVector(-875, 1190, 150));
	this->fire_component_1->SetRelativeRotation(FRotator(90, 180, 0));
	this->fire_component_1->SetWorldScale3D(FVector(10, 1, 1));
	this->fire_component_1->SetVisibility(false);

	this->fire_component_2->SetRelativeLocation(FVector(-875, 1330, 150));
	this->fire_component_2->SetRelativeRotation(FRotator(90, 180, 0));
	this->fire_component_2->SetWorldScale3D(FVector(10, 1, 1));
	this->fire_component_2->SetVisibility(false);
}

void Acheckerboard::show_combo()
{
	this->combo_render->SetText(FString::Printf(TEXT("%d"), this->combo));
	this->fire_component_1->SetVisibility(true);
	if (this->combo >= 10)
		this->fire_component_2->SetVisibility(true);
	return;
}

void Acheckerboard::clear_combo()
{
	this->combo_render->SetText(TEXT(""));
	this->combo = 0;
	this->fire_component_1->SetVisibility(false);
	this->fire_component_2->SetVisibility(false);
	return;
}

// Called when the game starts or when spawned
void Acheckerboard::BeginPlay()
{
	Super::BeginPlay();

	this->init_board();
	this->get_where_can_place_chess();
	this->hint();
	this->init_combo();
	//this->show_combo();
}

// Called every frame
void Acheckerboard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}