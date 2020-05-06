/*----------------------------------------
File Name: main.cpp
Purpose: Starts application
Author: Tarn Cooper
Modified: 17 April 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#include "GraphicsEngineApp.h"
//main function
int main() {
	
	// allocation
	auto app = new GraphicsEngineApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}