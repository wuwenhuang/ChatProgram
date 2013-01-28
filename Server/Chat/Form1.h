#include <iostream>
#include <winsock2.h>
#include <process.h>

#pragma comment(lib,"ws2_32.lib")

	WSADATA WsaDat;
	SOCKET mySocket;
	SOCKADDR_IN serverInf;

	bool clientConnect;

	bool messageSent;

namespace Chat {

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

		//void InitializeServer();

		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			if(WSAStartup(MAKEWORD(2,2),&WsaDat)!=0)
			{
				output->Text = "Initialization failed!\r\n";
				WSACleanup();
				return;
			}
			else
			{
				char szPath[128] = "";

				WSAStartup(MAKEWORD(2, 2), &WsaDat);
				gethostname(szPath, sizeof(szPath));

				String^ tempString = gcnew String( s2ws(szPath).c_str());

				IPAddressTextBox->Text = tempString;

				output->Text += "Initialization complete!\n";
			}
	
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

			clientConnect = false;

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

	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::Button^  Send;
	protected: 

	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  Join;
	private: System::Windows::Forms::RichTextBox^  output;
	private: System::Windows::Forms::Button^  sendButton;
	private: System::Windows::Forms::TextBox^  inputTextBox;
	private: System::Windows::Forms::TextBox^  IPAddressTextBox;

	private: System::Windows::Forms::Button^  createButton;


	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->output = (gcnew System::Windows::Forms::RichTextBox());
			this->sendButton = (gcnew System::Windows::Forms::Button());
			this->inputTextBox = (gcnew System::Windows::Forms::TextBox());
			this->IPAddressTextBox = (gcnew System::Windows::Forms::TextBox());
			this->createButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// output
			// 
			this->output->BackColor = System::Drawing::SystemColors::Control;
			this->output->Location = System::Drawing::Point(20, 45);
			this->output->Name = L"output";
			this->output->ReadOnly = true;
			this->output->Size = System::Drawing::Size(434, 342);
			this->output->TabIndex = 0;
			this->output->Text = L"";
			this->output->TextChanged += gcnew System::EventHandler(this, &Form1::output_TextChanged);
			// 
			// sendButton
			// 
			this->sendButton->Location = System::Drawing::Point(369, 402);
			this->sendButton->Name = L"sendButton";
			this->sendButton->Size = System::Drawing::Size(75, 23);
			this->sendButton->TabIndex = 1;
			this->sendButton->Text = L"Send";
			this->sendButton->UseVisualStyleBackColor = true;
			this->sendButton->Click += gcnew System::EventHandler(this, &Form1::sendButton_Click);
			// 
			// inputTextBox
			// 
			this->inputTextBox->Location = System::Drawing::Point(22, 405);
			this->inputTextBox->Name = L"inputTextBox";
			this->inputTextBox->Size = System::Drawing::Size(316, 20);
			this->inputTextBox->TabIndex = 2;
			// 
			// IPAddressTextBox
			// 
			this->IPAddressTextBox->Location = System::Drawing::Point(20, 8);
			this->IPAddressTextBox->Name = L"IPAddressTextBox";
			this->IPAddressTextBox->ReadOnly = true;
			this->IPAddressTextBox->Size = System::Drawing::Size(317, 20);
			this->IPAddressTextBox->TabIndex = 4;
			// 
			// createButton
			// 
			this->createButton->Location = System::Drawing::Point(369, 5);
			this->createButton->Name = L"createButton";
			this->createButton->Size = System::Drawing::Size(75, 23);
			this->createButton->TabIndex = 5;
			this->createButton->Text = L"Create";
			this->createButton->UseVisualStyleBackColor = true;
			this->createButton->Click += gcnew System::EventHandler(this, &Form1::createButton_Click_1);
			// 
			// Form1
			// 
			this->ClientSize = System::Drawing::Size(472, 432);
			this->Controls->Add(this->createButton);
			this->Controls->Add(this->IPAddressTextBox);
			this->Controls->Add(this->inputTextBox);
			this->Controls->Add(this->sendButton);
			this->Controls->Add(this->output);
			this->Name = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion
	
private: 

	System::Void sendButton_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		char *szMessage = (char*)(void*)Marshal::StringToHGlobalAnsi(inputTextBox->Text);
		
		send(mySocket,szMessage,strlen(szMessage),0);

		messageSent = true;
		output->Text += inputTextBox->Text;
	}

public:
	delegate void UpdateTextDelegate(String^ text);

	System::Void UpdateText(String^ text) {
		this->output->Text = "Server: " + text + "\n\n";
	}
	
	System::Void Read(void)
	{
		while (1)
		{
			if (clientConnect )
			{
				char buffer[1000];
				int inDataLength=recv(mySocket,buffer,1000,0); 
				String^ tempString = gcnew String( s2ws(buffer).c_str());

				UpdateTextDelegate^ action = gcnew UpdateTextDelegate(this, &Form1::UpdateText);
				this->BeginInvoke(action, tempString);
			}
		}
	} 
private: 

	System::Void createButton_Click_1(System::Object^  sender, System::EventArgs^  e) 
	{
		if (!clientConnect)
		{
			serverInf.sin_family=AF_INET;
			serverInf.sin_addr.s_addr=INADDR_ANY;
			serverInf.sin_port=htons(8888);

			if(bind(mySocket,(SOCKADDR*)(&serverInf),sizeof(serverInf))==SOCKET_ERROR)
			{
				output->Text += "Unable to bind socket!\r\n";
				WSACleanup();
				return;
			}

			output->Text += "listening\n";

			listen(mySocket,1);

			output->Text += "Waiting for incoming connections...\r\n";

			SOCKET TempSock=SOCKET_ERROR;
			int errorNo = WSAGetLastError();
			while(TempSock==SOCKET_ERROR)
			{
				//listen(TempSock,1);

				TempSock=accept(mySocket,NULL,NULL);
			}
			mySocket=TempSock;
			
			output->Text += "Client connected!\r\n\r\n";

			char *szMessage="Welcome to Chat Server!\r\n";
			send(mySocket,szMessage,strlen(szMessage),0);

			clientConnect = true;
		}
		

	}
private: 
	System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) 
	{
		Thread^ readThread = gcnew Thread(gcnew ThreadStart(this, &Chat::Form1::Read));
		readThread->Start();

		
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
};
}

