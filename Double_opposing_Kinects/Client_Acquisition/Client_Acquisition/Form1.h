///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////                          University of Bristol                          ////////////////
//////////////                       Computer Science Department                       ////////////////
//===================================================================================================//
///////                            This is an open source code for:                             ///////
////////           "3D Data Acquisition and Registration using Two Opposing Kinects"         //////////
////////////////      V. Soleimani, M. Mirmehdi, D. Damen, S. Hannuna, M. Camplani    /////////////////
////////////////         International Conference on 3D Vision, Stanford, 2016        /////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "workclass.h"

namespace Client_Acquisition {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;


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
	private: System::Windows::Forms::TextBox^  textBox1;
	protected: 
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::CheckedListBox^  recordOptions;


	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::CheckedListBox^  displayOptions;
	private: System::Windows::Forms::Button^  startStopButt;
	private: System::Windows::Forms::Label^  label3;


	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label5;

	private: System::Windows::Forms::RadioButton^  jpeg_radioButton1;
	private: System::Windows::Forms::RadioButton^  bmp_radioButton2;


	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  label4;




	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label6;







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
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->recordOptions = (gcnew System::Windows::Forms::CheckedListBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->displayOptions = (gcnew System::Windows::Forms::CheckedListBox());
			this->startStopButt = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->jpeg_radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->bmp_radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(189, 38);
			this->textBox1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(149, 22);
			this->textBox1->TabIndex = 0;
			this->textBox1->Text = L"C:\\DATA";
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(51, 42);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(91, 17);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Record Path:";
			// 
			// recordOptions
			// 
			this->recordOptions->Enabled = false;
			this->recordOptions->FormattingEnabled = true;
			this->recordOptions->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"Record RGB", L"Record Depth", L"Record Skeleton"});
			this->recordOptions->Location = System::Drawing::Point(189, 79);
			this->recordOptions->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->recordOptions->Name = L"recordOptions";
			this->recordOptions->Size = System::Drawing::Size(149, 72);
			this->recordOptions->TabIndex = 2;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(51, 78);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(111, 17);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Record Options:";
			// 
			// displayOptions
			// 
			this->displayOptions->Enabled = false;
			this->displayOptions->FormattingEnabled = true;
			this->displayOptions->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"Show RGB", L"Show Depth", L"Show Skeleton"});
			this->displayOptions->Location = System::Drawing::Point(189, 151);
			this->displayOptions->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->displayOptions->Name = L"displayOptions";
			this->displayOptions->Size = System::Drawing::Size(149, 72);
			this->displayOptions->TabIndex = 4;
			// 
			// startStopButt
			// 
			this->startStopButt->Location = System::Drawing::Point(200, 402);
			this->startStopButt->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->startStopButt->Name = L"startStopButt";
			this->startStopButt->Size = System::Drawing::Size(133, 33);
			this->startStopButt->TabIndex = 5;
			this->startStopButt->Text = L"Kinect ON!";
			this->startStopButt->UseVisualStyleBackColor = true;
			this->startStopButt->Click += gcnew System::EventHandler(this, &Form1::StartStop);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(51, 150);
			this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(94, 17);
			this->label3->TabIndex = 6;
			this->label3->Text = L"View Options:";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(200, 370);
			this->textBox2->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(132, 22);
			this->textBox2->TabIndex = 9;
			this->textBox2->Text = L"0.5";
			this->textBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &Form1::textBox2_TextChanged);
			this->textBox2->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::OnkeyDownScale);
			this->textBox2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::OnKeyPressScale);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(199, 351);
			this->label5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(114, 17);
			this->label5->TabIndex = 10;
			this->label5->Text = L"RGB scale (0-1):";
			// 
			// jpeg_radioButton1
			// 
			this->jpeg_radioButton1->AutoSize = true;
			this->jpeg_radioButton1->Checked = true;
			this->jpeg_radioButton1->Location = System::Drawing::Point(17, 23);
			this->jpeg_radioButton1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->jpeg_radioButton1->Name = L"jpeg_radioButton1";
			this->jpeg_radioButton1->Size = System::Drawing::Size(97, 21);
			this->jpeg_radioButton1->TabIndex = 12;
			this->jpeg_radioButton1->TabStop = true;
			this->jpeg_radioButton1->Text = L"jpeg (slow)";
			this->jpeg_radioButton1->UseVisualStyleBackColor = true;
			this->jpeg_radioButton1->CheckedChanged += gcnew System::EventHandler(this, &Form1::jpeg_checkChanged);
			// 
			// bmp_radioButton2
			// 
			this->bmp_radioButton2->AutoSize = true;
			this->bmp_radioButton2->Location = System::Drawing::Point(17, 52);
			this->bmp_radioButton2->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->bmp_radioButton2->Name = L"bmp_radioButton2";
			this->bmp_radioButton2->Size = System::Drawing::Size(89, 21);
			this->bmp_radioButton2->TabIndex = 13;
			this->bmp_radioButton2->Text = L"bmp (big)";
			this->bmp_radioButton2->UseVisualStyleBackColor = true;
			this->bmp_radioButton2->CheckedChanged += gcnew System::EventHandler(this, &Form1::bmp_checkChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->jpeg_radioButton1);
			this->groupBox1->Controls->Add(this->bmp_radioButton2);
			this->groupBox1->Location = System::Drawing::Point(189, 240);
			this->groupBox1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBox1->Size = System::Drawing::Size(145, 96);
			this->groupBox1->TabIndex = 14;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Encode options";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(52, 241);
			this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(95, 17);
			this->label4->TabIndex = 15;
			this->label4->Text = L"RGB Options:";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(51, 370);
			this->textBox3->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(132, 22);
			this->textBox3->TabIndex = 18;
			this->textBox3->Text = L"192.168.1.20";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(47, 351);
			this->label7->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(70, 17);
			this->label7->TabIndex = 19;
			this->label7->Text = L"Server IP:";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(49, 402);
			this->button2->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(133, 33);
			this->button2->TabIndex = 20;
			this->button2->Text = L"Connect!";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(48, 11);
			this->label6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(282, 17);
			this->label6->TabIndex = 21;
			this->label6->Text = L"Make sure the record path does exist!";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(388, 604);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->startStopButt);
			this->Controls->Add(this->displayOptions);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->recordOptions);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Name = L"Form1";
			this->Text = L"Client_Acquisition";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 //Inititalise stuff
			 }
	private: System::Void FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
				 //Clean stuff up
			 }


	private: System::Void StartStop(System::Object^  sender, System::EventArgs^  e) {

			m_bRunMainLoop = !m_bRunMainLoop;
			startStopButt->Enabled = false;

			if(m_bRunMainLoop)
			{
				int numIts = 10000;
				int numSaves = 300;

				InitState(); // Must go first to initialise sensor properly
				recv(ConnectSocket, recvbuf, recvbuflen, 0);
				m_bSaveRGB=(recvbuf[0]=='R'?true:false);
				m_bSaveDepth=(recvbuf[1]=='D'?true:false);
				m_bSaveBody=(recvbuf[2]=='B'?true:false);
				m_bViewRGB=(recvbuf[3]=='r'?true:false);
				m_bViewDepth=(recvbuf[4]=='d'?true:false);
				m_bViewBody=(recvbuf[5]=='b'?true:false);
				if (m_bSaveRGB) this->recordOptions->SetItemCheckState(0,CheckState::Checked);
				if (m_bSaveDepth) this->recordOptions->SetItemCheckState(1,CheckState::Checked);
				if (m_bSaveBody) this->recordOptions->SetItemCheckState(2,CheckState::Checked);
				if (m_bViewRGB) this->displayOptions->SetItemCheckState(0,CheckState::Checked);
				if (m_bViewDepth)this->displayOptions->SetItemCheckState(1,CheckState::Checked);
				if (m_bViewBody) this->displayOptions->SetItemCheckState(2,CheckState::Checked);

				if(workclass::InitializeDefaultSensor() == E_FAIL) return;
				workclass::InitStuff();
				workclass::mainLoop(numIts, numSaves);
				workclass::safeClose();
				destroyAllWindows();
			
			}
				
		}

	private:	 void InitState()
		{
					
			m_bSaveForce = m_bSaveBody = m_bSaveDepth = m_bSaveRGB =  m_bViewBody = m_bViewDepth = m_bViewRGB = m_bViewForce = false;

			IntPtr ptrToNativeString = Marshal::StringToHGlobalAnsi( this->textBox1->Text);
			char* cp = static_cast<char*>(ptrToNativeString.ToPointer());
			strcpy(cpRootDirect,cp);

			ptrToNativeString = Marshal::StringToHGlobalAnsi( this->textBox2->Text);
			cp = static_cast<char*>(ptrToNativeString.ToPointer());
			m_fRGBscaleFactor = atof(cp);
					
			m_iHeight = this->Height;
			m_iLeft = this->Left;
			m_iWidth = this->Width;
			m_iTop = this->Top;
				
		}



	private: System::Void OnRGBEncodeOptionsCheck(System::Object^  sender, System::Windows::Forms::ItemCheckEventArgs^  e) {
			 }
	private: System::Void jpeg_checkChanged(System::Object^  sender, System::EventArgs^  e) {
				 m_bUseJPGencode = !m_bUseJPGencode;	
				 
			 }
	private: System::Void bmp_checkChanged(System::Object^  sender, System::EventArgs^  e) {
				 m_bUseBMPencode = !m_bUseBMPencode;	
				 
			 }
	private: System::Void OnkeyDownScale(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {


			 }
	private: System::Void OnKeyPressScale(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
				 if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar) &&
					 (e->KeyChar != '.'))
				 {
					 e->Handled = true;
				 }

			 }

