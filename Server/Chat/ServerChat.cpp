#include "ServerChat.h"
#include "stdafx.h"

void ServerChat::Initialize(RichTextBox^ outputBox)
{
	WSADATA WsaDat;
	if(WSAStartup(MAKEWORD(2,2),&WsaDat)!=0)
	{
		outputBox->Text = "WSA Initialization failed!";
		WSACleanup();
		return;
	}
	return;
}

bool ServerChat::Create(RichTextBox^ outputBox)
{
	SOCKET socket=(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(socket==INVALID_SOCKET)
	{
		outputBox->Text += "Socket creation failed.\r\n";
		WSACleanup();
		return false;
	}
	
	SOCKADDR_IN serverInf;
	serverInf.sin_family=AF_INET;
	serverInf.sin_addr.s_addr=INADDR_ANY;
	serverInf.sin_port=htons(8888);

	if(bind(socket,(SOCKADDR*)(&serverInf),sizeof(serverInf))==SOCKET_ERROR)
	{
		outputBox->Text += "Unable to bind socket!\r\n";
		WSACleanup();
		return;
	}

	listen(socket,1);

	SOCKET TempSock=SOCKET_ERROR;
	while(TempSock==SOCKET_ERROR)
	{
		outputBox->Text += "Client connected!\r\n\r\n";
		outputBox->Text += "Waiting for incoming connections...\r\n";
		TempSock=accept(socket,NULL,NULL);
	}
	socket=TempSock;

	return socket;
}
	
char* ServerChat::Send(char* message)
{

	sendText=message;
	send(socket,sendText,strlen(sendText),0);

	return sendText;
}

char* ServerChat::Receive(RichTextBox^ outputBox)
{
	// Display message from server
	char* buffer;
	memset(buffer,0,999);
	int inDataLength=recv(socket,buffer,1000,0);
	
	return buffer;
}

void ServerChat::Shutdown()
{
	// Shutdown our socket
	shutdown(socket,SD_SEND);
	
	// Close our socket entirely
	closesocket(socket);

	// Cleanup Winsockc
	WSACleanup();
	return ;
}