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
#pragma region code_thua_thiet_ke_form_thien


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
    private: System::Windows::Forms::Label^ lb_limit_undo;
    protected:
    private: System::Windows::Forms::Label^ lb_che_do;

    protected:

    private: System::Windows::Forms::Panel^ panel6;
    private: System::Windows::Forms::Label^ lb_cot_n;

    private: System::Windows::Forms::Panel^ panel5;
    private: System::Windows::Forms::Label^ lb_dong_n;

    private: System::Windows::Forms::Panel^ panel4;
    private: System::Windows::Forms::Label^ lb_kiem_tra;

    private: System::Windows::Forms::Panel^ panel1;
    private: System::Windows::Forms::Panel^ panel2;
    private: System::Windows::Forms::Panel^ panel3;
    private: System::Windows::Forms::PictureBox^ pictureBox2;
    private: System::Windows::Forms::PictureBox^ pictureBox1;
    private: System::Windows::Forms::TextBox^ textBox3;
    private: System::Windows::Forms::Label^ label23;
    private: System::Windows::Forms::Label^ label3;
    private: System::Windows::Forms::Label^ lb_Words;

    private: System::Windows::Forms::Label^ label29;
    private: System::Windows::Forms::Label^ lb_dong;

    private: System::Windows::Forms::ToolStrip^ toolStrip1;
    private: System::Windows::Forms::ToolStripButton^ tsb_open;
    private: System::Windows::Forms::ToolStripButton^ tsb_luu_save;


    private: System::Windows::Forms::ToolStripButton^ btn_undo;
    private: System::Windows::Forms::ToolStripButton^ btn_redo;
    private: System::Windows::Forms::ToolStripButton^ tsb_find;
    private: System::Windows::Forms::ToolStripButton^ tsb_thaythe;
    private: System::Windows::Forms::ToolStripButton^ tsb_thongke;
    private: System::Windows::Forms::ToolStripButton^ tsb_check;






    private: System::Windows::Forms::ToolStripMenuItem^ thêmToolStripMenuItem;
    private: System::Windows::Forms::TextBox^ textBox2;
    private: System::Windows::Forms::ToolStripMenuItem^ chỉnhSửaToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ côngCụToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ trợGiúpToolStripMenuItem;
    private: System::Windows::Forms::RichTextBox^ richTextBox_code;

    private: System::Windows::Forms::MenuStrip^ menuStrip1;
    private: System::Windows::Forms::Label^ label5;
    private: System::Windows::Forms::TextBox^ textBox6;
    private: System::Windows::Forms::GroupBox^ groupBox5;
    private: System::Windows::Forms::Label^ lb_trangthai;

    private: System::Windows::Forms::Label^ label10;
    private: System::Windows::Forms::NumericUpDown^ numericUpDown_K_step;

    private: System::Windows::Forms::Label^ label18;
    private: System::Windows::Forms::Label^ label19;
    private: System::Windows::Forms::Label^ label20;
    private: System::Windows::Forms::Label^ label12;
    private: System::Windows::Forms::Label^ lb_ngoac_vuong;
    private: System::Windows::Forms::Label^ lb_ngoac_nhon;


    private: System::Windows::Forms::TextBox^ textBox4;
    private: System::Windows::Forms::GroupBox^ groupBox4;
    private: System::Windows::Forms::Button^ btn_timkiem;
    private: System::Windows::Forms::CheckBox^ checkbox_findall;
    private: System::Windows::Forms::RadioButton^ rb_hoa_thuong;
    private: System::Windows::Forms::RadioButton^ rb_tu_thuong;



    private: System::Windows::Forms::TextBox^ txt_tukhoa;
    private: System::Windows::Forms::Label^ label24;
    private: System::Windows::Forms::Label^ label25;
    private: System::Windows::Forms::Label^ label26;
    private: System::Windows::Forms::Label^ label27;
    private: System::Windows::Forms::Label^ label13;
    private: System::Windows::Forms::Panel^ panel7;
    private: System::Windows::Forms::GroupBox^ groupBox3;
    private: System::Windows::Forms::TextBox^ txt_thaythe;
    private: System::Windows::Forms::Button^ btn_thaythe;


    private: System::Windows::Forms::Label^ label11;
    private: System::Windows::Forms::Label^ label16;
    private: System::Windows::Forms::Label^ label17;
    private: System::Windows::Forms::Label^ label15;
    private: System::Windows::Forms::Label^ label14;
    private: System::Windows::Forms::Label^ label30;
private: System::Windows::Forms::Label^ lb_ngoac_tron;

    private: System::Windows::Forms::Label^ label9;
    private: System::Windows::Forms::Label^ label8;
    private: System::Windows::Forms::Label^ label7;
    private: System::Windows::Forms::Label^ label2;
    private: System::Windows::Forms::TextBox^ textBox1;
    private: System::Windows::Forms::GroupBox^ groupBox1;
