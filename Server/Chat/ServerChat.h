#include "stdafx.h"
#include <winsock2.h>
using namespace System::Windows::Forms;
#pragma comment(lib,"ws2_32.lib")

class ServerChat
{
public:
	void Initialize(RichTextBox^ outputBox);
	bool Create(RichTextBox^ outputBox);
	char* Send(char* message);
	char* Receive(RichTextBox^ outputBox);

	void Shutdown();

private:
	char* sendText;
	SOCKET socket;
};
