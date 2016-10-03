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

namespace KinectV2_Acquisition {

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
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::RadioButton^  jpeg_radioButton1;
	private: System::Windows::Forms::RadioButton^  bmp_radioButton2;


	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label7;










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
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->jpeg_radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->bmp_radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(131, 36);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(113, 20);
			this->textBox1->TabIndex = 0;
			this->textBox1->Text = L"C:\\DATA";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(38, 39);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(70, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Record Path:";
			// 
			// recordOptions
			// 
			this->recordOptions->FormattingEnabled = true;
			this->recordOptions->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"Record RGB", L"Record Depth", L"Record Skeleton"});
			this->recordOptions->Location = System::Drawing::Point(131, 72);
			this->recordOptions->Name = L"recordOptions";
			this->recordOptions->Size = System::Drawing::Size(113, 49);
			this->recordOptions->TabIndex = 2;
			this->recordOptions->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::recordOptions_SelectedIndexChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(38, 86);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(84, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Record Options:";
			// 
			// displayOptions
			// 
			this->displayOptions->FormattingEnabled = true;
			this->displayOptions->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"Show RGB", L"Show Depth", L"Show Skeleton"});
			this->displayOptions->Location = System::Drawing::Point(131, 147);
			this->displayOptions->Name = L"displayOptions";
			this->displayOptions->Size = System::Drawing::Size(113, 49);
			this->displayOptions->TabIndex = 4;
			// 
			// startStopButt
			// 
			this->startStopButt->Location = System::Drawing::Point(58, 394);
			this->startStopButt->Name = L"startStopButt";
			this->startStopButt->Size = System::Drawing::Size(186, 23);
			this->startStopButt->TabIndex = 5;
			this->startStopButt->Text = L"DISCO";
			this->startStopButt->UseVisualStyleBackColor = true;
			this->startStopButt->Click += gcnew System::EventHandler(this, &Form1::StartStop);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(38, 164);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(72, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"View Options:";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(131, 334);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(112, 20);
			this->textBox2->TabIndex = 9;
			this->textBox2->Text = L"0.25";
			this->textBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &Form1::textBox2_TextChanged);
			this->textBox2->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::OnkeyDownScale);
			this->textBox2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::OnKeyPressScale);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(128, 318);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(61, 13);
			this->label5->TabIndex = 10;
			this->label5->Text = L"RGB scale ";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(176, 318);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(67, 13);
			this->label6->TabIndex = 11;
			this->label6->Text = L"factor (0 - 1):";
			// 
			// jpeg_radioButton1
			// 
			this->jpeg_radioButton1->AutoSize = true;
			this->jpeg_radioButton1->Checked = true;
			this->jpeg_radioButton1->Location = System::Drawing::Point(13, 19);
			this->jpeg_radioButton1->Name = L"jpeg_radioButton1";
			this->jpeg_radioButton1->Size = System::Drawing::Size(75, 17);
			this->jpeg_radioButton1->TabIndex = 12;
			this->jpeg_radioButton1->TabStop = true;
			this->jpeg_radioButton1->Text = L"jpeg (slow)";
			this->jpeg_radioButton1->UseVisualStyleBackColor = true;
			this->jpeg_radioButton1->CheckedChanged += gcnew System::EventHandler(this, &Form1::jpeg_checkChanged);
			// 
			// bmp_radioButton2
			// 
			this->bmp_radioButton2->AutoSize = true;
			this->bmp_radioButton2->Location = System::Drawing::Point(13, 42);
			this->bmp_radioButton2->Name = L"bmp_radioButton2";
			this->bmp_radioButton2->Size = System::Drawing::Size(68, 17);
			this->bmp_radioButton2->TabIndex = 13;
			this->bmp_radioButton2->Text = L"bmp (big)";
			this->bmp_radioButton2->UseVisualStyleBackColor = true;
			this->bmp_radioButton2->CheckedChanged += gcnew System::EventHandler(this, &Form1::bmp_checkChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->jpeg_radioButton1);
			this->groupBox1->Controls->Add(this->bmp_radioButton2);
			this->groupBox1->Location = System::Drawing::Point(131, 228);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(109, 78);
			this->groupBox1->TabIndex = 14;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Encode options";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(43, 251);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(72, 13);
			this->label4->TabIndex = 15;
			this->label4->Text = L"RGB Options:";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(178)));
			this->label7->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label7->Location = System::Drawing::Point(34, 9);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(222, 13);
			this->label7->TabIndex = 16;
			this->label7->Text = L"Make sure the record path does exist!";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(291, 491);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->startStopButt);
			this->Controls->Add(this->displayOptions);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->recordOptions);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Name = L"Form1";
			this->Text = L"Kinect V2 Data Recorder";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 //Inititalise stuff
				 //this->encodeoptions->SetItemCheckState(0,CheckState::Checked);
				 this->recordOptions->SetItemCheckState(0,CheckState::Checked);
				 this->recordOptions->SetItemCheckState(1,CheckState::Checked);
				 this->recordOptions->SetItemCheckState(2,CheckState::Checked);
				 this->displayOptions->SetItemCheckState(0,CheckState::Checked);
				 this->displayOptions->SetItemCheckState(1,CheckState::Checked);
				 this->displayOptions->SetItemCheckState(2,CheckState::Checked);

			 }
	private: System::Void FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
				 //Clean stuff up

			 }


	private: System::Void StartStop(System::Object^  sender, System::EventArgs^  e) {

					m_bRunMainLoop = !m_bRunMainLoop;

					if(m_bRunMainLoop)
					{
					 int numIts = 10000;
					 int numSaves = 300;

					 InitState(); // Must go first to initialise sensor properly
					 if(workclass::InitializeDefaultSensor() == E_FAIL) return;
					 workclass::InitStuff();
					 workclass::mainLoop(numIts, numSaves);

					 workclass::safeClose();
					 destroyAllWindows();

			
					}

			 }

	private:	 void InitState()
				 {
					
					 m_bSaveBody = m_bSaveDepth = m_bSaveRGB =  m_bViewBody = m_bViewDepth = m_bViewRGB = false;
					 //View
					 if (this->displayOptions->GetItemCheckState(0) == CheckState::Checked)
						 m_bViewRGB = true;
					 if (this->displayOptions->GetItemCheckState(1) == CheckState::Checked)
						 m_bViewDepth = true;
					 if (this->displayOptions->GetItemCheckState(2) == CheckState::Checked)
						 m_bViewBody = true;

					 //Save
					 if (this->recordOptions->GetItemCheckState(0) == CheckState::Checked)
						 m_bSaveRGB = true;
					 if (this->recordOptions->GetItemCheckState(1) == CheckState::Checked)
						 m_bSaveDepth = true;
					 if (this->recordOptions->GetItemCheckState(2) == CheckState::Checked)
						 m_bSaveBody = true;

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
private: System::Void recordOptions_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
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
