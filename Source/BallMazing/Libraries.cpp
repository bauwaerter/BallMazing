

#include "BallMazing.h"
#include "Libraries.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>

//typedef char*(*_GetStuff)(); //our typedef is must be the same type of our dll function.

//class _Serial;
//typedef bool (_IsConnected)();
//typedef char *(*_GetFemtoduinoData)();

ULibraries::ULibraries(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	
}

Femtoduino::Serial * FemtoduinoPointer = new Femtoduino::Serial("\\\\.\\COM9");

FString ULibraries::GetFemtoduinoData()
{
	

	char incomingData[256] = "";
	int dataLength = 256;
	FemtoduinoPointer->ReadData(incomingData, dataLength);
	FString out = incomingData;
	return out;
}



//FString ULibraries::GetStuff()
//{
//	FString path = FPaths::GamePluginsDir();
//	FString filePath = FPaths::Combine(*FPaths::GamePluginsDir(), TEXT("Femtoduino/"), TEXT("Femtoduino.dll")); // get the plugin path, add the folder to contain the dll, and add the dll name
//	if (FPaths::FileExists(filePath))
//	{
//		void *DLLHandle;
//		DLLHandle = FPlatformProcess::GetDllHandle(*filePath); // get dll
//		if (DLLHandle != NULL)
//		{
//			_GetStuff DLLgetStuff = NULL; // the container for our dll function
//			FString procName = "?GetStuff@Serial@Femtoduino@@QEAAPEADXZ"; // the exact name of our dll function to recover
//			DLLgetStuff = (_GetStuff)FPlatformProcess::GetDllExport(DLLHandle, *procName); // get the dll function need
//			if (DLLgetStuff != NULL)
//			{
//				char * something = DLLgetStuff(); // call our dll function
//				FString out = (FString)something;
//				return out; // return to UE
//			}
//		}
//	}
//	return "";
//}

//bool ULibraries::IsConnected()
//{
//	FString path = FPaths::GamePluginsDir();
//	FString filePath = FPaths::Combine(*FPaths::GamePluginsDir(), TEXT("Femtoduino/"), TEXT("Femtoduino.dll")); // get the plugin path, add the folder to contain the dll, and add the dll name
//	if (FPaths::FileExists(filePath))
//	{
//		void *DLLHandle;
//		DLLHandle = FPlatformProcess::GetDllHandle(*filePath); // get dll
//		if (DLLHandle != NULL)
//		{
//			_IsConnected DLLisConnected = false; // the container for our dll function
//			FString procName = "IsConnected"; // the exact name of our dll function to recover
//			DLLisConnected = (_IsConnected)FPlatformProcess::GetDllExport(DLLHandle, *procName); // get the dll function need
//			if (DLLisConnected)
//			{
//				return IsConnected();
//			}
//		}
//	}
//	return false;
//}