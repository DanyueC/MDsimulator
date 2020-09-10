// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		UFUNCTION(BlueprintCallable, Category = "MDTools")
		static void TestArray(UPARAM(ref)TArray<FVector>& oxygen, UPARAM(ref)TArray<FVector>& carbon, UPARAM(ref)TArray<FVector>& nitrogen, UPARAM(ref)TArray<FVector>& hydrogen);
		UFUNCTION(BlueprintCallable, Category = "MDTools")
		static void Frames(int frame);
		UFUNCTION(BlueprintCallable, Category = "MDTools")
		static void VWDArray(int frame, UPARAM(ref)TArray<FVector>& oxygen, UPARAM(ref)TArray<FVector>& carbon, UPARAM(ref)TArray<FVector>& nitrogen, UPARAM(ref)TArray<FVector>& hydrogen);


};

struct Coords {
	float x;
	float y;
	float z;
	int acid;
};