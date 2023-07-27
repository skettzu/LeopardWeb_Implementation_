#pragma once

namespace LeopardWebImplementationGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Login
	/// </summary>
	public ref class Login : public System::Windows::Forms::Form
	{
	public:
		Login(void)
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
		~Login()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ Logon;
	protected:

	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ Username;
	private: System::Windows::Forms::Label^ Password;


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
			this->Logon = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->Username = (gcnew System::Windows::Forms::Label());
			this->Password = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// Logon
			// 
			this->Logon->Location = System::Drawing::Point(96, 174);
			this->Logon->Name = L"Logon";
			this->Logon->Size = System::Drawing::Size(93, 37);
			this->Logon->TabIndex = 0;
			this->Logon->Text = L"Logon";
			this->Logon->UseVisualStyleBackColor = true;
			this->Logon->Click += gcnew System::EventHandler(this, &Login::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(96, 130);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(146, 22);
			this->textBox1->TabIndex = 1;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &Login::textBox1_TextChanged);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(96, 90);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(146, 22);
			this->textBox2->TabIndex = 2;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &Login::textBox2_TextChanged);
			// 
			// Username
			// 
			this->Username->AutoSize = true;
			this->Username->Location = System::Drawing::Point(20, 90);
			this->Username->Name = L"Username";
			this->Username->Size = System::Drawing::Size(70, 16);
			this->Username->TabIndex = 3;
			this->Username->Text = L"Username";
			this->Username->Click += gcnew System::EventHandler(this, &Login::label1_Click);
			// 
			// Password
			// 
			this->Password->AutoSize = true;
			this->Password->Location = System::Drawing::Point(23, 133);
			this->Password->Name = L"Password";
			this->Password->Size = System::Drawing::Size(67, 16);
			this->Password->TabIndex = 4;
			this->Password->Text = L"Password";
			this->Password->Click += gcnew System::EventHandler(this, &Login::label1_Click_1);
			// 
			// Login
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(282, 253);
			this->Controls->Add(this->Password);
			this->Controls->Add(this->Username);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->Logon);
			this->Name = L"Login";
			this->Text = L"Login";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		if () {
			// Add code that checks credential
		}
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label1_Click_1(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
};
}
