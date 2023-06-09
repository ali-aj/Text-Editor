#pragma once
#include"TrieTree.h"
#include"HuffMan.h"
#include <msclr\marshal_cppstd.h>
#include<iostream>

namespace windowsFormProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
		TrieTree* trieTree;
		HuffMan* huffMan;
	private: System::Windows::Forms::ListView^ SuggestionBox;
	private: System::Windows::Forms::ColumnHeader^ Number;
	private: System::Windows::Forms::ColumnHeader^ Suggestions;
	private: System::Windows::Forms::Button^ Load;

	private: System::Windows::Forms::Button^ Save;
	private: System::Windows::Forms::Label^ label1;

		   std::string* suggestions;
	public:
		MyForm(void)
		{
			InitializeComponent();
			trieTree = new TrieTree;
			huffMan = new HuffMan;
			trieTree->readFromFile();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
				delete trieTree;
				delete huffMan;
				delete suggestions;
			}
		}
	private: System::Windows::Forms::TextBox^ inputString;


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
			this->inputString = (gcnew System::Windows::Forms::TextBox());
			this->SuggestionBox = (gcnew System::Windows::Forms::ListView());
			this->Number = (gcnew System::Windows::Forms::ColumnHeader());
			this->Suggestions = (gcnew System::Windows::Forms::ColumnHeader());
			this->Load = (gcnew System::Windows::Forms::Button());
			this->Save = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// inputString
			// 
			this->inputString->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->inputString->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->inputString->Font = (gcnew System::Drawing::Font(L"Mongolian Baiti", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->inputString->Location = System::Drawing::Point(1, 12);
			this->inputString->Multiline = true;
			this->inputString->Name = L"inputString";
			this->inputString->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->inputString->Size = System::Drawing::Size(1018, 116);
			this->inputString->TabIndex = 0;
			this->inputString->TextChanged += gcnew System::EventHandler(this, &MyForm::inputString_TextChanged);
			// 
			// SuggestionBox
			// 
			this->SuggestionBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->SuggestionBox->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) { this->Number, this->Suggestions });
			this->SuggestionBox->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SuggestionBox->HideSelection = false;
			this->SuggestionBox->Location = System::Drawing::Point(1, 211);
			this->SuggestionBox->MultiSelect = false;
			this->SuggestionBox->Name = L"SuggestionBox";
			this->SuggestionBox->Size = System::Drawing::Size(748, 479);
			this->SuggestionBox->TabIndex = 1;
			this->SuggestionBox->UseCompatibleStateImageBehavior = false;
			this->SuggestionBox->View = System::Windows::Forms::View::Details;
			this->SuggestionBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::SuggestionBox_SelectedIndexChanged);
			// 
			// Number
			// 
			this->Number->Text = L" Num";
			// 
			// Suggestions
			// 
			this->Suggestions->Text = L"Suggestions";
			this->Suggestions->Width = 545;
			// 
			// Load
			// 
			this->Load->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->Load->BackColor = System::Drawing::SystemColors::MenuBar;
			this->Load->Font = (gcnew System::Drawing::Font(L"Modern No. 20", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Load->Location = System::Drawing::Point(768, 635);
			this->Load->Name = L"Load";
			this->Load->Size = System::Drawing::Size(124, 55);
			this->Load->TabIndex = 2;
			this->Load->Text = L"Load";
			this->Load->UseVisualStyleBackColor = false;
			this->Load->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// Save
			// 
			this->Save->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->Save->BackColor = System::Drawing::SystemColors::ScrollBar;
			this->Save->Font = (gcnew System::Drawing::Font(L"Modern No. 20", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Save->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->Save->Location = System::Drawing::Point(898, 635);
			this->Save->Name = L"Save";
			this->Save->Size = System::Drawing::Size(121, 55);
			this->Save->TabIndex = 3;
			this->Save->Text = L"Save";
			this->Save->UseVisualStyleBackColor = false;
			this->Save->Click += gcnew System::EventHandler(this, &MyForm::Save_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Palatino Linotype", 18, static_cast<System::Drawing::FontStyle>(((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)
				| System::Drawing::FontStyle::Underline)), System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(-7, 160);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(219, 48);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Suggestions:";
			this->label1->UseMnemonic = false;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->ClientSize = System::Drawing::Size(1031, 702);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->Save);
			this->Controls->Add(this->Load);
			this->Controls->Add(this->SuggestionBox);
			this->Controls->Add(this->inputString);
			this->KeyPreview = true;
			this->MinimumSize = System::Drawing::Size(778, 718);
			this->Name = L"MyForm";
			this->Text = L"Text Editor";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		System::Void inputString_TextChanged(System::Object^ sender, System::EventArgs^ e) {
			suggestions = new std::string[50];
			for (int i = 0; i < 50; i++)
				suggestions[i] = "";
			if (this->inputString->Text != "") {
				std::string inputData = msclr::interop::marshal_as<std::string>(this->inputString->Text);
				trieTree->typingText(suggestions, inputData[inputData.length() - 1], inputData);
				addSuggestions(suggestions);
			}
		}

		void addSuggestions(std::string* suggestions) {
			SuggestionBox->Items->Clear();
			int ID = 1;
			for (int i = 0; i < 50; i++) {
				if (suggestions[i].length() == 0)
					break;
				this->SuggestionBox->Items->Add(ID.ToString());
				this->SuggestionBox->Items[i]->SubItems->Add(gcnew String(suggestions[i].c_str()));
				ID++;
			}
		}
	private: System::Void suggestions_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {

	}


	private: System::Void SuggestionBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		std::string item = msclr::interop::marshal_as<std::string>(this->SuggestionBox->SelectedItems[0]->SubItems[1]->Text);
		std::string temp = msclr::interop::marshal_as<std::string>(this->inputString->Text);
		for (int i = temp.length() - 1; i >= 0; i--) {
			if (temp[i] == ' ') {
				std::string currentWord = "";
				for (int j = 0; j <= i; j++)
					currentWord += temp[j];
				temp = currentWord + item;
				this->inputString->Text = gcnew String(temp.c_str());
				return;
			}
		}
		this->inputString->Text = this->SuggestionBox->SelectedItems[0]->SubItems[1]->Text;
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		std::string temp = huffMan->readFromFile();
		if (!temp.empty()) {
			this->inputString->Text = gcnew String(temp.c_str());
			trieTree->typingText(suggestions, temp[temp.length() - 1], temp);
			addSuggestions(suggestions);
		}
	}
	private: System::Void Save_Click(System::Object^ sender, System::EventArgs^ e) {
		std::string inputData = msclr::interop::marshal_as<std::string>(this->inputString->Text);
		if (!inputData.empty())
			huffMan->compressString(inputData);
	}
};
}
