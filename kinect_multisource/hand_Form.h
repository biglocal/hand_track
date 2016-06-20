#pragma once

namespace kinect_multisource {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for hand_Form
	/// </summary>
	public ref class hand_Form : public System::Windows::Forms::Form
	{
	public:
		hand_Form(void)
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
		~hand_Form()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::ListBox^  lb_log;
	public: System::Windows::Forms::PictureBox^  pic_result;
	public:
	protected:

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
			this->lb_log = (gcnew System::Windows::Forms::ListBox());
			this->pic_result = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pic_result))->BeginInit();
			this->SuspendLayout();
			// 
			// lb_log
			// 
			this->lb_log->FormattingEnabled = true;
			this->lb_log->ItemHeight = 12;
			this->lb_log->Location = System::Drawing::Point(12, 460);
			this->lb_log->Name = L"lb_log";
			this->lb_log->Size = System::Drawing::Size(512, 88);
			this->lb_log->TabIndex = 0;
			// 
			// pic_result
			// 
			this->pic_result->Location = System::Drawing::Point(12, 12);
			this->pic_result->Name = L"pic_result";
			this->pic_result->Size = System::Drawing::Size(512, 424);
			this->pic_result->TabIndex = 1;
			this->pic_result->TabStop = false;
			// 
			// hand_Form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(550, 563);
			this->Controls->Add(this->pic_result);
			this->Controls->Add(this->lb_log);
			this->Name = L"hand_Form";
			this->Text = L"hand_Form";
			this->Load += gcnew System::EventHandler(this, &hand_Form::hand_Form_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pic_result))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void hand_Form_Load(System::Object^  sender, System::EventArgs^  e);
	};
}
