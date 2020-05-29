// Fill out your copyright notice in the Description page of Project Settings.

#include "Tetris/Public/TBoard.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATBoard::ATBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Board Mesh"));
	RootComponent = BoardMesh;

	SpawnMarker = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Marker"));
	SpawnMarker->SetupAttachment(RootComponent);

	Base = CreateDefaultSubobject<UBoxComponent>(TEXT("Base"));
	Base->SetCollisionObjectType(STOPPING_ACTOR);
	Base->SetCollisionResponseToAllChannels(ECR_Ignore);
	Base->SetCollisionResponseToChannel(STOPPING_ACTOR, ECR_Overlap);
	Base->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATBoard::BeginPlay()
{
	Super::BeginPlay();
	for (int r = 0; r < BOARD_ROWS; ++r)
	{
		for (int c = 0; c < BOARD_COLUMNS; ++c)
		{
			Occupancies[r][c] = 0;
		}
	}
	SpawnTetromino();
}

void ATBoard::SpawnTetromino()
{
	if (TetrominoClasses.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tetromino Classes must be set in order to spawn them"));
		return;
	}
	int randIndex = FMath::RandRange(0, TetrominoClasses.Num() - 1);
	ATTetromino* Tetromino = GetWorld()->SpawnActor<ATTetromino>(TetrominoClasses[randIndex], SpawnMarker->GetComponentLocation(), FRotator::ZeroRotator);
	Tetromino->SetBoardOwner(this);

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	PC->Possess(Tetromino);
	PC->SetViewTarget(this);

	Tetromino->Init();
}

void ATBoard::ClearRow(int Row)
{

}

void ATBoard::CompleteTurn()
{

}

// Called every frame
void ATBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ATBoard::GetDescendRate()
{
	return DescendRate;
}

void ATBoard::EndTurn(ATTetromino* Tetromino)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	PC->bAutoManageActiveCameraTarget = false;
	PC->UnPossess();
	PC->SetViewTarget(this);
	SpawnTetromino();
}