private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {

			IntPtr ptrToNativeString = Marshal::StringToHGlobalAnsi( this->textBox3->Text);
			char* IP = static_cast<char*>(ptrToNativeString.ToPointer());
			WSADATA wsaData;
			int iResult;
			struct addrinfo *result = NULL,	*ptr = NULL,hints;
			char *sendbuf = "send flag";


	
			// Initialize Winsock
			iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
			if (iResult != 0) {
				exit(-1);
			}
			ZeroMemory( &hints, sizeof(hints) );
			hints.ai_family = AF_UNSPEC;
			hints.ai_socktype = SOCK_STREAM;
			hints.ai_protocol = IPPROTO_TCP;
			// Resolve the server address and port
			iResult = getaddrinfo(IP, DEFAULT_PORT, &hints, &result);
			if ( iResult != 0 ) {
				WSACleanup();
				exit(-1);
			}
			// Attempt to connect to an address until one succeeds
			for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {
				// Create a SOCKET for connecting to server
				ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,ptr->ai_protocol);
				if (ConnectSocket == INVALID_SOCKET) {
					WSACleanup();
					exit(-1);
				}
				// Connect to server.
				iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
				if (iResult == SOCKET_ERROR) {
					closesocket(ConnectSocket);
					ConnectSocket = INVALID_SOCKET;
					continue;
				}
				break;
			}
			freeaddrinfo(result);
			if (ConnectSocket == INVALID_SOCKET) {
				WSACleanup();
				exit(-1);
			}
			this->button2->Enabled = false;

		 }
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }

};
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////                          University of Bristol                          ////////////////
//////////////                       Computer Science Department                       ////////////////
//===================================================================================================//
///////                            This is an open source code for:                             ///////
////////           "3D Data Acquisition and Registration using Two Opposing Kinects"         //////////
////////////////      V. Soleimani, M. Mirmehdi, D. Damen, S. Hannuna, M. Camplani    /////////////////
////////////////         International Conference on 3D Vision, Stanford, 2016        /////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