private: System::Windows::Forms::Label^ lb_check_ngoac;

    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::Label^ label4;
    private: System::Windows::Forms::GroupBox^ groupBox2;
    private: System::Windows::Forms::Label^ label28;
private: System::Windows::Forms::Label^ label36;
private: System::Windows::Forms::Label^ label37;
private: System::Windows::Forms::Label^ label38;
private: System::Windows::Forms::Label^ lb_check;

private: System::Windows::Forms::Label^ label40;
#pragma endregion

#pragma region Windows Form Designer generated code
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;


		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(CodeNote_N3::typeid));
            this->lb_limit_undo = (gcnew System::Windows::Forms::Label());
            this->lb_che_do = (gcnew System::Windows::Forms::Label());
            this->panel6 = (gcnew System::Windows::Forms::Panel());
            this->lb_cot_n = (gcnew System::Windows::Forms::Label());
            this->panel5 = (gcnew System::Windows::Forms::Panel());
            this->lb_dong_n = (gcnew System::Windows::Forms::Label());
            this->panel4 = (gcnew System::Windows::Forms::Panel());
            this->lb_kiem_tra = (gcnew System::Windows::Forms::Label());
            this->panel1 = (gcnew System::Windows::Forms::Panel());
            this->panel2 = (gcnew System::Windows::Forms::Panel());
            this->panel3 = (gcnew System::Windows::Forms::Panel());
            this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
            this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
            this->textBox3 = (gcnew System::Windows::Forms::TextBox());
            this->label23 = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->lb_Words = (gcnew System::Windows::Forms::Label());
            this->label29 = (gcnew System::Windows::Forms::Label());
            this->lb_dong = (gcnew System::Windows::Forms::Label());
            this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
            this->tsb_open = (gcnew System::Windows::Forms::ToolStripButton());
            this->tsb_luu_save = (gcnew System::Windows::Forms::ToolStripButton());
            this->btn_undo = (gcnew System::Windows::Forms::ToolStripButton());
            this->btn_redo = (gcnew System::Windows::Forms::ToolStripButton());
            this->tsb_find = (gcnew System::Windows::Forms::ToolStripButton());
            this->tsb_thaythe = (gcnew System::Windows::Forms::ToolStripButton());
            this->tsb_thongke = (gcnew System::Windows::Forms::ToolStripButton());
            this->tsb_check = (gcnew System::Windows::Forms::ToolStripButton());
            this->thêmToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->textBox2 = (gcnew System::Windows::Forms::TextBox());
            this->chỉnhSửaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->côngCụToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->trợGiúpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->richTextBox_code = (gcnew System::Windows::Forms::RichTextBox());
            this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->textBox6 = (gcnew System::Windows::Forms::TextBox());
            this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
            this->lb_trangthai = (gcnew System::Windows::Forms::Label());
            this->label10 = (gcnew System::Windows::Forms::Label());
            this->numericUpDown_K_step = (gcnew System::Windows::Forms::NumericUpDown());
            this->label18 = (gcnew System::Windows::Forms::Label());
            this->label19 = (gcnew System::Windows::Forms::Label());
            this->label20 = (gcnew System::Windows::Forms::Label());
            this->label12 = (gcnew System::Windows::Forms::Label());
            this->lb_ngoac_vuong = (gcnew System::Windows::Forms::Label());
            this->lb_ngoac_nhon = (gcnew System::Windows::Forms::Label());
            this->textBox4 = (gcnew System::Windows::Forms::TextBox());
            this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
            this->btn_timkiem = (gcnew System::Windows::Forms::Button());
            this->checkbox_findall = (gcnew System::Windows::Forms::CheckBox());
            this->rb_hoa_thuong = (gcnew System::Windows::Forms::RadioButton());
            this->rb_tu_thuong = (gcnew System::Windows::Forms::RadioButton());
            this->txt_tukhoa = (gcnew System::Windows::Forms::TextBox());
            this->label24 = (gcnew System::Windows::Forms::Label());
            this->label25 = (gcnew System::Windows::Forms::Label());
            this->label26 = (gcnew System::Windows::Forms::Label());
            this->label27 = (gcnew System::Windows::Forms::Label());
            this->label13 = (gcnew System::Windows::Forms::Label());
            this->panel7 = (gcnew System::Windows::Forms::Panel());
            this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
            this->txt_thaythe = (gcnew System::Windows::Forms::TextBox());
            this->btn_thaythe = (gcnew System::Windows::Forms::Button());
            this->label11 = (gcnew System::Windows::Forms::Label());
            this->label16 = (gcnew System::Windows::Forms::Label());
            this->label17 = (gcnew System::Windows::Forms::Label());
            this->label15 = (gcnew System::Windows::Forms::Label());
            this->label14 = (gcnew System::Windows::Forms::Label());
            this->label30 = (gcnew System::Windows::Forms::Label());
            this->lb_ngoac_tron = (gcnew System::Windows::Forms::Label());
            this->label9 = (gcnew System::Windows::Forms::Label());
            this->label8 = (gcnew System::Windows::Forms::Label());
            this->label7 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->textBox1 = (gcnew System::Windows::Forms::TextBox());
            this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
            this->lb_check_ngoac = (gcnew System::Windows::Forms::Label());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
            this->label28 = (gcnew System::Windows::Forms::Label());
            this->label36 = (gcnew System::Windows::Forms::Label());
            this->label37 = (gcnew System::Windows::Forms::Label());
            this->label38 = (gcnew System::Windows::Forms::Label());
            this->lb_check = (gcnew System::Windows::Forms::Label());
            this->label40 = (gcnew System::Windows::Forms::Label());
            this->panel1->SuspendLayout();
            this->panel2->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
            this->toolStrip1->SuspendLayout();
            this->menuStrip1->SuspendLayout();
            this->groupBox5->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_K_step))->BeginInit();
            this->groupBox4->SuspendLayout();
            this->groupBox3->SuspendLayout();
            this->groupBox1->SuspendLayout();
            this->groupBox2->SuspendLayout();
            this->SuspendLayout();
            // 
            // lb_limit_undo
            // 
            this->lb_limit_undo->AutoSize = true;
            this->lb_limit_undo->BackColor = System::Drawing::Color::LightGray;
            this->lb_limit_undo->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->lb_limit_undo->Location = System::Drawing::Point(1324, 1016);
            this->lb_limit_undo->Name = L"lb_limit_undo";
            this->lb_limit_undo->Size = System::Drawing::Size(169, 23);
            this->lb_limit_undo->TabIndex = 102;
            this->lb_limit_undo->Text = L"Limit undo: x bước";
            this->lb_limit_undo->TextAlign = System::Drawing::ContentAlignment::TopRight;
            this->lb_limit_undo->Click += gcnew System::EventHandler(this, &CodeNote_N3::lb_limit_undo_Click);
            // 
            // lb_che_do
            // 
            this->lb_che_do->AutoSize = true;
            this->lb_che_do->BackColor = System::Drawing::Color::LightGray;
            this->lb_che_do->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->lb_che_do->Location = System::Drawing::Point(1158, 1016);
            this->lb_che_do->Name = L"lb_che_do";
            this->lb_che_do->Size = System::Drawing::Size(117, 23);
            this->lb_che_do->TabIndex = 100;
            this->lb_che_do->Text = L"Chế độ: C++";
            this->lb_che_do->TextAlign = System::Drawing::ContentAlignment::TopRight;
            this->lb_che_do->Click += gcnew System::EventHandler(this, &CodeNote_N3::lb_che_do_Click);
            // 
            // panel6
            // 
            this->panel6->Location = System::Drawing::Point(1150, 998);
            this->panel6->Name = L"panel6";
            this->panel6->Size = System::Drawing::Size(2, 57);
            this->panel6->TabIndex = 99;
            // 
            // lb_cot_n
            // 
            this->lb_cot_n->AutoSize = true;
            this->lb_cot_n->BackColor = System::Drawing::Color::LightGray;
            this->lb_cot_n->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->lb_cot_n->Location = System::Drawing::Point(679, 1016);
            this->lb_cot_n->Name = L"lb_cot_n";
            this->lb_cot_n->Size = System::Drawing::Size(63, 23);
            this->lb_cot_n->TabIndex = 98;
            this->lb_cot_n->Text = L"Cột: y";
            this->lb_cot_n->Click += gcnew System::EventHandler(this, &CodeNote_N3::lb_cot_n_Click);
            // 
            // panel5
            // 
            this->panel5->Location = System::Drawing::Point(652, 998);
            this->panel5->Name = L"panel5";
            this->panel5->Size = System::Drawing::Size(2, 57);
            this->panel5->TabIndex = 97;
            // 
            // lb_dong_n
            // 
            this->lb_dong_n->AutoSize = true;
            this->lb_dong_n->BackColor = System::Drawing::Color::LightGray;
            this->lb_dong_n->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->lb_dong_n->Location = System::Drawing::Point(540, 1016);
            this->lb_dong_n->Name = L"lb_dong_n";
            this->lb_dong_n->Size = System::Drawing::Size(76, 23);
            this->lb_dong_n->TabIndex = 96;
            this->lb_dong_n->Text = L"Dòng: x";
            this->lb_dong_n->Click += gcnew System::EventHandler(this, &CodeNote_N3::lb_dong_n_Click);
            // 
            // panel4
            // 
            this->panel4->Location = System::Drawing::Point(502, 998);
            this->panel4->Name = L"panel4";
            this->panel4->Size = System::Drawing::Size(2, 57);
            this->panel4->TabIndex = 95;
            // 
            // lb_kiem_tra
            // 
            this->lb_kiem_tra->AutoSize = true;
            this->lb_kiem_tra->BackColor = System::Drawing::Color::LightGray;
            this->lb_kiem_tra->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->lb_kiem_tra->Location = System::Drawing::Point(32, 1016);
            this->lb_kiem_tra->Name = L"lb_kiem_tra";
            this->lb_kiem_tra->Size = System::Drawing::Size(84, 23);
            this->lb_kiem_tra->TabIndex = 84;
            this->lb_kiem_tra->Text = L"Sẵn sàng";
            this->lb_kiem_tra->Click += gcnew System::EventHandler(this, &CodeNote_N3::lb_kiem_tra_Click);
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
            this->label3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"label3.Image")));
            this->label3->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
            this->label3->Location = System::Drawing::Point(23, 22);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(107, 26);
            this->label3->TabIndex = 4;
            this->label3->Text = L"Từ";
            this->label3->TextAlign = System::Drawing::ContentAlignment::TopCenter;
            // 
            // lb_Words
            // 
            this->lb_Words->AutoSize = true;
            this->lb_Words->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->lb_Words->Location = System::Drawing::Point(162, 22);
            this->lb_Words->Name = L"lb_Words";
            this->lb_Words->Size = System::Drawing::Size(93, 26);
            this->lb_Words->TabIndex = 5;
            this->lb_Words->Text = L"abcxyz..";
            this->lb_Words->Click += gcnew System::EventHandler(this, &CodeNote_N3::lb_Words_Click);
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
            // lb_dong
            // 
            this->lb_dong->AutoSize = true;
            this->lb_dong->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->lb_dong->Location = System::Drawing::Point(162, 73);
            this->lb_dong->Name = L"lb_dong";
            this->lb_dong->Size = System::Drawing::Size(93, 26);
            this->lb_dong->TabIndex = 8;
            this->lb_dong->Text = L"abcxyz..";
            this->lb_dong->Click += gcnew System::EventHandler(this, &CodeNote_N3::lb_dong_Click);
            // 
            // toolStrip1
            // 
            this->toolStrip1->ImageScalingSize = System::Drawing::Size(24, 24);
            this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(8) {
                this->tsb_open, this->tsb_luu_save,
                    this->btn_undo, this->btn_redo, this->tsb_find, this->tsb_thaythe, this->tsb_thongke, this->tsb_check
            });
            this->toolStrip1->Location = System::Drawing::Point(0, 33);
            this->toolStrip1->Name = L"toolStrip1";
            this->toolStrip1->Size = System::Drawing::Size(1520, 58);
            this->toolStrip1->TabIndex = 76;
            this->toolStrip1->Text = L"toolStrip1";
            // 
            // tsb_open
            // 
            this->tsb_open->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->tsb_open->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsb_open.Image")));
            this->tsb_open->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->tsb_open->Name = L"tsb_open";
            this->tsb_open->Size = System::Drawing::Size(48, 53);
            this->tsb_open->Text = L"Mở";
            this->tsb_open->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
            this->tsb_open->Click += gcnew System::EventHandler(this, &CodeNote_N3::tsb_open_Click);
            // 
            // tsb_luu_save
            // 
            this->tsb_luu_save->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->tsb_luu_save->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsb_luu_save.Image")));
            this->tsb_luu_save->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->tsb_luu_save->Name = L"tsb_luu_save";
            this->tsb_luu_save->Size = System::Drawing::Size(56, 53);
            this->tsb_luu_save->Text = L"Lưu";
            this->tsb_luu_save->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
            this->tsb_luu_save->Click += gcnew System::EventHandler(this, &CodeNote_N3::tsb_luu_save_Click);
            // 
            // btn_undo
            // 
            this->btn_undo->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->btn_undo->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_undo.Image")));
            this->btn_undo->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->btn_undo->Name = L"btn_undo";
            this->btn_undo->Size = System::Drawing::Size(217, 53);
            this->btn_undo->Text = L"Hoàn Tác (CTRL+Z)";
            this->btn_undo->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
            this->btn_undo->Click += gcnew System::EventHandler(this, &CodeNote_N3::btn_undo_Click);
            // 
            // btn_redo
            // 
            this->btn_redo->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->btn_redo->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_redo.Image")));
            this->btn_redo->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->btn_redo->Name = L"btn_redo";
            this->btn_redo->Size = System::Drawing::Size(207, 53);
            this->btn_redo->Text = L"Làm Lại (CTRL+Y)";
            this->btn_redo->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
            this->btn_redo->Click += gcnew System::EventHandler(this, &CodeNote_N3::btn_redo_Click);
            // 
            // tsb_find
            // 
            this->tsb_find->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->tsb_find->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsb_find.Image")));
            this->tsb_find->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->tsb_find->Name = L"tsb_find";
            this->tsb_find->Size = System::Drawing::Size(113, 53);
            this->tsb_find->Text = L"Tìm Kiếm";
            this->tsb_find->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
            this->tsb_find->Click += gcnew System::EventHandler(this, &CodeNote_N3::tsb_find_Click);
            // 
            // tsb_thaythe
            // 
            this->tsb_thaythe->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->tsb_thaythe->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsb_thaythe.Image")));
            this->tsb_thaythe->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->tsb_thaythe->Name = L"tsb_thaythe";
            this->tsb_thaythe->Size = System::Drawing::Size(107, 53);
            this->tsb_thaythe->Text = L"Thay Thế";
            this->tsb_thaythe->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
            this->tsb_thaythe->Click += gcnew System::EventHandler(this, &CodeNote_N3::tsb_thaythe_Click);
            // 
            // tsb_thongke
            // 
            this->tsb_thongke->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->tsb_thongke->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsb_thongke.Image")));
            this->tsb_thongke->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->tsb_thongke->Name = L"tsb_thongke";
            this->tsb_thongke->Size = System::Drawing::Size(111, 53);
            this->tsb_thongke->Text = L"Thống Kê";
            this->tsb_thongke->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
            this->tsb_thongke->Click += gcnew System::EventHandler(this, &CodeNote_N3::tsb_thongke_Click);
            // 
            // tsb_check
            // 
            this->tsb_check->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->tsb_check->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsb_check.Image")));
            this->tsb_check->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->tsb_check->Name = L"tsb_check";
            this->tsb_check->Size = System::Drawing::Size(162, 53);
            this->tsb_check->Text = L"Kiểm tra ngoặc";
            this->tsb_check->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
            this->tsb_check->Click += gcnew System::EventHandler(this, &CodeNote_N3::tsb_check_Click);
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
            this->textBox2->BackColor = System::Drawing::SystemColors::ActiveCaption;
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
            // richTextBox_code
            // 
            this->richTextBox_code->Location = System::Drawing::Point(310, 96);
            this->richTextBox_code->Name = L"richTextBox_code";
            this->richTextBox_code->Size = System::Drawing::Size(895, 765);
            this->richTextBox_code->TabIndex = 74;
            this->richTextBox_code->Text = L"";
            this->richTextBox_code->TextChanged += gcnew System::EventHandler(this, &CodeNote_N3::richTextBox_code_TextChanged);
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
            this->label5->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"label5.Image")));
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
            this->groupBox5->Controls->Add(this->lb_trangthai);
            this->groupBox5->Controls->Add(this->label10);
            this->groupBox5->Controls->Add(this->numericUpDown_K_step);
            this->groupBox5->Controls->Add(this->label18);
            this->groupBox5->Controls->Add(this->label19);
            this->groupBox5->Controls->Add(this->label20);
            this->groupBox5->Location = System::Drawing::Point(1231, 720);
            this->groupBox5->Name = L"groupBox5";
            this->groupBox5->Size = System::Drawing::Size(276, 141);
            this->groupBox5->TabIndex = 89;
            this->groupBox5->TabStop = false;
            // 
            // lb_trangthai
            // 
            this->lb_trangthai->AutoSize = true;
            this->lb_trangthai->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->lb_trangthai->Location = System::Drawing::Point(124, 73);
            this->lb_trangthai->Name = L"lb_trangthai";
            this->lb_trangthai->Size = System::Drawing::Size(93, 26);
            this->lb_trangthai->TabIndex = 10;
            this->lb_trangthai->Text = L"abcxyz..";
            this->lb_trangthai->Click += gcnew System::EventHandler(this, &CodeNote_N3::lb_trangthai_Click);
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
            // numericUpDown_K_step
            // 
            this->numericUpDown_K_step->Location = System::Drawing::Point(130, 19);
            this->numericUpDown_K_step->Name = L"numericUpDown_K_step";
            this->numericUpDown_K_step->Size = System::Drawing::Size(80, 26);
            this->numericUpDown_K_step->TabIndex = 9;
            this->numericUpDown_K_step->ValueChanged += gcnew System::EventHandler(this, &CodeNote_N3::numericUpDown_K_step_ValueChanged);
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
            // lb_ngoac_vuong
            // 
            this->lb_ngoac_vuong->AutoSize = true;
            this->lb_ngoac_vuong->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->lb_ngoac_vuong->Location = System::Drawing::Point(143, 200);
            this->lb_ngoac_vuong->Name = L"lb_ngoac_vuong";
            this->lb_ngoac_vuong->Size = System::Drawing::Size(66, 26);
            this->lb_ngoac_vuong->TabIndex = 14;
            this->lb_ngoac_vuong->Text = L"Dòng";
            this->lb_ngoac_vuong->Click += gcnew System::EventHandler(this, &CodeNote_N3::lb_ngoac_vuong_Click);
            // 
            // lb_ngoac_nhon
            // 
            this->lb_ngoac_nhon->AutoSize = true;
            this->lb_ngoac_nhon->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->lb_ngoac_nhon->Location = System::Drawing::Point(143, 159);
            this->lb_ngoac_nhon->Name = L"lb_ngoac_nhon";
            this->lb_ngoac_nhon->Size = System::Drawing::Size(66, 26);
            this->lb_ngoac_nhon->TabIndex = 13;
            this->lb_ngoac_nhon->Text = L"Dòng";
            this->lb_ngoac_nhon->Click += gcnew System::EventHandler(this, &CodeNote_N3::lb_ngoac_nhon_Click);
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
            this->groupBox4->Controls->Add(this->checkbox_findall);
            this->groupBox4->Controls->Add(this->rb_hoa_thuong);
            this->groupBox4->Controls->Add(this->rb_tu_thuong);
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
            this->btn_timkiem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_timkiem.Image")));
            this->btn_timkiem->Location = System::Drawing::Point(22, 263);
            this->btn_timkiem->Name = L"btn_timkiem";
            this->btn_timkiem->Size = System::Drawing::Size(226, 46);
            this->btn_timkiem->TabIndex = 13;
            this->btn_timkiem->Text = L"Tìm kiếm";
            this->btn_timkiem->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
            this->btn_timkiem->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
            this->btn_timkiem->UseVisualStyleBackColor = true;
            this->btn_timkiem->Click += gcnew System::EventHandler(this, &CodeNote_N3::btn_timkiem_Click);
            // 
            // checkbox_findall
            // 
            this->checkbox_findall->AutoSize = true;
            this->checkbox_findall->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->checkbox_findall->Location = System::Drawing::Point(22, 231);
            this->checkbox_findall->Name = L"checkbox_findall";
            this->checkbox_findall->Size = System::Drawing::Size(120, 26);
            this->checkbox_findall->TabIndex = 12;
            this->checkbox_findall->Text = L"Tìm cả tệp";
            this->checkbox_findall->UseVisualStyleBackColor = true;
            this->checkbox_findall->CheckedChanged += gcnew System::EventHandler(this, &CodeNote_N3::checkbox_findall_CheckedChanged);
            // 
            // rb_hoa_thuong
            // 
            this->rb_hoa_thuong->AutoSize = true;
            this->rb_hoa_thuong->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->rb_hoa_thuong->Location = System::Drawing::Point(22, 199);
            this->rb_hoa_thuong->Name = L"rb_hoa_thuong";
            this->rb_hoa_thuong->Size = System::Drawing::Size(201, 26);
            this->rb_hoa_thuong->TabIndex = 11;
            this->rb_hoa_thuong->TabStop = true;
            this->rb_hoa_thuong->Text = L"Phân biệt hoa/thường";
            this->rb_hoa_thuong->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            this->rb_hoa_thuong->UseVisualStyleBackColor = true;
            this->rb_hoa_thuong->CheckedChanged += gcnew System::EventHandler(this, &CodeNote_N3::rb_hoa_thuong_CheckedChanged);
            // 
            // rb_tu_thuong
            // 
            this->rb_tu_thuong->AutoSize = true;
            this->rb_tu_thuong->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->rb_tu_thuong->Location = System::Drawing::Point(22, 167);
            this->rb_tu_thuong->Name = L"rb_tu_thuong";
            this->rb_tu_thuong->Size = System::Drawing::Size(96, 26);
            this->rb_tu_thuong->TabIndex = 10;
            this->rb_tu_thuong->TabStop = true;
            this->rb_tu_thuong->Text = L"Thường";
            this->rb_tu_thuong->UseVisualStyleBackColor = true;
            this->rb_tu_thuong->CheckedChanged += gcnew System::EventHandler(this, &CodeNote_N3::rb_tu_thuong_CheckedChanged);
            // 
            // txt_tukhoa
            // 
            this->txt_tukhoa->Location = System::Drawing::Point(15, 97);
            this->txt_tukhoa->Multiline = true;
            this->txt_tukhoa->Name = L"txt_tukhoa";
            this->txt_tukhoa->Size = System::Drawing::Size(247, 36);
            this->txt_tukhoa->TabIndex = 9;
            this->txt_tukhoa->TextChanged += gcnew System::EventHandler(this, &CodeNote_N3::txt_tukhoa_TextChanged);
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
            this->groupBox3->Controls->Add(this->txt_thaythe);
            this->groupBox3->Controls->Add(this->btn_thaythe);
            this->groupBox3->Controls->Add(this->label11);
            this->groupBox3->Controls->Add(this->label16);
            this->groupBox3->Controls->Add(this->label17);
            this->groupBox3->Location = System::Drawing::Point(1231, 497);
            this->groupBox3->Name = L"groupBox3";
            this->groupBox3->Size = System::Drawing::Size(276, 141);
            this->groupBox3->TabIndex = 86;
            this->groupBox3->TabStop = false;
            // 
            // txt_thaythe
            // 
            this->txt_thaythe->Location = System::Drawing::Point(100, 15);
            this->txt_thaythe->Multiline = true;
            this->txt_thaythe->Name = L"txt_thaythe";
            this->txt_thaythe->Size = System::Drawing::Size(162, 36);
            this->txt_thaythe->TabIndex = 14;
            this->txt_thaythe->TextChanged += gcnew System::EventHandler(this, &CodeNote_N3::txt_thaythe_TextChanged);
            // 
            // btn_thaythe
            // 
            this->btn_thaythe->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btn_thaythe->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->btn_thaythe->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_thaythe.Image")));
            this->btn_thaythe->Location = System::Drawing::Point(22, 73);
            this->btn_thaythe->Name = L"btn_thaythe";
            this->btn_thaythe->Size = System::Drawing::Size(226, 46);
            this->btn_thaythe->TabIndex = 13;
            this->btn_thaythe->Text = L"Thay Thế";
            this->btn_thaythe->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
            this->btn_thaythe->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
            this->btn_thaythe->UseVisualStyleBackColor = true;
            this->btn_thaythe->Click += gcnew System::EventHandler(this, &CodeNote_N3::btn_thaythe_Click);
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
            // lb_ngoac_tron
            // 
            this->lb_ngoac_tron->AutoSize = true;
            this->lb_ngoac_tron->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->lb_ngoac_tron->Location = System::Drawing::Point(143, 108);
            this->lb_ngoac_tron->Name = L"lb_ngoac_tron";
            this->lb_ngoac_tron->Size = System::Drawing::Size(66, 26);
            this->lb_ngoac_tron->TabIndex = 12;
            this->lb_ngoac_tron->Text = L"Dòng";
            this->lb_ngoac_tron->Click += gcnew System::EventHandler(this, &CodeNote_N3::lb_ngoac_tron_Click);
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
            this->groupBox1->Controls->Add(this->lb_check_ngoac);
            this->groupBox1->Controls->Add(this->label15);
            this->groupBox1->Controls->Add(this->label14);
            this->groupBox1->Controls->Add(this->label13);
            this->groupBox1->Controls->Add(this->lb_ngoac_vuong);
            this->groupBox1->Controls->Add(this->lb_ngoac_nhon);
            this->groupBox1->Controls->Add(this->lb_ngoac_tron);
            this->groupBox1->Controls->Add(this->label9);
            this->groupBox1->Controls->Add(this->label8);
            this->groupBox1->Controls->Add(this->label7);
            this->groupBox1->Location = System::Drawing::Point(14, 351);
            this->groupBox1->Name = L"groupBox1";
            this->groupBox1->Size = System::Drawing::Size(276, 510);
            this->groupBox1->TabIndex = 79;
            this->groupBox1->TabStop = false;
            // 
            // lb_check_ngoac
            // 
            this->lb_check_ngoac->BackColor = System::Drawing::SystemColors::Control;
            this->lb_check_ngoac->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->lb_check_ngoac->ForeColor = System::Drawing::Color::Green;
            this->lb_check_ngoac->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb_check_ngoac.Image")));
            this->lb_check_ngoac->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
            this->lb_check_ngoac->Location = System::Drawing::Point(18, 44);
            this->lb_check_ngoac->Name = L"lb_check_ngoac";
            this->lb_check_ngoac->Size = System::Drawing::Size(258, 26);
            this->lb_check_ngoac->TabIndex = 18;
            this->lb_check_ngoac->Text = L"Ngoặc cân bằng!";
            this->lb_check_ngoac->TextAlign = System::Drawing::ContentAlignment::TopCenter;
            this->lb_check_ngoac->Click += gcnew System::EventHandler(this, &CodeNote_N3::lb_check_ngoac_Click);
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
            this->groupBox2->Controls->Add(this->lb_dong);
            this->groupBox2->Controls->Add(this->label3);
            this->groupBox2->Controls->Add(this->lb_Words);
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
            // label36
            // 
            this->label36->BackColor = System::Drawing::SystemColors::ActiveCaption;
            this->label36->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label36->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
            this->label36->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"label36.Image")));
            this->label36->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
            this->label36->Location = System::Drawing::Point(35, 118);
            this->label36->Name = L"label36";
            this->label36->Size = System::Drawing::Size(210, 32);
            this->label36->TabIndex = 103;
            this->label36->Text = L"Thống Kê";
            this->label36->TextAlign = System::Drawing::ContentAlignment::TopCenter;
            // 
            // label37
            // 
            this->label37->AutoSize = true;
            this->label37->BackColor = System::Drawing::SystemColors::ActiveCaption;
            this->label37->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label37->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
            this->label37->Location = System::Drawing::Point(1248, 674);
            this->label37->Name = L"label37";
            this->label37->Size = System::Drawing::Size(234, 26);
            this->label37->TabIndex = 104;
            this->label37->Text = L"Giới hạn Undo / Redo";
            // 
            // label38
            // 
            this->label38->AutoSize = true;
            this->label38->BackColor = System::Drawing::SystemColors::ActiveCaption;
            this->label38->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label38->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
            this->label38->Location = System::Drawing::Point(40, 889);
            this->label38->Name = L"label38";
            this->label38->Size = System::Drawing::Size(214, 26);
            this->label38->TabIndex = 105;
            this->label38->Text = L"Kết quả / thông báo";
            // 
            // lb_check
            // 
            this->lb_check->BackColor = System::Drawing::SystemColors::Control;
            this->lb_check->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->lb_check->ForeColor = System::Drawing::Color::Green;
            this->lb_check->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb_check.Image")));
            this->lb_check->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
            this->lb_check->Location = System::Drawing::Point(40, 959);
            this->lb_check->Name = L"lb_check";
            this->lb_check->Size = System::Drawing::Size(410, 26);
            this->lb_check->TabIndex = 19;
            this->lb_check->Text = L"Kiểm tra cú pháp thành công!";
            this->lb_check->TextAlign = System::Drawing::ContentAlignment::TopCenter;
            this->lb_check->Click += gcnew System::EventHandler(this, &CodeNote_N3::lb_check_Click);
            // 
            // label40
            // 
            this->label40->AutoSize = true;
            this->label40->BackColor = System::Drawing::SystemColors::ActiveCaption;
            this->label40->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label40->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
            this->label40->Location = System::Drawing::Point(29, 304);
            this->label40->Name = L"label40";
            this->label40->Size = System::Drawing::Size(198, 32);
            this->label40->TabIndex = 106;
            this->label40->Text = L"Kiểm tra ngoặc";
            // 
            // CodeNote_N3
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1520, 1063);
            this->Controls->Add(this->label40);
            this->Controls->Add(this->lb_check);
            this->Controls->Add(this->label38);
            this->Controls->Add(this->label37);
            this->Controls->Add(this->label36);
            this->Controls->Add(this->lb_limit_undo);
            this->Controls->Add(this->lb_che_do);
            this->Controls->Add(this->panel6);
            this->Controls->Add(this->lb_cot_n);
            this->Controls->Add(this->panel5);
            this->Controls->Add(this->lb_dong_n);
            this->Controls->Add(this->panel4);
            this->Controls->Add(this->lb_kiem_tra);
            this->Controls->Add(this->panel1);
            this->Controls->Add(this->pictureBox2);
            this->Controls->Add(this->pictureBox1);
            this->Controls->Add(this->textBox3);
            this->Controls->Add(this->label23);
            this->Controls->Add(this->label29);
            this->Controls->Add(this->toolStrip1);
            this->Controls->Add(this->textBox2);
            this->Controls->Add(this->richTextBox_code);
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
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_K_step))->EndInit();
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

