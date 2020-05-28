// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tetris/Tetris.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "TTetromino.h"
#include "TBoard.generated.h"

UCLASS()
class TETRIS_API ATBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATBoard();

protected:

	uint8 Occupancies[BOARD_ROWS][BOARD_COLUMNS];

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* BoardMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* SpawnMarker;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* Base;


	UPROPERTY(EditDefaultsOnly, Category = "Board")
	TArray<TSubclassOf<ATTetromino>> TetrominoClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Board")
	float DescendRate = 1.0f;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnTetromino();
	void ClearRow(int Row);
	void CompleteTurn();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetDescendRate();

};
