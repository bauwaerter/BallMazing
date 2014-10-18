#pragma once
#include "Femtoduino.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Libraries.generated.h"


/**
 * 
 */
UCLASS()
class BALLMAZING_API ULibraries : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "Femtoduino Libraries")

	

	static FString GetFemtoduinoData();
	
	/*class Serial;*/
	


	
};

