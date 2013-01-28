// Chat.cpp : main project file.

#include "stdafx.h"
#include "Form1.h"

using namespace Chat;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 
	int m;

	// Create the main window and run it
	Application::Run(gcnew Form1());

	//Initialize
	return 0;
}
