// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tetris/Tetris.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "TTetromino.generated.h"

class ATBoard;


UCLASS()
class TETRIS_API ATTetromino : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATTetromino();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	FTimerHandle DescendTimer;

	ATBoard* BoardOwner;

	USceneComponent* Pivot;

	FVector OriginDelta;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void Descend();

	void HandleLeft();
	void HandleRight();
	void HandleUp();
	void HandleDown();

	void EndTurn();

	void SnapToGrid();

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Init();

	void SetBoardOwner(ATBoard* Board);

};
