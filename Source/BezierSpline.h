// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BezierSpline.generated.h"

UCLASS()
class GHOSTPROTO_API ABezierSpline : public AActor
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere, Category = Debug) bool bShouldDrawDebug = false;
	UPROPERTY(EditAnywhere, Category = Debug) bool bShouldDrawVelocityLine = false;
	UPROPERTY(EditAnywhere, Category = Debug) float debugOffset = 50;
	UPROPERTY(VisibleAnywhere, Category = Debug) int curveSteps = 10;

	UPROPERTY(VisibleAnywhere, Category = Points) int32 index = 4;
	UPROPERTY(VisibleAnywhere, Category = Points) int32 baseIndex = 4;
	int32 numOfCurvePoints = 3;

	UPROPERTY(EditAnywhere, Category = Points) TArray<USceneComponent*> points;
	UPROPERTY() USceneComponent* p0;
	UPROPERTY() USceneComponent* p1;
	UPROPERTY() USceneComponent* p2;
	UPROPERTY() USceneComponent* p3;

public:
	ABezierSpline();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual bool ShouldTickIfViewportsOnly() const override;

	FORCEINLINE int CurveCount() { return points.Num() / 3; }

	UFUNCTION(CallInEditor, Category = Debug)
	void DrawVisualDebug();
	void DrawDefaultLines();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = Points)
	virtual void AddCurve();
	virtual void AddPoint();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = Points)
	virtual void RemoveCurve();
	virtual void RemovePoint();

	UFUNCTION(BlueprintCallable, CallInEditor, Category = Points)
	virtual void Reset();


	FVector GetDirection(const float& _time);

	FVector GetPoint(const float& _time);
	FVector GetVelocity(const float& _time);

};
