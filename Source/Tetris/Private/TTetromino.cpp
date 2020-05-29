// Fill out your copyright notice in the Description page of Project Settings.


#include "Tetris/Public/TTetromino.h"
#include "TimerManager.h"
#include "../Public/TBoard.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

// Sets default values
ATTetromino::ATTetromino()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Pivot = CreateDefaultSubobject<USceneComponent>(TEXT("Pivot"));
	RootComponent = Pivot;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComp->SetCollisionObjectType(STOPPING_ACTOR);
	MeshComp->SetupAttachment(RootComponent);
	
}



void ATTetromino::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	SnapToGrid();
	EndTurn();
}

// Called when the game starts or when spawned
void ATTetromino::BeginPlay()
{
	Super::BeginPlay();

}

void ATTetromino::Descend()
{
	FVector CurrentLocation = GetActorLocation();
	if (!SetActorLocation(CurrentLocation + FVector::DownVector * BLOCK_SIZE, true))
	{
		SnapToGrid();
		EndTurn();
	}
}


void ATTetromino::HandleLeft()
{
	FVector CurLocation = GetActorLocation();
	SetActorLocation(CurLocation + FVector::BackwardVector * BLOCK_SIZE, true);
}

void ATTetromino::HandleRight()
{
	FVector CurLocation = GetActorLocation();
	SetActorLocation(CurLocation + FVector::ForwardVector * BLOCK_SIZE, true);
}

void ATTetromino::HandleUp()
{
	AddActorLocalRotation(FRotator(-90.0f,0,0), true);
	SnapToGrid();
}

void ATTetromino::HandleDown()
{
	GetWorldTimerManager().ClearTimer(DescendTimer);
	GetWorldTimerManager().SetTimer(DescendTimer, this, &ATTetromino::Descend, BoardOwner->GetDescendRate(), true);
	Descend();
}

void ATTetromino::EndTurn()
{
	GetWorldTimerManager().ClearTimer(DescendTimer);
	BoardOwner->EndTurn(this);
}

void ATTetromino::SnapToGrid()
{
	FBox BB = MeshComp->CalcBounds(GetTransform()).GetBox();

	FVector OriginLocation = FVector(BB.Min.X, BB.Max.Y, BB.Max.Z);
	FVector ToCenter = GetActorLocation() - OriginLocation;
	OriginLocation.X = FMath::RoundToInt(OriginLocation.X / BLOCK_SIZE) * BLOCK_SIZE;
	OriginLocation.Z = FMath::RoundToInt(OriginLocation.Z / BLOCK_SIZE) * BLOCK_SIZE;
	SetActorLocation(OriginLocation + ToCenter, true);
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
	PlayerInputComponent->BindAction("Left", EInputEvent::IE_Pressed, this, &ATTetromino::HandleLeft);
	PlayerInputComponent->BindAction("Right", EInputEvent::IE_Pressed, this, &ATTetromino::HandleRight);
	PlayerInputComponent->BindAction("Up", EInputEvent::IE_Pressed, this, &ATTetromino::HandleUp);
	PlayerInputComponent->BindAction("Down", EInputEvent::IE_Pressed, this, &ATTetromino::HandleDown);

}

void ATTetromino::Init()
{
	FVector OldLocation = GetActorLocation();
	RootComponent->DestroyComponent(true);
	OriginDelta = OldLocation - GetActorLocation();
	GetWorldTimerManager().SetTimer(DescendTimer, this, &ATTetromino::Descend, BoardOwner->GetDescendRate(), true);
}

void ATTetromino::SetBoardOwner(ATBoard* Board)
{
	BoardOwner = Board;
}

