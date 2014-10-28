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

	static FRotator GetQRotation();

	UFUNCTION(BlueprintCallable, Category = "Femtoduino Libraries")
	static FRotator GetFemtoduinoData();
	
	UFUNCTION(BlueprintCallable, Category = "Femtoduino Libraries")
		static void SetHome(FRotator h);
	/*class Serial;*/
	


	
};

