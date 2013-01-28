//#include "Client.h"
//
//void Client::Initialize()
//{
//	// Initialise Winsock
//	WSADATA WsaDat;
//	if(WSAStartup(MAKEWORD(2,2),&WsaDat)!=0)
//	{
//		std::cout<<"Winsock error - Winsock initialization failed\r\n";
//		WSACleanup();
//		system("PAUSE");
//		return;
//	}
//}
//
//bool Client::Join()
//{
//	// Create our socket
//	SOCKET Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
//	if(Socket==INVALID_SOCKET)
//	{
//		std::cout<<"Winsock error - Socket creation Failed!\r\n";
//		WSACleanup();
//		system("PAUSE");
//		return 0;
//	}
//
//	// Resolve IP address for hostname
//	struct hostent *host;
//	if((host=gethostbyname("localhost"))==NULL)
//	{
//		std::cout<<"Failed to resolve hostname.\r\n";
//		WSACleanup();
//		system("PAUSE");
//		return 0;
//	}
//
//	// Setup our socket address structure
//	SOCKADDR_IN SockAddr;
//	SockAddr.sin_port=htons(8888);
//	SockAddr.sin_family=AF_INET;
//	SockAddr.sin_addr.s_addr=*((unsigned long*)host->h_addr);
//
//	// Attempt to connect to server
//	if(connect(Socket,(SOCKADDR*)(&SockAddr),sizeof(SockAddr))!=0)
//	{
//		std::cout<<"Failed to establish connection with server\r\n";
//		WSACleanup();
//		system("PAUSE");
//		return 0;
//	}
//}
//
//char* Client::Send(char* message)
//{
//	sendText=message;
//	send(Socket,szMessage,strlen(sendText),0);
//
//	return sendText;
//}
//
//char* Client::Receive()
//{
//	// Display message from server
//	char* buffer[1000];
//	memset(buffer,0,999);
//	int inDataLength=recv(Socket,buffer,1000,0);
//	
//	return buffer;
//}
//
//void Client::Shutdown()
//{
//	// Shutdown our socket
//	shutdown(Socket,SD_SEND);
//
//	// Close our socket entirely
//	closesocket(Socket);
//
//	// Cleanup Winsock
//	WSACleanup();
//	return;
//}