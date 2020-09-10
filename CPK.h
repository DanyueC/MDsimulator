// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CPK.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UCPK : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		//Stick position & direction vector
		UFUNCTION(BlueprintCallable, Category = "MDTools")
		static void CPKArray(int frame, UPARAM(ref)TArray<FVector>& stick, UPARAM(ref)TArray<FVector>& direction);
		//This founction is not used, this is future work
		UFUNCTION(BlueprintCallable, Category = "MDTools")
		static void NewArray(int frame, UPARAM(ref)TArray<FVector>& newpoint);
};


struct Coords {
	float x;
	float y;
	float z;
	int acid;
};