#pragma region code_toolstripbutton_open_save_undo_redo_vv



    private: System::Void tsb_open_Click(System::Object^ sender, System::EventArgs^ e) {

    }
private: System::Void tsb_luu_save_Click(System::Object^ sender, System::EventArgs^ e) {

}
private: System::Void btn_undo_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void btn_redo_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void tsb_find_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void tsb_thaythe_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void tsb_thongke_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void tsb_check_Click(System::Object^ sender, System::EventArgs^ e) {

}
#pragma endregion

#pragma region Thong_ke_cac_tu



private: System::Void lb_Words_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void lb_dong_Click(System::Object^ sender, System::EventArgs^ e) {
}
#pragma endregion

#pragma region Kiem_tra_ngoac



private: System::Void lb_check_ngoac_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void lb_ngoac_tron_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void lb_ngoac_nhon_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void lb_ngoac_vuong_Click(System::Object^ sender, System::EventArgs^ e) {
}
#pragma endregion

#pragma region code_Tim_kiem_thay_the



private: System::Void txt_tukhoa_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void rb_tu_thuong_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void rb_hoa_thuong_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void checkbox_findall_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void btn_timkiem_Click(System::Object^ sender, System::EventArgs^ e) {
}

private: System::Void txt_thaythe_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void btn_thaythe_Click(System::Object^ sender, System::EventArgs^ e) {
}
#pragma endregion


#pragma region gioi_han_undo/redo



private: System::Void numericUpDown_K_step_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void lb_trangthai_Click(System::Object^ sender, System::EventArgs^ e) {
}
#pragma endregion

#pragma region Ketqua_thongbao



private: System::Void lb_check_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void lb_kiem_tra_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void lb_dong_n_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void lb_cot_n_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void lb_che_do_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void lb_limit_undo_Click(System::Object^ sender, System::EventArgs^ e) {
}
#pragma endregion

#pragma region Vung_bo_code



private: System::Void richTextBox_code_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
#pragma endregion
};
}
