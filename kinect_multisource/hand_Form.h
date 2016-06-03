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
			this->SuspendLayout();
			// 
			// lb_log
			// 
			this->lb_log->FormattingEnabled = true;
			this->lb_log->ItemHeight = 12;
			this->lb_log->Location = System::Drawing::Point(12, 506);
			this->lb_log->Name = L"lb_log";
			this->lb_log->Size = System::Drawing::Size(518, 88);
			this->lb_log->TabIndex = 0;
			// 
			// hand_Form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(672, 606);
			this->Controls->Add(this->lb_log);
			this->Name = L"hand_Form";
			this->Text = L"hand_Form";
			this->Load += gcnew System::EventHandler(this, &hand_Form::hand_Form_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void hand_Form_Load(System::Object^  sender, System::EventArgs^  e);
	};
}
