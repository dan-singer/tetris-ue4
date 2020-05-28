// Fill out your copyright notice in the Description page of Project Settings.


#include "Tetris/Public/TTetromino.h"
#include "TimerManager.h"
#include "../Public/TBoard.h"

// Sets default values
ATTetromino::ATTetromino()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Holder = CreateDefaultSubobject<USceneComponent>(TEXT("Holder"));
	RootComponent = Holder;

	BlockA = MakeBlock("Block A");
	BlockB = MakeBlock("Block B");
	BlockC = MakeBlock("Block C");
	BlockD = MakeBlock("Block D");
}

void ATTetromino::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	UE_LOG(LogTemp, Warning, TEXT("OUCH!"));
}

// Called when the game starts or when spawned
void ATTetromino::BeginPlay()
{
	Super::BeginPlay();

}

void ATTetromino::Descend()
{
	FVector CurLocation = GetActorLocation();
	SetActorLocation(CurLocation + -FVector::UpVector * BLOCK_SIZE);
}

UStaticMeshComponent* ATTetromino::MakeBlock(FName Name)
{
	UStaticMeshComponent* Block = CreateDefaultSubobject<UStaticMeshComponent>(Name);
	Block->SetCollisionObjectType(STOPPING_ACTOR);
	Block->SetupAttachment(RootComponent);
	return Block;
}

// Called every frame
void ATTetromino::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATTetromino::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATTetromino::Init()
{
	ATBoard* Board = Cast<ATBoard>(GetOwner());
	GetWorldTimerManager().SetTimer(DescendTimer, this, &ATTetromino::Descend, Board->GetDescendRate(), true);
}

