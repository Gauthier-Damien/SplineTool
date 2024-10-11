#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LineActor.generated.h"

UCLASS()
class GHOSTPROTO_API ALineActor : public AActor
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere, Category = Debug) bool bShouldDrawDebug = false;
	UPROPERTY(EditAnywhere, Category = Debug) float debugOffset = 50;

	UPROPERTY(VisibleAnywhere, Category = Points) int32 index = 2;


	UPROPERTY(EditAnywhere, Category = Points) TArray<USceneComponent*> points;
	UPROPERTY() USceneComponent* p0;
	UPROPERTY() USceneComponent* p1;



public:	
	ALineActor();

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
};
