#ifndef SERIALCLASS_H_INCLUDED
#define SERIALCLASS_H_INCLUDED

#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>

#if defined DLL_EXPORT
#define DECLDIR __declspec(dllexport)
#else
#define DECLDIR __declspec(dllexport)
#endif

#define ARDUINO_WAIT_TIME 2000

namespace Femtoduino{
	class Serial
	{
	private:
		//Serial comm handler
		HANDLE hSerial;
		//Connection status
		bool connected;
		//Get various information about the connection
		COMSTAT status;
		//Keep track of last error
		unsigned long errors;

	public:
		//Initialize Serial communication with the given COM port
		DECLDIR Serial(char *portName);
		//Close the connection
		//NOTA: for some reason you can't connect again before exiting
		//the program and running it again
		DECLDIR ~Serial();
		//Read data in a buffer, if nbChar is greater than the
		//maximum number of bytes available, it will return only the
		//bytes available. The function return -1 when nothing could
		//be read, the number of bytes actually read.
		DECLDIR int ReadData(char *buffer, unsigned int nbChar);
		//Writes data from a buffer through the Serial connection
		//return true on success.
		DECLDIR bool WriteData(char *buffer, unsigned int nbChar);
		//Check if we are actually connected
		DECLDIR bool IsConnected();

		DECLDIR HANDLE& getHandle();

		DECLDIR char * GetStuff(void);
	};



}
#endif // SERIALCLASS_H_INCLUDED