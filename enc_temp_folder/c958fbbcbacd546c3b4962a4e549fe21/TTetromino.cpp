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

void ATTetromino::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	UE_LOG(LogTemp, Warning, TEXT("OUCH!"));
}

void ATTetromino::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
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
	AddActorLocalRotation(FRotator(-90.0f,0,0), true);

	OriginDelta = OriginDelta.RotateAngleAxis(-90.0f, FVector::RightVector);


	// Snap to grid
	FVector OriginLocation = GetActorLocation() + OriginDelta;

	DrawDebugSphere(GetWorld(), OriginLocation, 32.0f, 16, FColor::Red, false, 1.0f);

	OriginLocation.X = (int)(OriginLocation.X) / BLOCK_SIZE * BLOCK_SIZE;
	OriginLocation.Z = (int)(OriginLocation.Z) / BLOCK_SIZE * BLOCK_SIZE;
	SetActorLocation(OriginLocation - OriginDelta);
}

void ATTetromino::HandleDown()
{
	FVector CurLocation = GetActorLocation();
	SetActorLocation(CurLocation + FVector::DownVector * BLOCK_SIZE, true);
}

void ATTetromino::EndTurn()
{
	GetWorldTimerManager().ClearTimer(DescendTimer);
	BoardOwner->EndTurn(this);
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

