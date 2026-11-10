#pragma once

namespace N3CTDLGT {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for CodeNote_N3
	/// </summary>
	public ref class CodeNote_N3 : public System::Windows::Forms::Form
	{
	public:
		CodeNote_N3(void)
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
		~CodeNote_N3()
		{
			if (components)
			{
				delete components;
			}
		}
    private: System::Windows::Forms::Label^ label35;
    protected:
    private: System::Windows::Forms::Label^ label34;
    private: System::Windows::Forms::Panel^ panel6;
    private: System::Windows::Forms::Label^ label33;
    private: System::Windows::Forms::Panel^ panel5;
    private: System::Windows::Forms::Label^ label32;
    private: System::Windows::Forms::Panel^ panel4;
    private: System::Windows::Forms::Label^ label31;
    private: System::Windows::Forms::Panel^ panel1;
    private: System::Windows::Forms::Panel^ panel2;
    private: System::Windows::Forms::Panel^ panel3;
    private: System::Windows::Forms::PictureBox^ pictureBox2;
    private: System::Windows::Forms::PictureBox^ pictureBox1;
    private: System::Windows::Forms::TextBox^ textBox3;
    private: System::Windows::Forms::Label^ label23;
    private: System::Windows::Forms::Label^ label3;
    private: System::Windows::Forms::Label^ lbl_Words;
    private: System::Windows::Forms::Label^ label29;
    private: System::Windows::Forms::Label^ label6;
    private: System::Windows::Forms::ToolStrip^ toolStrip1;
    private: System::Windows::Forms::ToolStripButton^ toolStripButton1;
    private: System::Windows::Forms::ToolStripButton^ toolStripButton2;
    private: System::Windows::Forms::ToolStripButton^ toolStripButton3;
    private: System::Windows::Forms::ToolStripButton^ toolStripButton4;
    private: System::Windows::Forms::ToolStripButton^ toolStripButton5;
    private: System::Windows::Forms::ToolStripButton^ toolStripButton6;
    private: System::Windows::Forms::ToolStripButton^ toolStripButton7;
    private: System::Windows::Forms::ToolStripButton^ toolStripButton8;
    private: System::Windows::Forms::ToolStripMenuItem^ thêmToolStripMenuItem;
    private: System::Windows::Forms::TextBox^ textBox2;
    private: System::Windows::Forms::ToolStripMenuItem^ chỉnhSửaToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ côngCụToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ trợGiúpToolStripMenuItem;
    private: System::Windows::Forms::RichTextBox^ richTextBox1;
    private: System::Windows::Forms::MenuStrip^ menuStrip1;
    private: System::Windows::Forms::Label^ label5;
    private: System::Windows::Forms::TextBox^ textBox6;
    private: System::Windows::Forms::GroupBox^ groupBox5;
    private: System::Windows::Forms::Label^ label21;
    private: System::Windows::Forms::Label^ label10;
    private: System::Windows::Forms::NumericUpDown^ numericUpDown1;
    private: System::Windows::Forms::Label^ label18;
    private: System::Windows::Forms::Label^ label19;
    private: System::Windows::Forms::Label^ label20;
    private: System::Windows::Forms::Label^ label12;
    private: System::Windows::Forms::Label^ lbl_ngoac_vuong;
    private: System::Windows::Forms::Label^ lbl_ngoac_nhon;
    private: System::Windows::Forms::TextBox^ textBox4;
    private: System::Windows::Forms::GroupBox^ groupBox4;
    private: System::Windows::Forms::Button^ btn_timkiem;
    private: System::Windows::Forms::CheckBox^ checkBox1;
    private: System::Windows::Forms::RadioButton^ radioButton2;
    private: System::Windows::Forms::RadioButton^ radioButton1;
    private: System::Windows::Forms::TextBox^ txt_tukhoa;
    private: System::Windows::Forms::Label^ label24;
    private: System::Windows::Forms::Label^ label25;
    private: System::Windows::Forms::Label^ label26;
    private: System::Windows::Forms::Label^ label27;
    private: System::Windows::Forms::Label^ label13;
    private: System::Windows::Forms::Panel^ panel7;
    private: System::Windows::Forms::GroupBox^ groupBox3;
    private: System::Windows::Forms::TextBox^ textBox5;
    private: System::Windows::Forms::Button^ button1;
    private: System::Windows::Forms::Label^ label11;
    private: System::Windows::Forms::Label^ label16;
    private: System::Windows::Forms::Label^ label17;
    private: System::Windows::Forms::Label^ label15;
    private: System::Windows::Forms::Label^ label14;
    private: System::Windows::Forms::Label^ label30;
    private: System::Windows::Forms::Label^ lbl_ngoac_tron;
    private: System::Windows::Forms::Label^ label9;
    private: System::Windows::Forms::Label^ label8;
    private: System::Windows::Forms::Label^ label7;
    private: System::Windows::Forms::Label^ label2;
    private: System::Windows::Forms::TextBox^ textBox1;
    private: System::Windows::Forms::GroupBox^ groupBox1;
    private: System::Windows::Forms::Label^ label22;
    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::Label^ label4;
    private: System::Windows::Forms::GroupBox^ groupBox2;
    private: System::Windows::Forms::Label^ label28;

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
            this->label35 = (gcnew System::Windows::Forms::Label());
            this->label34 = (gcnew System::Windows::Forms::Label());
            this->panel6 = (gcnew System::Windows::Forms::Panel());
            this->label33 = (gcnew System::Windows::Forms::Label());
            this->panel5 = (gcnew System::Windows::Forms::Panel());
            this->label32 = (gcnew System::Windows::Forms::Label());
            this->panel4 = (gcnew System::Windows::Forms::Panel());
            this->label31 = (gcnew System::Windows::Forms::Label());
            this->panel1 = (gcnew System::Windows::Forms::Panel());
            this->panel2 = (gcnew System::Windows::Forms::Panel());
            this->panel3 = (gcnew System::Windows::Forms::Panel());
            this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
            this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
            this->textBox3 = (gcnew System::Windows::Forms::TextBox());
            this->label23 = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->lbl_Words = (gcnew System::Windows::Forms::Label());
            this->label29 = (gcnew System::Windows::Forms::Label());
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
            this->toolStripButton1 = (gcnew System::Windows::Forms::ToolStripButton());
            this->toolStripButton2 = (gcnew System::Windows::Forms::ToolStripButton());
            this->toolStripButton3 = (gcnew System::Windows::Forms::ToolStripButton());
            this->toolStripButton4 = (gcnew System::Windows::Forms::ToolStripButton());
            this->toolStripButton5 = (gcnew System::Windows::Forms::ToolStripButton());
            this->toolStripButton6 = (gcnew System::Windows::Forms::ToolStripButton());
            this->toolStripButton7 = (gcnew System::Windows::Forms::ToolStripButton());
            this->toolStripButton8 = (gcnew System::Windows::Forms::ToolStripButton());
            this->thêmToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->textBox2 = (gcnew System::Windows::Forms::TextBox());
            this->chỉnhSửaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->côngCụToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->trợGiúpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
            this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->textBox6 = (gcnew System::Windows::Forms::TextBox());
            this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
            this->label21 = (gcnew System::Windows::Forms::Label());
            this->label10 = (gcnew System::Windows::Forms::Label());
            this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
            this->label18 = (gcnew System::Windows::Forms::Label());
            this->label19 = (gcnew System::Windows::Forms::Label());
            this->label20 = (gcnew System::Windows::Forms::Label());
            this->label12 = (gcnew System::Windows::Forms::Label());
            this->lbl_ngoac_vuong = (gcnew System::Windows::Forms::Label());
            this->lbl_ngoac_nhon = (gcnew System::Windows::Forms::Label());
            this->textBox4 = (gcnew System::Windows::Forms::TextBox());
            this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
            this->btn_timkiem = (gcnew System::Windows::Forms::Button());
            this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
            this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
            this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
            this->txt_tukhoa = (gcnew System::Windows::Forms::TextBox());
            this->label24 = (gcnew System::Windows::Forms::Label());
            this->label25 = (gcnew System::Windows::Forms::Label());
            this->label26 = (gcnew System::Windows::Forms::Label());
            this->label27 = (gcnew System::Windows::Forms::Label());
            this->label13 = (gcnew System::Windows::Forms::Label());
            this->panel7 = (gcnew System::Windows::Forms::Panel());
            this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
            this->textBox5 = (gcnew System::Windows::Forms::TextBox());
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->label11 = (gcnew System::Windows::Forms::Label());
            this->label16 = (gcnew System::Windows::Forms::Label());
            this->label17 = (gcnew System::Windows::Forms::Label());
            this->label15 = (gcnew System::Windows::Forms::Label());
            this->label14 = (gcnew System::Windows::Forms::Label());
            this->label30 = (gcnew System::Windows::Forms::Label());
            this->lbl_ngoac_tron = (gcnew System::Windows::Forms::Label());
            this->label9 = (gcnew System::Windows::Forms::Label());
            this->label8 = (gcnew System::Windows::Forms::Label());
            this->label7 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->textBox1 = (gcnew System::Windows::Forms::TextBox());
            this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
            this->label22 = (gcnew System::Windows::Forms::Label());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
            this->label28 = (gcnew System::Windows::Forms::Label());
            this->panel1->SuspendLayout();
            this->panel2->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
            this->toolStrip1->SuspendLayout();
            this->menuStrip1->SuspendLayout();
            this->groupBox5->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
            this->groupBox4->SuspendLayout();
            this->groupBox3->SuspendLayout();
            this->groupBox1->SuspendLayout();
            this->groupBox2->SuspendLayout();
            this->SuspendLayout();
            // 
            // label35
            // 
            this->label35->AutoSize = true;
            this->label35->BackColor = System::Drawing::Color::LightGray;
            this->label35->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label35->Location = System::Drawing::Point(1324, 1016);
            this->label35->Name = L"label35";
            this->label35->Size = System::Drawing::Size(169, 23);
            this->label35->TabIndex = 102;
            this->label35->Text = L"Limit undo: x bước";
            this->label35->TextAlign = System::Drawing::ContentAlignment::TopRight;
            // 
            // label34
            // 
            this->label34->AutoSize = true;
            this->label34->BackColor = System::Drawing::Color::LightGray;
            this->label34->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label34->Location = System::Drawing::Point(1158, 1016);
            this->label34->Name = L"label34";
            this->label34->Size = System::Drawing::Size(117, 23);
            this->label34->TabIndex = 100;
            this->label34->Text = L"Chế độ: C++";
            this->label34->TextAlign = System::Drawing::ContentAlignment::TopRight;
            // 
            // panel6
            // 
            this->panel6->Location = System::Drawing::Point(1150, 998);
            this->panel6->Name = L"panel6";
            this->panel6->Size = System::Drawing::Size(2, 57);
            this->panel6->TabIndex = 99;
            // 
            // label33
            // 
            this->label33->AutoSize = true;
            this->label33->BackColor = System::Drawing::Color::LightGray;
            this->label33->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label33->Location = System::Drawing::Point(679, 1016);
            this->label33->Name = L"label33";
            this->label33->Size = System::Drawing::Size(63, 23);
            this->label33->TabIndex = 98;
            this->label33->Text = L"Cột: y";
            // 
            // panel5
            // 
            this->panel5->Location = System::Drawing::Point(652, 998);
            this->panel5->Name = L"panel5";
            this->panel5->Size = System::Drawing::Size(2, 57);
            this->panel5->TabIndex = 97;
            // 
            // label32
            // 
            this->label32->AutoSize = true;
            this->label32->BackColor = System::Drawing::Color::LightGray;
            this->label32->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label32->Location = System::Drawing::Point(540, 1016);
            this->label32->Name = L"label32";
            this->label32->Size = System::Drawing::Size(76, 23);
            this->label32->TabIndex = 96;
            this->label32->Text = L"Dòng: x";
            // 
            // panel4
            // 
            this->panel4->Location = System::Drawing::Point(502, 998);
            this->panel4->Name = L"panel4";
            this->panel4->Size = System::Drawing::Size(2, 57);
            this->panel4->TabIndex = 95;
            // 
            // label31
            // 
            this->label31->AutoSize = true;
            this->label31->BackColor = System::Drawing::Color::LightGray;
            this->label31->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label31->Location = System::Drawing::Point(32, 1016);
            this->label31->Name = L"label31";
            this->label31->Size = System::Drawing::Size(84, 23);
            this->label31->TabIndex = 84;
            this->label31->Text = L"Sẵn sàng";
            // 
            // panel1
            // 
            this->panel1->Controls->Add(this->panel2);
            this->panel1->Location = System::Drawing::Point(152, 997);
            this->panel1->Name = L"panel1";
            this->panel1->Size = System::Drawing::Size(2, 57);
            this->panel1->TabIndex = 94;
            // 
            // panel2
            // 
            this->panel2->Controls->Add(this->panel3);
            this->panel2->Location = System::Drawing::Point(0, 0);
            this->panel2->Name = L"panel2";
            this->panel2->Size = System::Drawing::Size(2, 57);
            this->panel2->TabIndex = 33;
            // 
            // panel3
            // 
            this->panel3->Location = System::Drawing::Point(0, 0);
            this->panel3->Name = L"panel3";
            this->panel3->Size = System::Drawing::Size(2, 57);
            this->panel3->TabIndex = 33;
            // 
            // pictureBox2
            // 
            this->pictureBox2->BackColor = System::Drawing::Color::LightGray;
            this->pictureBox2->Location = System::Drawing::Point(17, 997);
            this->pictureBox2->Name = L"pictureBox2";
            this->pictureBox2->Size = System::Drawing::Size(1490, 58);
            this->pictureBox2->TabIndex = 93;
            this->pictureBox2->TabStop = false;
            // 
            // pictureBox1
            // 
            this->pictureBox1->BackColor = System::Drawing::Color::White;
            this->pictureBox1->Location = System::Drawing::Point(16, 942);
            this->pictureBox1->Name = L"pictureBox1";
            this->pictureBox1->Size = System::Drawing::Size(1490, 58);
            this->pictureBox1->TabIndex = 92;
            this->pictureBox1->TabStop = false;
            // 
            // textBox3
            // 
            this->textBox3->BackColor = System::Drawing::SystemColors::ActiveCaption;
            this->textBox3->Location = System::Drawing::Point(16, 874);
            this->textBox3->Multiline = true;
            this->textBox3->Name = L"textBox3";
            this->textBox3->Size = System::Drawing::Size(1491, 68);
            this->textBox3->TabIndex = 90;
            // 
            // label23
            // 
            this->label23->AutoSize = true;
            this->label23->BackColor = System::Drawing::SystemColors::ActiveCaption;
            this->label23->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label23->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
            this->label23->Location = System::Drawing::Point(1240, 107);
            this->label23->Name = L"label23";
            this->label23->Size = System::Drawing::Size(253, 32);
            this->label23->TabIndex = 82;
            this->label23->Text = L"Tìm kiếm / Thay thế";
            // 
            // label3
            // 
            this->label3->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label3->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
            this->label3->Location = System::Drawing::Point(23, 22);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(107, 26);
            this->label3->TabIndex = 4;
            this->label3->Text = L"Từ";
            this->label3->TextAlign = System::Drawing::ContentAlignment::TopCenter;
            // 
            // lbl_Words
            // 
            this->lbl_Words->AutoSize = true;
            this->lbl_Words->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->lbl_Words->Location = System::Drawing::Point(162, 22);
            this->lbl_Words->Name = L"lbl_Words";
            this->lbl_Words->Size = System::Drawing::Size(93, 26);
            this->lbl_Words->TabIndex = 5;
            this->lbl_Words->Text = L"abcxyz..";
            // 
            // label29
            // 
            this->label29->AutoSize = true;
            this->label29->BackColor = System::Drawing::SystemColors::ActiveCaption;
            this->label29->Font = (gcnew System::Drawing::Font(L"Times New Roman", 13, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label29->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
            this->label29->Location = System::Drawing::Point(30, 885);
            this->label29->Name = L"label29";
            this->label29->Size = System::Drawing::Size(244, 30);
            this->label29->TabIndex = 91;
            this->label29->Text = L"Kết quả / Thông báo";
            // 
            // label6
            // 
            this->label6->AutoSize = true;
            this->label6->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label6->Location = System::Drawing::Point(162, 73);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(93, 26);
            this->label6->TabIndex = 8;
            this->label6->Text = L"abcxyz..";
            // 
            // toolStrip1
            // 
            this->toolStrip1->ImageScalingSize = System::Drawing::Size(24, 24);
            this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(8) {
                this->toolStripButton1,
                    this->toolStripButton2, this->toolStripButton3, this->toolStripButton4, this->toolStripButton5, this->toolStripButton6, this->toolStripButton7,
                    this->toolStripButton8
            });
            this->toolStrip1->Location = System::Drawing::Point(0, 33);
            this->toolStrip1->Name = L"toolStrip1";
            this->toolStrip1->Size = System::Drawing::Size(1520, 34);
            this->toolStrip1->TabIndex = 76;
            this->toolStrip1->Text = L"toolStrip1";
            // 
            // toolStripButton1
            // 
            this->toolStripButton1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->toolStripButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->toolStripButton1->Name = L"toolStripButton1";
            this->toolStripButton1->Size = System::Drawing::Size(48, 29);
            this->toolStripButton1->Text = L"Mở";
            this->toolStripButton1->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
            // 
            // toolStripButton2
            // 
            this->toolStripButton2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->toolStripButton2->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->toolStripButton2->Name = L"toolStripButton2";
            this->toolStripButton2->Size = System::Drawing::Size(56, 29);
            this->toolStripButton2->Text = L"Lưu";
            this->toolStripButton2->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
            // 
            // toolStripButton3
            // 
            this->toolStripButton3->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->toolStripButton3->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->toolStripButton3->Name = L"toolStripButton3";
            this->toolStripButton3->Size = System::Drawing::Size(217, 29);
            this->toolStripButton3->Text = L"Hoàn Tác (CTRL+Z)";
            this->toolStripButton3->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
            // 
            // toolStripButton4
            // 
            this->toolStripButton4->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->toolStripButton4->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->toolStripButton4->Name = L"toolStripButton4";
            this->toolStripButton4->Size = System::Drawing::Size(207, 29);
            this->toolStripButton4->Text = L"Làm Lại (CTRL+Y)";
            this->toolStripButton4->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
            // 
            // toolStripButton5
            // 
            this->toolStripButton5->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->toolStripButton5->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->toolStripButton5->Name = L"toolStripButton5";
            this->toolStripButton5->Size = System::Drawing::Size(113, 29);
            this->toolStripButton5->Text = L"Tìm Kiếm";
            this->toolStripButton5->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
            // 
            // toolStripButton6
            // 
            this->toolStripButton6->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->toolStripButton6->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->toolStripButton6->Name = L"toolStripButton6";
            this->toolStripButton6->Size = System::Drawing::Size(107, 29);
            this->toolStripButton6->Text = L"Thay Thế";
            this->toolStripButton6->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
            // 
            // toolStripButton7
            // 
            this->toolStripButton7->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->toolStripButton7->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->toolStripButton7->Name = L"toolStripButton7";
            this->toolStripButton7->Size = System::Drawing::Size(111, 29);
            this->toolStripButton7->Text = L"Thống Kê";
            this->toolStripButton7->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
            // 
            // toolStripButton8
            // 
            this->toolStripButton8->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->toolStripButton8->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->toolStripButton8->Name = L"toolStripButton8";
            this->toolStripButton8->Size = System::Drawing::Size(162, 29);
            this->toolStripButton8->Text = L"Kiểm tra ngoặc";
            this->toolStripButton8->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
            // 
            // thêmToolStripMenuItem
            // 
            this->thêmToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->thêmToolStripMenuItem->Name = L"thêmToolStripMenuItem";
            this->thêmToolStripMenuItem->Size = System::Drawing::Size(65, 29);
            this->thêmToolStripMenuItem->Text = L"Tệp";
            // 
            // textBox2
            // 
            this->textBox2->BackColor = System::Drawing::Color::Beige;
            this->textBox2->Location = System::Drawing::Point(10, 282);
            this->textBox2->Multiline = true;
            this->textBox2->Name = L"textBox2";
            this->textBox2->Size = System::Drawing::Size(281, 68);
            this->textBox2->TabIndex = 77;
            // 
            // chỉnhSửaToolStripMenuItem
            // 
            this->chỉnhSửaToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->chỉnhSửaToolStripMenuItem->Name = L"chỉnhSửaToolStripMenuItem";
            this->chỉnhSửaToolStripMenuItem->Size = System::Drawing::Size(128, 29);
            this->chỉnhSửaToolStripMenuItem->Text = L"Chỉnh Sửa";
            // 
            // côngCụToolStripMenuItem
            // 
            this->côngCụToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->côngCụToolStripMenuItem->Name = L"côngCụToolStripMenuItem";
            this->côngCụToolStripMenuItem->Size = System::Drawing::Size(112, 29);
            this->côngCụToolStripMenuItem->Text = L"Công Cụ";
            // 
            // trợGiúpToolStripMenuItem
            // 
            this->trợGiúpToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->trợGiúpToolStripMenuItem->Name = L"trợGiúpToolStripMenuItem";
            this->trợGiúpToolStripMenuItem->Size = System::Drawing::Size(115, 29);
            this->trợGiúpToolStripMenuItem->Text = L"Trợ Giúp";
            // 
            // richTextBox1
            // 
            this->richTextBox1->Location = System::Drawing::Point(310, 96);
            this->richTextBox1->Name = L"richTextBox1";
            this->richTextBox1->Size = System::Drawing::Size(895, 765);
            this->richTextBox1->TabIndex = 74;
            this->richTextBox1->Text = L"";
            // 
            // menuStrip1
            // 
            this->menuStrip1->GripMargin = System::Windows::Forms::Padding(2, 2, 0, 2);
            this->menuStrip1->GripStyle = System::Windows::Forms::ToolStripGripStyle::Visible;
            this->menuStrip1->ImageScalingSize = System::Drawing::Size(24, 24);
            this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
                this->thêmToolStripMenuItem,
                    this->chỉnhSửaToolStripMenuItem, this->côngCụToolStripMenuItem, this->trợGiúpToolStripMenuItem
            });
            this->menuStrip1->Location = System::Drawing::Point(0, 0);
            this->menuStrip1->Name = L"menuStrip1";
            this->menuStrip1->Size = System::Drawing::Size(1520, 33);
            this->menuStrip1->TabIndex = 75;
            this->menuStrip1->Text = L"menuStrip1";
            // 
            // label5
            // 
            this->label5->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label5->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
            this->label5->Location = System::Drawing::Point(21, 70);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(138, 26);
            this->label5->TabIndex = 7;
            this->label5->Text = L"Dòng";
            this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            // 
            // textBox6
            // 
            this->textBox6->BackColor = System::Drawing::SystemColors::ActiveCaption;
            this->textBox6->Location = System::Drawing::Point(1226, 649);
            this->textBox6->Multiline = true;
            this->textBox6->Name = L"textBox6";
            this->textBox6->Size = System::Drawing::Size(281, 68);
            this->textBox6->TabIndex = 87;
            // 
            // groupBox5
            // 
            this->groupBox5->Controls->Add(this->label21);
            this->groupBox5->Controls->Add(this->label10);
            this->groupBox5->Controls->Add(this->numericUpDown1);
            this->groupBox5->Controls->Add(this->label18);
            this->groupBox5->Controls->Add(this->label19);
            this->groupBox5->Controls->Add(this->label20);
            this->groupBox5->Location = System::Drawing::Point(1231, 720);
            this->groupBox5->Name = L"groupBox5";
            this->groupBox5->Size = System::Drawing::Size(276, 141);
            this->groupBox5->TabIndex = 89;
            this->groupBox5->TabStop = false;
            // 
            // label21
            // 
            this->label21->AutoSize = true;
            this->label21->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label21->Location = System::Drawing::Point(124, 73);
            this->label21->Name = L"label21";
            this->label21->Size = System::Drawing::Size(93, 26);
            this->label21->TabIndex = 10;
            this->label21->Text = L"abcxyz..";
            // 
            // label10
            // 
            this->label10->AutoSize = true;
            this->label10->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label10->Location = System::Drawing::Point(10, 77);
            this->label10->Name = L"label10";
            this->label10->Size = System::Drawing::Size(95, 22);
            this->label10->TabIndex = 10;
            this->label10->Text = L"Trạng thái:";
            // 
            // numericUpDown1
            // 
            this->numericUpDown1->Location = System::Drawing::Point(130, 19);
            this->numericUpDown1->Name = L"numericUpDown1";
            this->numericUpDown1->Size = System::Drawing::Size(80, 26);
            this->numericUpDown1->TabIndex = 9;
            // 
            // label18
            // 
            this->label18->AutoSize = true;
            this->label18->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label18->Location = System::Drawing::Point(125, 73);
            this->label18->Name = L"label18";
            this->label18->Size = System::Drawing::Size(0, 26);
            this->label18->TabIndex = 8;
            // 
            // label19
            // 
            this->label19->AutoSize = true;
            this->label19->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label19->Location = System::Drawing::Point(125, 25);
            this->label19->Name = L"label19";
            this->label19->Size = System::Drawing::Size(0, 26);
            this->label19->TabIndex = 5;
            // 
            // label20
            // 
            this->label20->AutoSize = true;
            this->label20->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label20->Location = System::Drawing::Point(11, 20);
            this->label20->Name = L"label20";
            this->label20->Size = System::Drawing::Size(76, 22);
            this->label20->TabIndex = 7;
            this->label20->Text = L"K bước:";
            // 
            // label12
            // 
            this->label12->AutoSize = true;
            this->label12->BackColor = System::Drawing::SystemColors::ActiveCaption;
            this->label12->Font = (gcnew System::Drawing::Font(L"Times New Roman", 13, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label12->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
            this->label12->Location = System::Drawing::Point(1240, 660);
            this->label12->Name = L"label12";
            this->label12->Size = System::Drawing::Size(260, 30);
            this->label12->TabIndex = 88;
            this->label12->Text = L"Giới hạn Undo / Redo";
            // 
            // lbl_ngoac_vuong
            // 
            this->lbl_ngoac_vuong->AutoSize = true;
            this->lbl_ngoac_vuong->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->lbl_ngoac_vuong->Location = System::Drawing::Point(143, 200);
            this->lbl_ngoac_vuong->Name = L"lbl_ngoac_vuong";
            this->lbl_ngoac_vuong->Size = System::Drawing::Size(66, 26);
            this->lbl_ngoac_vuong->TabIndex = 14;
            this->lbl_ngoac_vuong->Text = L"Dòng";
            // 
            // lbl_ngoac_nhon
            // 
            this->lbl_ngoac_nhon->AutoSize = true;
            this->lbl_ngoac_nhon->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->lbl_ngoac_nhon->Location = System::Drawing::Point(143, 159);
            this->lbl_ngoac_nhon->Name = L"lbl_ngoac_nhon";
            this->lbl_ngoac_nhon->Size = System::Drawing::Size(66, 26);
            this->lbl_ngoac_nhon->TabIndex = 13;
            this->lbl_ngoac_nhon->Text = L"Dòng";
            // 
            // textBox4
            // 
            this->textBox4->BackColor = System::Drawing::SystemColors::ActiveCaption;
            this->textBox4->Location = System::Drawing::Point(1226, 96);
            this->textBox4->Multiline = true;
            this->textBox4->Name = L"textBox4";
            this->textBox4->Size = System::Drawing::Size(281, 68);
            this->textBox4->TabIndex = 81;
            // 
            // groupBox4
            // 
            this->groupBox4->Controls->Add(this->btn_timkiem);
            this->groupBox4->Controls->Add(this->checkBox1);
            this->groupBox4->Controls->Add(this->radioButton2);
            this->groupBox4->Controls->Add(this->radioButton1);
            this->groupBox4->Controls->Add(this->txt_tukhoa);
            this->groupBox4->Controls->Add(this->label24);
            this->groupBox4->Controls->Add(this->label25);
            this->groupBox4->Controls->Add(this->label26);
            this->groupBox4->Controls->Add(this->label27);
            this->groupBox4->Location = System::Drawing::Point(1231, 167);
            this->groupBox4->Name = L"groupBox4";
            this->groupBox4->Size = System::Drawing::Size(276, 324);
            this->groupBox4->TabIndex = 85;
            this->groupBox4->TabStop = false;
            // 
            // btn_timkiem
            // 
            this->btn_timkiem->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btn_timkiem->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->btn_timkiem->Location = System::Drawing::Point(22, 263);
            this->btn_timkiem->Name = L"btn_timkiem";
            this->btn_timkiem->Size = System::Drawing::Size(226, 46);
            this->btn_timkiem->TabIndex = 13;
            this->btn_timkiem->Text = L"Tìm kiếm";
            this->btn_timkiem->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
            this->btn_timkiem->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
            this->btn_timkiem->UseVisualStyleBackColor = true;
            // 
            // checkBox1
            // 
            this->checkBox1->AutoSize = true;
            this->checkBox1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->checkBox1->Location = System::Drawing::Point(22, 231);
            this->checkBox1->Name = L"checkBox1";
            this->checkBox1->Size = System::Drawing::Size(120, 26);
            this->checkBox1->TabIndex = 12;
            this->checkBox1->Text = L"Tìm cả tệp";
            this->checkBox1->UseVisualStyleBackColor = true;
            // 
            // radioButton2
            // 
            this->radioButton2->AutoSize = true;
            this->radioButton2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->radioButton2->Location = System::Drawing::Point(22, 199);
            this->radioButton2->Name = L"radioButton2";
            this->radioButton2->Size = System::Drawing::Size(201, 26);
            this->radioButton2->TabIndex = 11;
            this->radioButton2->TabStop = true;
            this->radioButton2->Text = L"Phân biệt hoa/thường";
            this->radioButton2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            this->radioButton2->UseVisualStyleBackColor = true;
            // 
            // radioButton1
            // 
            this->radioButton1->AutoSize = true;
            this->radioButton1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->radioButton1->Location = System::Drawing::Point(22, 167);
            this->radioButton1->Name = L"radioButton1";
            this->radioButton1->Size = System::Drawing::Size(96, 26);
            this->radioButton1->TabIndex = 10;
            this->radioButton1->TabStop = true;
            this->radioButton1->Text = L"Thường";
            this->radioButton1->UseVisualStyleBackColor = true;
            // 
            // txt_tukhoa
            // 
            this->txt_tukhoa->Location = System::Drawing::Point(15, 97);
            this->txt_tukhoa->Multiline = true;
            this->txt_tukhoa->Name = L"txt_tukhoa";
            this->txt_tukhoa->Size = System::Drawing::Size(247, 36);
            this->txt_tukhoa->TabIndex = 9;
            // 
            // label24
            // 
            this->label24->AutoSize = true;
            this->label24->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label24->Location = System::Drawing::Point(125, 73);
            this->label24->Name = L"label24";
            this->label24->Size = System::Drawing::Size(0, 26);
            this->label24->TabIndex = 8;
            // 
            // label25
            // 
            this->label25->AutoSize = true;
            this->label25->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label25->Location = System::Drawing::Point(10, 12);
            this->label25->Name = L"label25";
            this->label25->Size = System::Drawing::Size(109, 26);
            this->label25->TabIndex = 4;
            this->label25->Text = L"Tìm kiếm";
            // 
            // label26
            // 
            this->label26->AutoSize = true;
            this->label26->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label26->Location = System::Drawing::Point(125, 25);
            this->label26->Name = L"label26";
            this->label26->Size = System::Drawing::Size(0, 26);
            this->label26->TabIndex = 5;
            // 
            // label27
            // 
            this->label27->AutoSize = true;
            this->label27->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label27->Location = System::Drawing::Point(11, 63);
            this->label27->Name = L"label27";
            this->label27->Size = System::Drawing::Size(86, 22);
            this->label27->TabIndex = 7;
            this->label27->Text = L"Từ Khóa:";
            // 
            // label13
            // 
            this->label13->AutoSize = true;
            this->label13->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label13->Location = System::Drawing::Point(99, 108);
            this->label13->Name = L"label13";
            this->label13->Size = System::Drawing::Size(20, 26);
            this->label13->TabIndex = 15;
            this->label13->Text = L":";
            // 
            // panel7
            // 
            this->panel7->Location = System::Drawing::Point(1316, 998);
            this->panel7->Name = L"panel7";
            this->panel7->Size = System::Drawing::Size(2, 57);
            this->panel7->TabIndex = 101;
            // 
            // groupBox3
            // 
            this->groupBox3->Controls->Add(this->textBox5);
            this->groupBox3->Controls->Add(this->button1);
            this->groupBox3->Controls->Add(this->label11);
            this->groupBox3->Controls->Add(this->label16);
            this->groupBox3->Controls->Add(this->label17);
            this->groupBox3->Location = System::Drawing::Point(1231, 497);
            this->groupBox3->Name = L"groupBox3";
            this->groupBox3->Size = System::Drawing::Size(276, 141);
            this->groupBox3->TabIndex = 86;
            this->groupBox3->TabStop = false;
            // 
            // textBox5
            // 
            this->textBox5->Location = System::Drawing::Point(100, 15);
            this->textBox5->Multiline = true;
            this->textBox5->Name = L"textBox5";
            this->textBox5->Size = System::Drawing::Size(162, 36);
            this->textBox5->TabIndex = 14;
            // 
            // button1
            // 
            this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->button1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->button1->Location = System::Drawing::Point(22, 73);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(226, 46);
            this->button1->TabIndex = 13;
            this->button1->Text = L"Thay Thế";
            this->button1->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
            this->button1->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
            this->button1->UseVisualStyleBackColor = true;
            // 
            // label11
            // 
            this->label11->AutoSize = true;
            this->label11->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label11->Location = System::Drawing::Point(125, 73);
            this->label11->Name = L"label11";
            this->label11->Size = System::Drawing::Size(0, 26);
            this->label11->TabIndex = 8;
            // 
            // label16
            // 
            this->label16->AutoSize = true;
            this->label16->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label16->Location = System::Drawing::Point(125, 25);
            this->label16->Name = L"label16";
            this->label16->Size = System::Drawing::Size(0, 26);
            this->label16->TabIndex = 5;
            // 
            // label17
            // 
            this->label17->AutoSize = true;
            this->label17->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label17->Location = System::Drawing::Point(11, 20);
            this->label17->Name = L"label17";
            this->label17->Size = System::Drawing::Size(83, 22);
            this->label17->TabIndex = 7;
            this->label17->Text = L"Thay thế:";
            // 
            // label15
            // 
            this->label15->AutoSize = true;
            this->label15->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label15->Location = System::Drawing::Point(99, 200);
            this->label15->Name = L"label15";
            this->label15->Size = System::Drawing::Size(20, 26);
            this->label15->TabIndex = 17;
            this->label15->Text = L":";
            // 
            // label14
            // 
            this->label14->AutoSize = true;
            this->label14->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label14->Location = System::Drawing::Point(99, 159);
            this->label14->Name = L"label14";
            this->label14->Size = System::Drawing::Size(20, 26);
            this->label14->TabIndex = 16;
            this->label14->Text = L":";
            // 
            // label30
            // 
            this->label30->BackColor = System::Drawing::Color::White;
            this->label30->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label30->ForeColor = System::Drawing::Color::Black;
            this->label30->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
            this->label30->Location = System::Drawing::Point(38, 959);
            this->label30->Name = L"label30";
            this->label30->Size = System::Drawing::Size(252, 26);
            this->label30->TabIndex = 83;
            this->label30->Text = L"kiểm tra cú pháp...";
            this->label30->TextAlign = System::Drawing::ContentAlignment::TopCenter;
            // 
            // lbl_ngoac_tron
            // 
            this->lbl_ngoac_tron->AutoSize = true;
            this->lbl_ngoac_tron->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->lbl_ngoac_tron->Location = System::Drawing::Point(143, 117);
            this->lbl_ngoac_tron->Name = L"lbl_ngoac_tron";
            this->lbl_ngoac_tron->Size = System::Drawing::Size(66, 26);
            this->lbl_ngoac_tron->TabIndex = 12;
            this->lbl_ngoac_tron->Text = L"Dòng";
            // 
            // label9
            // 
            this->label9->AutoSize = true;
            this->label9->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label9->Location = System::Drawing::Point(23, 200);
            this->label9->Name = L"label9";
            this->label9->Size = System::Drawing::Size(28, 26);
            this->label9->TabIndex = 11;
            this->label9->Text = L"[]";
            // 
            // label8
            // 
            this->label8->AutoSize = true;
            this->label8->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label8->Location = System::Drawing::Point(23, 159);
            this->label8->Name = L"label8";
            this->label8->Size = System::Drawing::Size(30, 26);
            this->label8->TabIndex = 10;
            this->label8->Text = L"{}";
            // 
            // label7
            // 
            this->label7->AutoSize = true;
            this->label7->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label7->Location = System::Drawing::Point(23, 108);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(28, 26);
            this->label7->TabIndex = 9;
            this->label7->Text = L"()";
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label2->Location = System::Drawing::Point(323, 355);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(0, 60);
            this->label2->TabIndex = 72;
            // 
            // textBox1
            // 
            this->textBox1->BackColor = System::Drawing::SystemColors::ActiveCaption;
            this->textBox1->Location = System::Drawing::Point(10, 96);
            this->textBox1->Multiline = true;
            this->textBox1->Name = L"textBox1";
            this->textBox1->Size = System::Drawing::Size(281, 68);
            this->textBox1->TabIndex = 71;
            // 
            // groupBox1
            // 
            this->groupBox1->Controls->Add(this->label22);
            this->groupBox1->Controls->Add(this->label15);
            this->groupBox1->Controls->Add(this->label14);
            this->groupBox1->Controls->Add(this->label13);
            this->groupBox1->Controls->Add(this->lbl_ngoac_vuong);
            this->groupBox1->Controls->Add(this->lbl_ngoac_nhon);
            this->groupBox1->Controls->Add(this->lbl_ngoac_tron);
            this->groupBox1->Controls->Add(this->label9);
            this->groupBox1->Controls->Add(this->label8);
            this->groupBox1->Controls->Add(this->label7);
            this->groupBox1->Location = System::Drawing::Point(14, 351);
            this->groupBox1->Name = L"groupBox1";
            this->groupBox1->Size = System::Drawing::Size(276, 510);
            this->groupBox1->TabIndex = 79;
            this->groupBox1->TabStop = false;
            // 
            // label22
            // 
            this->label22->BackColor = System::Drawing::SystemColors::Control;
            this->label22->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label22->ForeColor = System::Drawing::Color::Green;
            this->label22->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
            this->label22->Location = System::Drawing::Point(18, 44);
            this->label22->Name = L"label22";
            this->label22->Size = System::Drawing::Size(258, 26);
            this->label22->TabIndex = 18;
            this->label22->Text = L"Ngoặc cân bằng!";
            this->label22->TextAlign = System::Drawing::ContentAlignment::TopCenter;
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->BackColor = System::Drawing::Color::Beige;
            this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label1->ForeColor = System::Drawing::Color::Black;
            this->label1->Location = System::Drawing::Point(37, 293);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(208, 32);
            this->label1->TabIndex = 78;
            this->label1->Text = L"Kiểm Tra Ngoặc";
            // 
            // label4
            // 
            this->label4->AutoSize = true;
            this->label4->BackColor = System::Drawing::SystemColors::ActiveCaption;
            this->label4->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label4->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
            this->label4->Location = System::Drawing::Point(37, 107);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(126, 32);
            this->label4->TabIndex = 73;
            this->label4->Text = L"Thống kê";
            // 
            // groupBox2
            // 
            this->groupBox2->Controls->Add(this->label28);
            this->groupBox2->Controls->Add(this->label6);
            this->groupBox2->Controls->Add(this->label3);
            this->groupBox2->Controls->Add(this->lbl_Words);
            this->groupBox2->Controls->Add(this->label5);
            this->groupBox2->Location = System::Drawing::Point(15, 167);
            this->groupBox2->Name = L"groupBox2";
            this->groupBox2->Size = System::Drawing::Size(276, 123);
            this->groupBox2->TabIndex = 80;
            this->groupBox2->TabStop = false;
            // 
            // label28
            // 
            this->label28->AutoSize = true;
            this->label28->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label28->Location = System::Drawing::Point(57, 25);
            this->label28->Name = L"label28";
            this->label28->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
            this->label28->Size = System::Drawing::Size(0, 26);
            this->label28->TabIndex = 9;
            // 
            // CodeNote_N3
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1520, 1063);
            this->Controls->Add(this->label35);
            this->Controls->Add(this->label34);
            this->Controls->Add(this->panel6);
            this->Controls->Add(this->label33);
            this->Controls->Add(this->panel5);
            this->Controls->Add(this->label32);
            this->Controls->Add(this->panel4);
            this->Controls->Add(this->label31);
            this->Controls->Add(this->panel1);
            this->Controls->Add(this->pictureBox2);
            this->Controls->Add(this->pictureBox1);
            this->Controls->Add(this->textBox3);
            this->Controls->Add(this->label23);
            this->Controls->Add(this->label29);
            this->Controls->Add(this->toolStrip1);
            this->Controls->Add(this->textBox2);
            this->Controls->Add(this->richTextBox1);
            this->Controls->Add(this->menuStrip1);
            this->Controls->Add(this->textBox6);
            this->Controls->Add(this->groupBox5);
            this->Controls->Add(this->label12);
            this->Controls->Add(this->textBox4);
            this->Controls->Add(this->groupBox4);
            this->Controls->Add(this->panel7);
            this->Controls->Add(this->groupBox3);
            this->Controls->Add(this->label30);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->textBox1);
            this->Controls->Add(this->groupBox1);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->label4);
            this->Controls->Add(this->groupBox2);
            this->Name = L"CodeNote_N3";
            this->Text = L"CodeNote_N3";
            this->panel1->ResumeLayout(false);
            this->panel2->ResumeLayout(false);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
            this->toolStrip1->ResumeLayout(false);
            this->toolStrip1->PerformLayout();
            this->menuStrip1->ResumeLayout(false);
            this->menuStrip1->PerformLayout();
            this->groupBox5->ResumeLayout(false);
            this->groupBox5->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
            this->groupBox4->ResumeLayout(false);
            this->groupBox4->PerformLayout();
            this->groupBox3->ResumeLayout(false);
            this->groupBox3->PerformLayout();
            this->groupBox1->ResumeLayout(false);
            this->groupBox1->PerformLayout();
            this->groupBox2->ResumeLayout(false);
            this->groupBox2->PerformLayout();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
	};
}
