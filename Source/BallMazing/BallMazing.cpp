#include "BallMazing.h"
//#include "Femtoduino.h"

//class FUE4MagicGameModule : public FDefaultGameModuleImpl
//{
//	Femtoduino::Serial *FemtoduinoPointer;
//
//	/**
//	* Called right after the module DLL has been loaded and the module object has been created
//	*/
//	virtual void StartupModule() override
//	{
//		FemtoduinoPointer = new Femtoduino::Serial("\\\\.\\COM9");
//		/*char incomingData[256] = "";
//		int dataLength = 256;
//		FemtoduinoPointer->ReadData(incomingData, dataLength);*/
//	}
//
//	/**
//	* Called before the module is unloaded, right before the module object is destroyed.
//	*/
//	virtual void ShutdownModule()
//	{
//		//PointerToBobsMagic->Dispose();
//		FemtoduinoPointer = NULL;
//	}
//};

// Override the default implementation with ours implementation =)
//IMPLEMENT_PRIMARY_GAME_MODULE(FUE4MagicGameModule, BallMazing, "BallMazing");
IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, BallMazing, "BallMazing");