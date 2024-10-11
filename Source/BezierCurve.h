#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BezierCurve.generated.h"

UCLASS()
class GHOSTPROTO_API ABezierCurve : public AActor
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, Category = Debug) bool bShouldDrawDebug = false;
	UPROPERTY(EditAnywhere, Category = Debug) bool bShouldDrawVelocityLine = false;
	UPROPERTY(EditAnywhere, Category = Debug) float debugOffset = 50;
	UPROPERTY(VisibleAnywhere, Category = Debug) int lineSteps = 10;

	UPROPERTY(VisibleAnywhere, Category = Points) int32 index = 3;
	UPROPERTY(VisibleAnywhere, Category = Points) int32 baseIndex = 3;

	UPROPERTY(EditAnywhere, Category = Points) TArray<USceneComponent*> points;
	UPROPERTY() USceneComponent* p0;
	UPROPERTY() USceneComponent* p1;
	UPROPERTY() USceneComponent* p2;





public:
	ABezierCurve();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual bool ShouldTickIfViewportsOnly() const override;
	UFUNCTION(CallInEditor, Category = Debug)
	void DrawVisualDebug();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = Points)
	virtual void AddPoint();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = Points)
	virtual void RemovePoint();

	UFUNCTION(BlueprintCallable, CallInEditor, Category = Points)
	virtual void Reset();


	FVector GetPoint(const float& _time);
	FVector GetVelocity(const float& _time);


};
