// Fill out your copyright notice in the Description page of Project Settings.


#include "Tetris/Public/TTetromino.h"
#include "TimerManager.h"
#include "../Public/TBoard.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATTetromino::ATTetromino()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComp->SetCollisionObjectType(STOPPING_ACTOR);
	RootComponent = MeshComp;
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
	FVector CurrentLocation = GetActorLocation();
	SetActorLocation(CurrentLocation + FVector::DownVector * BLOCK_SIZE, true);
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

}

void ATTetromino::HandleDown()
{
	FVector CurLocation = GetActorLocation();
	SetActorLocation(CurLocation + FVector::DownVector * BLOCK_SIZE, true);
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
	GetWorldTimerManager().SetTimer(DescendTimer, this, &ATTetromino::Descend, BoardOwner->GetDescendRate(), true);
}

void ATTetromino::SetBoardOwner(ATBoard* Board)
{
	BoardOwner = Board;
}

