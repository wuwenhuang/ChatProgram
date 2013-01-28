#include <iostream>
#include <process.h>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib")

WSADATA WsaDat;
SOCKET mySocket;
SOCKADDR_IN serverInf;

bool serverConnect;
bool messageSent;

namespace ClientChat {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace System::Threading;

	/// <summary>
	/// Summary for Form1
	/// </summary>

	

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			// Initialise Winsock
			
			if(WSAStartup(MAKEWORD(2,2),&WsaDat)!=0)
			{
				output->Text = "Initialization failed!\r\n";
				WSACleanup();
				return;
			}
			else
			{
				output->Text += "Initialization complete!\n";
			}
	
			// Create our socket
			mySocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
			if(mySocket==INVALID_SOCKET)
			{
				output->Text += "Socket creation failed.\r\n";
				WSACleanup();
				return;
			}
			else
			{
				output->Text += "Socket creation complete!\n";
			}

			serverConnect = false;

			messageSent = false;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^  output;
	private: System::Windows::Forms::TextBox^  inputTextBox;
	private: System::Windows::Forms::Button^  sendButton;
	protected: 

	protected: 


	private: System::Windows::Forms::TextBox^  ServerIPAddressTextBox;
	private: System::Windows::Forms::Button^  JoinButton;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->output = (gcnew System::Windows::Forms::RichTextBox());
			this->inputTextBox = (gcnew System::Windows::Forms::TextBox());
			this->sendButton = (gcnew System::Windows::Forms::Button());
			this->ServerIPAddressTextBox = (gcnew System::Windows::Forms::TextBox());
			this->JoinButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// output
			// 
			this->output->BackColor = System::Drawing::SystemColors::Control;
			this->output->Location = System::Drawing::Point(6, 50);
			this->output->Name = L"output";
			this->output->ReadOnly = true;
			this->output->Size = System::Drawing::Size(391, 313);
			this->output->TabIndex = 0;
			this->output->Text = L"";
			this->output->TextChanged += gcnew System::EventHandler(this, &Form1::output_TextChanged);
			// 
			// inputTextBox
			// 
			this->inputTextBox->Location = System::Drawing::Point(6, 378);
			this->inputTextBox->Name = L"inputTextBox";
			this->inputTextBox->Size = System::Drawing::Size(309, 20);
			this->inputTextBox->TabIndex = 1;
			// 
			// sendButton
			// 
			this->sendButton->Location = System::Drawing::Point(322, 376);
			this->sendButton->Name = L"sendButton";
			this->sendButton->Size = System::Drawing::Size(75, 25);
			this->sendButton->TabIndex = 2;
			this->sendButton->Text = L"Send";
			this->sendButton->UseVisualStyleBackColor = true;
			this->sendButton->Click += gcnew System::EventHandler(this, &Form1::sendButton_Click);
			// 
			// ServerIPAddressTextBox
			// 
			this->ServerIPAddressTextBox->Location = System::Drawing::Point(9, 14);
			this->ServerIPAddressTextBox->Name = L"ServerIPAddressTextBox";
			this->ServerIPAddressTextBox->Size = System::Drawing::Size(280, 20);
			this->ServerIPAddressTextBox->TabIndex = 3;
			this->ServerIPAddressTextBox->TextChanged += gcnew System::EventHandler(this, &Form1::ServerIPAddressTextBox_TextChanged);
			// 
			// JoinButton
			// 
			this->JoinButton->Location = System::Drawing::Point(322, 14);
			this->JoinButton->Name = L"JoinButton";
			this->JoinButton->Size = System::Drawing::Size(75, 25);
			this->JoinButton->TabIndex = 4;
			this->JoinButton->Text = L"Join";
			this->JoinButton->UseVisualStyleBackColor = true;
			this->JoinButton->Click += gcnew System::EventHandler(this, &Form1::JoinButton_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(409, 414);
			this->Controls->Add(this->JoinButton);
			this->Controls->Add(this->ServerIPAddressTextBox);
			this->Controls->Add(this->sendButton);
			this->Controls->Add(this->inputTextBox);
			this->Controls->Add(this->output);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		System::Void JoinButton_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if (!serverConnect)
			{
				char *serverName = (char*)(void*)Marshal::StringToHGlobalAnsi(ServerIPAddressTextBox->Text);
				// Resolve IP address for hostname
				struct hostent *host;
				if((host=gethostbyname(serverName))==NULL)
				{
					output->Text += "Failed to resolve hostname.\r\n";
					WSACleanup();
				}
				else
				{
					output->Text += "Resolve hostname successfully!\r\n";
				}

				// Setup our socket address structure
				SOCKADDR_IN SockAddr;
				SockAddr.sin_port=htons(8888);
				SockAddr.sin_family=AF_INET;
				SockAddr.sin_addr.s_addr=*((unsigned long*)host->h_addr);
				
				// Attempt to connect to server
				if(connect(mySocket,(SOCKADDR*)(&SockAddr),sizeof(SockAddr))!=0)
				{
					output->Text += "Failed to establish connection with server\r\n";
					WSACleanup();
				}
				else
				{
					serverConnect = true;
					output->Text += "Establish connection with server successfully!\r\n";

					
				}
			}
		}

public:
	delegate void UpdateTextDelegate(String^ text);

	System::Void UpdateText(String^ text) {
		this->output->Text += "Client: " + text + "\n\n";
	}

	System::Void Read(void)
	{
		while(1)
		{
			if (serverConnect)
			{	
				char buffer[1000];
				int inDataLength=recv(mySocket,buffer,1000,0);
				String^ tempString = gcnew String( s2ws(buffer).c_str());

				UpdateTextDelegate^ action = gcnew UpdateTextDelegate(this, &Form1::UpdateText);
				this->BeginInvoke(action, tempString);
			}
		}
	}

	System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e)
	{
		Thread^ readThread = gcnew Thread(gcnew ThreadStart(this, &ClientChat::Form1::Read));
		readThread->Start();
	}
private: 
	System::Void sendButton_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		char *szMessage = (char*)(void*)Marshal::StringToHGlobalAnsi(inputTextBox->Text);
		
		send(mySocket,szMessage,strlen(szMessage),0);

		output->Text += inputTextBox->Text;

		messageSent = true;
	}

	std::wstring s2ws(const std::string& s)
	{
		int len;
		int slength = (int)s.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
		std::wstring r(buf);
		delete[] buf;
		return r;
	}
private: 
	System::Void output_TextChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		
	}
private: System::Void ServerIPAddressTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
		 }
};
}

