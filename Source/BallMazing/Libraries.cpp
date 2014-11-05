

#include "BallMazing.h"
#include "Libraries.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>



// convert hex ascii to int
// return true on success, false on failure
bool hexasciitoint(char& ival, char character)
{
	if (character >= 48 && character <= 57) // [0-9]
	{
		ival = static_cast<char>(character - 48);
		return true;
	}
	else if (character >= 65 && character <= 70) // [A-F]
	{
		ival = static_cast<char>(10 + character - 65);
		return true;
	}
	else if (character >= 97 && character <= 102) // [a-f]
	{
		ival = static_cast<char>(10 + character - 97);
		return true;
	}

	ival = 0;
	return false;
}

// convert array of 8 hex ascii to f32
// The input hexascii is required to be a little-endian representation
// as used in the iridas file format
// "AD10753F" -> 0.9572857022285461f on ALL architectures

bool hexasciitofloat(float& fval, const char * ascii)
{
	// Convert all ASCII numbers to their numerical representations
	char asciinums[8];
	for (unsigned int i = 0; i<8; ++i)
	{
		if (!hexasciitoint(asciinums[i], ascii[i]))
		{
			return false;
		}
	}

	unsigned char * fvalbytes = reinterpret_cast<unsigned char *>(&fval);
	fvalbytes[0] = (unsigned char)(asciinums[1] | (asciinums[0] << 4));
	fvalbytes[1] = (unsigned char)(asciinums[3] | (asciinums[2] << 4));
	fvalbytes[2] = (unsigned char)(asciinums[5] | (asciinums[4] << 4));
	fvalbytes[3] = (unsigned char)(asciinums[7] | (asciinums[6] << 4));
	//#if OCIO_LITTLE_ENDIAN
	//	// Since incoming values are little endian, and we're on little endian
	//	// preserve the byte order
	//	fvalbytes[0] = (unsigned char)(asciinums[1] | (asciinums[0] << 4));
	//	fvalbytes[1] = (unsigned char)(asciinums[3] | (asciinums[2] << 4));
	//	fvalbytes[2] = (unsigned char)(asciinums[5] | (asciinums[4] << 4));
	//	fvalbytes[3] = (unsigned char)(asciinums[7] | (asciinums[6] << 4));
	//#else
	//	// Since incoming values are little endian, and we're on big endian
	//	// flip the byte order
	//	fvalbytes[0] = (unsigned char)(asciinums[1] | (asciinums[0] << 4));
	//	fvalbytes[2] = (unsigned char)(asciinums[3] | (asciinums[2] << 4));
	//	fvalbytes[1] = (unsigned char)(asciinums[5] | (asciinums[4] << 4));
	//	fvalbytes[0] = (unsigned char)(asciinums[7] | (asciinums[6] << 4));
	//#endif
	return true;
}


ULibraries::ULibraries(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	
}

Femtoduino::Serial * FemtoduinoPointer = new Femtoduino::Serial("\\\\.\\COM7");
FQuat hq = FQuat::Identity;

void ULibraries::WriteFemtoduino()
{

	FemtoduinoPointer->WriteData("w\n", 32);

}



void ULibraries::SetHome(FRotator h)
{
	float q1, q2, q3, q4;
	bool sent = FemtoduinoPointer->WriteData("w\n", 32);
	char parse1[10], parse2[10], parse3[10], parse4[10];
	char incomingData[250];
	int dataLength = 250;
	Sleep(50);
	FemtoduinoPointer->ReadData(incomingData, dataLength);

	_memccpy(&parse1, incomingData, ',', 8);
	_memccpy(&parse2, &incomingData[9], ',', 8);
	_memccpy(&parse3, &incomingData[18], ',', 8);
	_memccpy(&parse4, &incomingData[27], ',', 8);



	hexasciitofloat(q1, parse1);
	hexasciitofloat(q2, parse2);
	hexasciitofloat(q3, parse3);
	hexasciitofloat(q4, parse4);


	FQuat newQ = FQuat(-q2, -q3, -q4, q1);
	hq = newQ;
}



FRotator ULibraries::GetQRotation()
{
	
	float q1, q2, q3, q4;
	bool sent = FemtoduinoPointer->WriteData("w\n", 32);
	char parse1[10], parse2[10], parse3[10], parse4[10];
	char incomingData[250];
	int dataLength = 250;
	//Sleep(50);
	FemtoduinoPointer->ReadData(incomingData, dataLength);

	_memccpy(&parse1, incomingData,',' ,8);
	_memccpy(&parse2, &incomingData[9],',', 8);
	_memccpy(&parse3, &incomingData[18], ',', 8);
	_memccpy(&parse4, &incomingData[27], ',', 8);



	hexasciitofloat(q1, parse1);
	hexasciitofloat(q2, parse2);
	hexasciitofloat(q3, parse3);
	hexasciitofloat(q4, parse4);
	
	
	FQuat newQ = FQuat(q2,q3,q4,q1);

	if (!hq.Equals(FQuat::Identity))
	{
		return (hq*newQ).Rotator();
	}

	//newQ.Normalize(1.1);
	//FQuat hq = FQuat::Identity;
	//FQuat next = newQ*hq;     //FQuat::Slerp(newQ,current.Quaternion(),.5);
	//FRotator test = next.Rotator();

	return newQ.Rotator();
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