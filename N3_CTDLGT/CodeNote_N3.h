#pragma once

#include "DoublyLinkedList.h"
#include "UndoRedoManager.h"
#include "SyntaxChecker.h"
#include <msclr/marshal_cppstd.h>

#define CN_WM_SETREDRAW 0x000B
#define CN_EM_GETSCROLLPOS (0x0400 + 221)
#define CN_EM_SETSCROLLPOS (0x0400 + 222)

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
	private:
		[System::Runtime::InteropServices::StructLayout(System::Runtime::InteropServices::LayoutKind::Sequential)]
		value struct Win32Point {
			int x;
			int y;
		};

		[System::Runtime::InteropServices::DllImport("user32.dll", CharSet = System::Runtime::InteropServices::CharSet::Auto)]
		static System::IntPtr SendMessage(System::IntPtr hWnd, int msg, System::IntPtr wParam, System::IntPtr lParam);

		[System::Runtime::InteropServices::DllImport("user32.dll", CharSet = System::Runtime::InteropServices::CharSet::Auto)]
		static System::IntPtr SendMessage(System::IntPtr hWnd, int msg, System::IntPtr wParam, Win32Point% lParam);

		DoublyLinkedList* coreDoc;
		UndoRedoManager* undoManager;
		std::string* lastSyncedText;
		TextPosition* lastCursorPos;
		bool _isApplyingUndoRedo;
		System::Windows::Forms::Timer^ syntaxHighlightTimer;

		std::string ToStdString(System::String^ s) {
			if (System::String::IsNullOrEmpty(s)) return "";
			return msclr::interop::marshal_as<std::string>(s);
		}
		System::String^ ToSysString(const std::string& s) {
			return gcnew System::String(s.c_str());
		}

	public:
		CodeNote_N3(void)
		{
			InitializeComponent();
#pragma region Phong_to_form
			// ===== TRAN VIEN FULL SIZE =====

			// 1. Thanh toolbar keo dai sang phai
			this->toolStrip1->Dock = System::Windows::Forms::DockStyle::Top;

			// 2. Khung code chinh giua - dan 4 huong
			this->richTextBox_code->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(
				System::Windows::Forms::AnchorStyles::Top |
				System::Windows::Forms::AnchorStyles::Bottom |
				System::Windows::Forms::AnchorStyles::Left |
				System::Windows::Forms::AnchorStyles::Right
			);

			// 3. Cot trai (Thong ke + Kiem tra ngoac) - ban sai ben trai
			System::Windows::Forms::AnchorStyles anchorTrai = static_cast<System::Windows::Forms::AnchorStyles>(
				System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left
			);
			this->groupBox2->Anchor = anchorTrai;
			this->groupBox1->Anchor = anchorTrai;
			this->textBox2->Anchor = anchorTrai;

			// 4. Cum Tim kiem / Thay the / Undo - ban sat men phai
			System::Windows::Forms::AnchorStyles anchorPhai = static_cast<System::Windows::Forms::AnchorStyles>(
				System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right
			);
			this->textBox4->Anchor = anchorPhai;
			this->label23->Anchor = anchorPhai;
			this->groupBox4->Anchor = anchorPhai;
			this->groupBox3->Anchor = anchorPhai;
			this->textBox6->Anchor = anchorPhai;
			this->label12->Anchor = anchorPhai;
			this->label37->Anchor = anchorPhai;
			this->groupBox5->Anchor = anchorPhai;

			// 5. Thanh ket qua + vung ve + thanh trang thai - ban sat day, keo tran chieu ngang
			System::Windows::Forms::AnchorStyles anchorDay = static_cast<System::Windows::Forms::AnchorStyles>(
				System::Windows::Forms::AnchorStyles::Bottom |
				System::Windows::Forms::AnchorStyles::Left |
				System::Windows::Forms::AnchorStyles::Right
			);
			this->textBox3->Anchor = anchorDay;
			this->pictureBox1->Anchor = anchorDay;
			this->pictureBox2->Anchor = anchorDay;

			// 6. Chu trang thai goc duoi trai
			System::Windows::Forms::AnchorStyles anchorDayTrai = static_cast<System::Windows::Forms::AnchorStyles>(
				System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left
			);
			this->label29->Anchor = anchorDayTrai;
			this->label38->Anchor = anchorDayTrai;
			this->lb_check->Anchor = anchorDayTrai;
			this->label30->Anchor = anchorDayTrai;
			this->label6->Anchor = anchorDayTrai;
			this->panel8->Anchor = anchorDayTrai;
			this->label21->Anchor = anchorDayTrai;
			this->panel9->Anchor = anchorDayTrai;
			this->label22->Anchor = anchorDayTrai;

			// 7. Chu trang thai goc duoi phai
			System::Windows::Forms::AnchorStyles anchorDayPhai = static_cast<System::Windows::Forms::AnchorStyles>(
				System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right
			);
			this->panel6->Anchor = anchorDayPhai;
			this->label31->Anchor = anchorDayPhai;
			this->panel7->Anchor = anchorDayPhai;
			this->label32->Anchor = anchorDayPhai;

			// 8. Mo toan man hinh
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;

			// Setup editor style: Dark theme giong VS Dark
			SetupEditorStyle();

			// Bat che do DoubleBuffered de tranh giat lag toan Form va PictureBox
			this->DoubleBuffered = true;
			this->SetStyle(System::Windows::Forms::ControlStyles::OptimizedDoubleBuffer |
				System::Windows::Forms::ControlStyles::AllPaintingInWmPaint |
				System::Windows::Forms::ControlStyles::UserPaint, true);

			// Timer debounce cho Syntax Highlighting (120ms): go phim muot ma khong giut lag
			this->syntaxHighlightTimer = gcnew System::Windows::Forms::Timer();
			this->syntaxHighlightTimer->Interval = 120;
			this->syntaxHighlightTimer->Tick += gcnew System::EventHandler(this, &CodeNote_N3::syntaxHighlightTimer_Tick);

			coreDoc = new DoublyLinkedList();
			coreDoc->appendLine("");
			undoManager = new UndoRedoManager(0);
			lastSyncedText = new std::string("");
			lastCursorPos = new TextPosition(0, 0);
			_isApplyingUndoRedo = false;
			this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &CodeNote_N3::pictureBox1_Paint);
			this->richTextBox_code->SelectionChanged += gcnew System::EventHandler(this, &CodeNote_N3::richTextBox_code_SelectionChanged);
			this->richTextBox_code->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &CodeNote_N3::richTextBox_code_KeyDown);
			UpdateUndoRedoUI();
			UpdateSyntaxBracketUI();
#pragma endregion
		}
#pragma region code_thua_thiet_ke_form

	protected:
		~CodeNote_N3()
		{
			if (coreDoc != nullptr) {
				delete coreDoc;
				coreDoc = nullptr;
			}
			if (undoManager != nullptr) {
				delete undoManager;
				undoManager = nullptr;
			}
			if (lastSyncedText != nullptr) {
				delete lastSyncedText;
				lastSyncedText = nullptr;
			}
			if (lastCursorPos != nullptr) {
				delete lastCursorPos;
				lastCursorPos = nullptr;
			}

			if (components)
			{
				delete components;
			}
		}

    protected:


    protected:

    private: System::Windows::Forms::Panel^ panel6;











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

private: System::Windows::Forms::Label^ label6;
private: System::Windows::Forms::Panel^ panel8;
private: System::Windows::Forms::Label^ label21;
private: System::Windows::Forms::Panel^ panel9;
private: System::Windows::Forms::Label^ label22;
private: System::Windows::Forms::Label^ label31;
private: System::Windows::Forms::Label^ label32;
private: System::Windows::Forms::ToolStripButton^ tsb_thoat;




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
            this->panel6 = (gcnew System::Windows::Forms::Panel());
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
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->panel8 = (gcnew System::Windows::Forms::Panel());
            this->label21 = (gcnew System::Windows::Forms::Label());
            this->panel9 = (gcnew System::Windows::Forms::Panel());
            this->label22 = (gcnew System::Windows::Forms::Label());
            this->label31 = (gcnew System::Windows::Forms::Label());
            this->label32 = (gcnew System::Windows::Forms::Label());
            this->tsb_thoat = (gcnew System::Windows::Forms::ToolStripButton());
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
            // panel6
            // 
            this->panel6->Location = System::Drawing::Point(1154, 1148);
            this->panel6->Name = L"panel6";
            this->panel6->Size = System::Drawing::Size(2, 57);
            this->panel6->TabIndex = 99;
            // 
            // pictureBox2
            // 
            this->pictureBox2->BackColor = System::Drawing::Color::LightGray;
            this->pictureBox2->Location = System::Drawing::Point(16, 1147);
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
            this->pictureBox1->Size = System::Drawing::Size(1490, 263);
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
            this->toolStrip1->Dock = System::Windows::Forms::DockStyle::None;
            this->toolStrip1->ImageScalingSize = System::Drawing::Size(24, 24);
            this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(9) {
                this->tsb_open, this->tsb_luu_save,
                    this->btn_undo, this->btn_redo, this->tsb_find, this->tsb_thaythe, this->tsb_thongke, this->tsb_check, this->tsb_thoat
            });
            this->toolStrip1->Location = System::Drawing::Point(0, 36);
            this->toolStrip1->Name = L"toolStrip1";
            this->toolStrip1->Size = System::Drawing::Size(1157, 58);
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
            this->menuStrip1->Dock = System::Windows::Forms::DockStyle::None;
            this->menuStrip1->GripMargin = System::Windows::Forms::Padding(2, 2, 0, 2);
            this->menuStrip1->GripStyle = System::Windows::Forms::ToolStripGripStyle::Visible;
            this->menuStrip1->ImageScalingSize = System::Drawing::Size(24, 24);
            this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
                this->thêmToolStripMenuItem,
                    this->chỉnhSửaToolStripMenuItem, this->côngCụToolStripMenuItem, this->trợGiúpToolStripMenuItem
            });
            this->menuStrip1->Location = System::Drawing::Point(0, 0);
            this->menuStrip1->Name = L"menuStrip1";
            this->menuStrip1->Size = System::Drawing::Size(435, 33);
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
            this->panel7->Location = System::Drawing::Point(1320, 1148);
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
            this->txt_thaythe->Location = System::Drawing::Point(100, 13);
            this->txt_thaythe->Multiline = true;
            this->txt_thaythe->Name = L"txt_thaythe";
            this->txt_thaythe->Size = System::Drawing::Size(162, 38);
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
            this->label28->AutoSize = false;
            this->label28->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label28->Location = System::Drawing::Point(55, 18);
            this->label28->Name = L"label28";
            this->label28->RightToLeft = System::Windows::Forms::RightToLeft::No;
            this->label28->Size = System::Drawing::Size(215, 46);
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
            // label6
            // 
            this->label6->AutoSize = true;
            this->label6->BackColor = System::Drawing::Color::LightGray;
            this->label6->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label6->Location = System::Drawing::Point(35, 1166);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(84, 23);
            this->label6->TabIndex = 84;
            this->label6->Text = L"Sẵn sàng";
            this->label6->Click += gcnew System::EventHandler(this, &CodeNote_N3::lb_kiem_tra_Click);
            // 
            // panel8
            // 
            this->panel8->Location = System::Drawing::Point(505, 1148);
            this->panel8->Name = L"panel8";
            this->panel8->Size = System::Drawing::Size(2, 57);
            this->panel8->TabIndex = 95;
            // 
            // label21
            // 
            this->label21->AutoSize = true;
            this->label21->BackColor = System::Drawing::Color::LightGray;
            this->label21->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label21->Location = System::Drawing::Point(543, 1166);
            this->label21->Name = L"label21";
            this->label21->Size = System::Drawing::Size(76, 23);
            this->label21->TabIndex = 96;
            this->label21->Text = L"Dòng: x";
            this->label21->Click += gcnew System::EventHandler(this, &CodeNote_N3::lb_dong_n_Click);
            // 
            // panel9
            // 
            this->panel9->Location = System::Drawing::Point(655, 1148);
            this->panel9->Name = L"panel9";
            this->panel9->Size = System::Drawing::Size(2, 57);
            this->panel9->TabIndex = 97;
            // 
            // label22
            // 
            this->label22->AutoSize = true;
            this->label22->BackColor = System::Drawing::Color::LightGray;
            this->label22->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label22->Location = System::Drawing::Point(682, 1166);
            this->label22->Name = L"label22";
            this->label22->Size = System::Drawing::Size(63, 23);
            this->label22->TabIndex = 98;
            this->label22->Text = L"Cột: y";
            this->label22->Click += gcnew System::EventHandler(this, &CodeNote_N3::lb_cot_n_Click);
            // 
            // label31
            // 
            this->label31->AutoSize = true;
            this->label31->BackColor = System::Drawing::Color::LightGray;
            this->label31->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label31->Location = System::Drawing::Point(1161, 1166);
            this->label31->Name = L"label31";
            this->label31->Size = System::Drawing::Size(117, 23);
            this->label31->TabIndex = 100;
            this->label31->Text = L"Chế độ: C++";
            this->label31->TextAlign = System::Drawing::ContentAlignment::TopRight;
            this->label31->Click += gcnew System::EventHandler(this, &CodeNote_N3::lb_che_do_Click);
            // 
            // label32
            // 
            this->label32->AutoSize = true;
            this->label32->BackColor = System::Drawing::Color::LightGray;
            this->label32->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label32->Location = System::Drawing::Point(1327, 1166);
            this->label32->Name = L"label32";
            this->label32->Size = System::Drawing::Size(169, 23);
            this->label32->TabIndex = 102;
            this->label32->Text = L"Limit undo: x bước";
            this->label32->TextAlign = System::Drawing::ContentAlignment::TopRight;
            this->label32->Click += gcnew System::EventHandler(this, &CodeNote_N3::lb_limit_undo_Click);
            // 
            // tsb_thoat
            // 
            this->tsb_thoat->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->tsb_thoat->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsb_thoat.Image")));
            this->tsb_thoat->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->tsb_thoat->Name = L"tsb_thoat";
            this->tsb_thoat->Size = System::Drawing::Size(72, 53);
            this->tsb_thoat->Text = L"Thoát";
            this->tsb_thoat->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
            this->tsb_thoat->Click += gcnew System::EventHandler(this, &CodeNote_N3::tsb_thoat_Click);
            // 
            // CodeNote_N3
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1520, 1215);
            this->Controls->Add(this->label40);
            this->Controls->Add(this->lb_check);
            this->Controls->Add(this->label38);
            this->Controls->Add(this->label37);
            this->Controls->Add(this->label36);
            this->Controls->Add(this->label32);
            this->Controls->Add(this->label31);
            this->Controls->Add(this->panel6);
            this->Controls->Add(this->label22);
            this->Controls->Add(this->panel9);
            this->Controls->Add(this->label21);
            this->Controls->Add(this->panel8);
            this->Controls->Add(this->label6);
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
            this->Controls->Add(this->pictureBox2);
            this->Controls->Add(this->pictureBox1);
            this->Name = L"CodeNote_N3";
            this->Text = L"CodeNote_N3";
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

#pragma region code_toolstripbutton_open_save (Thiện)
    private: System::Void tsb_open_Click(System::Object^ sender, System::EventArgs^ e) {
        if (coreDoc == nullptr) return;
        OpenFileDialog^ ofd = gcnew OpenFileDialog();
        ofd->Filter = L"Tệp văn bản (*.txt)|*.txt|Tệp mã nguồn C/C++ (*.cpp;*.h)|*.cpp;*.h|Tất cả tệp (*.*)|*.*";
        ofd->Title = L"Mở tệp vào CodeNote";
        if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
            std::string filePath = ToStdString(ofd->FileName);
            if (coreDoc->loadFromFile(filePath)) {
                _isApplyingUndoRedo = true;
                this->richTextBox_code->Text = ToSysString(coreDoc->getAllText());
                ApplySyntaxHighlighting();
                _isApplyingUndoRedo = false;

                if (undoManager != nullptr) {
                    undoManager->onDocumentOpened();
                }
                if (lastSyncedText != nullptr) {
                    *lastSyncedText = NormalizeLF(coreDoc->getAllText());
                }
                if (lastCursorPos != nullptr) {
                    *lastCursorPos = TextPosition(0, 0);
                }

                this->lb_check->Text = L"Đã mở tệp: " + System::IO::Path::GetFileName(ofd->FileName);
                this->label21->Text = L"Dòng: 1";
                this->label22->Text = L"Cột: 1";
                UpdateStatisticsUI();
                UpdateUndoRedoUI();
                UpdateSyntaxBracketUI();
                this->pictureBox1->Invalidate();
            } else {
                MessageBox::Show(L"Không thể mở tệp này!", L"Lỗi", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
    }

    private: System::Void tsb_luu_save_Click(System::Object^ sender, System::EventArgs^ e) {
        if (coreDoc == nullptr) return;
        SaveFileDialog^ sfd = gcnew SaveFileDialog();
        sfd->Filter = L"Tệp văn bản (*.txt)|*.txt|Tệp mã nguồn C/C++ (*.cpp;*.h)|*.cpp;*.h|Tất cả tệp (*.*)|*.*";
        sfd->Title = L"Lưu tệp từ CodeNote";
        if (sfd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
            std::string filePath = ToStdString(sfd->FileName);
            coreDoc->loadFromText(ToStdString(this->richTextBox_code->Text));
            if (coreDoc->saveToFile(filePath)) {
                this->lb_check->Text = L"Đã lưu tệp: " + System::IO::Path::GetFileName(sfd->FileName);
                MessageBox::Show(L"Đã lưu tệp thành công!", L"Thông báo", MessageBoxButtons::OK, MessageBoxIcon::Information);
            } else {
                MessageBox::Show(L"Không thể lưu tệp!", L"Lỗi", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
    }

    private: System::Void tsb_find_Click(System::Object^ sender, System::EventArgs^ e) {
        this->txt_tukhoa->Focus();
        btn_timkiem_Click(sender, e);
    }

    private: System::Void tsb_thaythe_Click(System::Object^ sender, System::EventArgs^ e) {
        this->txt_thaythe->Focus();
        btn_thaythe_Click(sender, e);
    }

    private: System::Void tsb_thongke_Click(System::Object^ sender, System::EventArgs^ e) {
        UpdateStatisticsUI();
        if (coreDoc != nullptr) {
            TextStatistics st = coreDoc->getStatistics();
            MessageBox::Show(L"KẾT QUẢ THỐNG KÊ VĂN BẢN:\n\n" +
                L"- Tổng số dòng: " + st.lineCount.ToString() + L"\n" +
                L"- Tổng số từ: " + st.wordCount.ToString() + L"\n" +
                L"- Tổng số ký tự (cả khoảng trắng): " + st.charCount.ToString() + L"\n" +
                L"- Tổng số ký tự (không tính khoảng trắng): " + st.charNoSpaceCount.ToString(),
                L"Thống kê CodeNote", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
    }
#pragma endregion

#pragma region Thong_ke_cac_tu (Thiện)
    private: System::Void lb_Words_Click(System::Object^ sender, System::EventArgs^ e) {
        UpdateStatisticsUI();
    }

    private: System::Void lb_dong_Click(System::Object^ sender, System::EventArgs^ e) {
        UpdateStatisticsUI();
    }
#pragma endregion

#pragma region Kiem_tra_ngoac (Phuc)
    private: System::Void UpdateSyntaxBracketUI() {
        if (coreDoc == nullptr) return;

        BracketCheckResult res = SyntaxChecker::checkDocument(*coreDoc, true);

        if (res.isBalanced) {
            this->lb_check_ngoac->Text = L"Ngoặc cân bằng!";
            this->lb_check_ngoac->ForeColor = System::Drawing::Color::Green;

            // ()
            if (res.roundOpenCount == 0 && res.roundCloseCount == 0) {
                this->lb_ngoac_tron->Text = L"Không có";
                this->lb_ngoac_tron->ForeColor = System::Drawing::Color::Gray;
            } else {
                this->lb_ngoac_tron->Text = L"Cân bằng (" + res.roundOpenCount.ToString() + L")";
                this->lb_ngoac_tron->ForeColor = System::Drawing::Color::Green;
            }

            // {}
            if (res.curlyOpenCount == 0 && res.curlyCloseCount == 0) {
                this->lb_ngoac_nhon->Text = L"Không có";
                this->lb_ngoac_nhon->ForeColor = System::Drawing::Color::Gray;
            } else {
                this->lb_ngoac_nhon->Text = L"Cân bằng (" + res.curlyOpenCount.ToString() + L")";
                this->lb_ngoac_nhon->ForeColor = System::Drawing::Color::Green;
            }

            // []
            if (res.squareOpenCount == 0 && res.squareCloseCount == 0) {
                this->lb_ngoac_vuong->Text = L"Không có";
                this->lb_ngoac_vuong->ForeColor = System::Drawing::Color::Gray;
            } else {
                this->lb_ngoac_vuong->Text = L"Cân bằng (" + res.squareOpenCount.ToString() + L")";
                this->lb_ngoac_vuong->ForeColor = System::Drawing::Color::Green;
            }
        } else {
            // Phat hien loi mat can bang
            this->lb_check_ngoac->Text = L"Mất cân bằng!";
            this->lb_check_ngoac->ForeColor = System::Drawing::Color::Crimson;

            char errChar = (res.foundChar != '\0') ? res.foundChar : res.expectedChar;
            bool isRound = (errChar == '(' || errChar == ')');
            bool isCurly = (errChar == '{' || errChar == '}');
            bool isSquare = (errChar == '[' || errChar == ']');

            // ()
            if (isRound) {
                this->lb_ngoac_tron->Text = L"Lỗi dòng " + (res.errorLine + 1).ToString();
                this->lb_ngoac_tron->ForeColor = System::Drawing::Color::Crimson;
            } else {
                if (res.roundOpenCount == res.roundCloseCount) {
                    this->lb_ngoac_tron->Text = (res.roundOpenCount == 0) ? L"Không có" : L"Cân bằng (" + res.roundOpenCount.ToString() + L")";
                    this->lb_ngoac_tron->ForeColor = (res.roundOpenCount == 0) ? System::Drawing::Color::Gray : System::Drawing::Color::Green;
                } else {
                    this->lb_ngoac_tron->Text = L"Lệch (" + res.roundOpenCount.ToString() + L"/" + res.roundCloseCount.ToString() + L")";
                    this->lb_ngoac_tron->ForeColor = System::Drawing::Color::DarkOrange;
                }
            }

            // {}
            if (isCurly) {
                this->lb_ngoac_nhon->Text = L"Lỗi dòng " + (res.errorLine + 1).ToString();
                this->lb_ngoac_nhon->ForeColor = System::Drawing::Color::Crimson;
            } else {
                if (res.curlyOpenCount == res.curlyCloseCount) {
                    this->lb_ngoac_nhon->Text = (res.curlyOpenCount == 0) ? L"Không có" : L"Cân bằng (" + res.curlyOpenCount.ToString() + L")";
                    this->lb_ngoac_nhon->ForeColor = (res.curlyOpenCount == 0) ? System::Drawing::Color::Gray : System::Drawing::Color::Green;
                } else {
                    this->lb_ngoac_nhon->Text = L"Lệch (" + res.curlyOpenCount.ToString() + L"/" + res.curlyCloseCount.ToString() + L")";
                    this->lb_ngoac_nhon->ForeColor = System::Drawing::Color::DarkOrange;
                }
            }

            // []
            if (isSquare) {
                this->lb_ngoac_vuong->Text = L"Lỗi dòng " + (res.errorLine + 1).ToString();
                this->lb_ngoac_vuong->ForeColor = System::Drawing::Color::Crimson;
            } else {
                if (res.squareOpenCount == res.squareCloseCount) {
                    this->lb_ngoac_vuong->Text = (res.squareOpenCount == 0) ? L"Không có" : L"Cân bằng (" + res.squareOpenCount.ToString() + L")";
                    this->lb_ngoac_vuong->ForeColor = (res.squareOpenCount == 0) ? System::Drawing::Color::Gray : System::Drawing::Color::Green;
                } else {
                    this->lb_ngoac_vuong->Text = L"Lệch (" + res.squareOpenCount.ToString() + L"/" + res.squareCloseCount.ToString() + L")";
                    this->lb_ngoac_vuong->ForeColor = System::Drawing::Color::DarkOrange;
                }
            }
        }
    }

    private: System::Void NavigateToBracketError(int line, int col) {
        if (this->richTextBox_code == nullptr || line < 0) return;
        try {
            int charIdx = this->richTextBox_code->GetFirstCharIndexFromLine(line);
            if (charIdx >= 0) {
                int targetPos = charIdx + (col >= 0 ? col : 0);
                if (targetPos > this->richTextBox_code->Text->Length) {
                    targetPos = this->richTextBox_code->Text->Length;
                }
                this->richTextBox_code->Focus();
                this->richTextBox_code->Select(targetPos, 1);
                this->richTextBox_code->ScrollToCaret();
            }
        } catch (...) {}
    }

    private: System::Void tsb_check_Click(System::Object^ sender, System::EventArgs^ e) {
        if (coreDoc == nullptr) return;
        UpdateSyntaxBracketUI();

        BracketCheckResult res = SyntaxChecker::checkDocument(*coreDoc, true);
        if (res.isBalanced) {
            this->lb_check->Text = L"Cú pháp ngoặc: Cân bằng hợp lệ!";
            MessageBox::Show(
                L"KẾT QUẢ KIỂM TRA NGOẶC:\n\n"
                L"✔ Tất cả các cặp ngoặc đều CÂN BẰNG hoàn hảo!\n\n"
                L"• Ngoặc tròn (): " + res.roundOpenCount.ToString() + L" cặp\n"
                L"• Ngoặc nhọn {}: " + res.curlyOpenCount.ToString() + L" cặp\n"
                L"• Ngoặc vuông []: " + res.squareOpenCount.ToString() + L" cặp",
                L"Kiểm tra ngoặc thành công",
                MessageBoxButtons::OK,
                MessageBoxIcon::Information
            );
        } else {
            String^ msg = ToSysString(res.message);
            this->lb_check->Text = msg;

            NavigateToBracketError(res.errorLine, res.errorCol);

            MessageBox::Show(
                L"PHÁT HIỆN LỖI NGOẶC:\n\n" + msg + L"\n\n"
                L"-> Con trỏ soạn thảo đã tự động chuyển đến dòng " + (res.errorLine + 1).ToString() + 
                L", cột " + (res.errorCol + 1).ToString() + L" để bạn dễ dàng quan sát và sửa lỗi.",
                L"Lỗi cú pháp ngoặc",
                MessageBoxButtons::OK,
                MessageBoxIcon::Warning
            );
        }
    }

    private: System::Void lb_check_ngoac_Click(System::Object^ sender, System::EventArgs^ e) {
        tsb_check_Click(sender, e);
    }
    private: System::Void lb_ngoac_tron_Click(System::Object^ sender, System::EventArgs^ e) {
        tsb_check_Click(sender, e);
    }
    private: System::Void lb_ngoac_nhon_Click(System::Object^ sender, System::EventArgs^ e) {
        tsb_check_Click(sender, e);
    }
    private: System::Void lb_ngoac_vuong_Click(System::Object^ sender, System::EventArgs^ e) {
        tsb_check_Click(sender, e);
    }
#pragma endregion

#pragma region code_Tim_kiem_thay_the (Thiện)
    private: System::Void txt_tukhoa_TextChanged(System::Object^ sender, System::EventArgs^ e) {
    }
    private: System::Void rb_tu_thuong_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    }
    private: System::Void rb_hoa_thuong_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    }
    private: System::Void checkbox_findall_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    }

    private: System::Void btn_timkiem_Click(System::Object^ sender, System::EventArgs^ e) {
        if (coreDoc == nullptr || String::IsNullOrEmpty(this->txt_tukhoa->Text)) {
            this->lb_check->Text = L"Vui lòng nhập từ khóa tìm kiếm!";
            return;
        }

        std::string keyword = ToStdString(this->txt_tukhoa->Text);
        bool matchCase = this->rb_hoa_thuong->Checked;
        bool findAllMatches = this->checkbox_findall->Checked;

        if (findAllMatches) {
            int totalCount = 0;
            SearchResult* results = coreDoc->findAll(keyword, totalCount, matchCase);

            if (totalCount > 0 && results != nullptr) {
                int currentSel = this->richTextBox_code->SelectionStart;
                int currentLen = this->richTextBox_code->SelectionLength;

                Win32Point searchScrollPt;
                searchScrollPt.x = 0;
                searchScrollPt.y = 0;
                SendMessage(this->richTextBox_code->Handle, CN_EM_GETSCROLLPOS, System::IntPtr::Zero, searchScrollPt);
                SendMessage(this->richTextBox_code->Handle, CN_WM_SETREDRAW, System::IntPtr::Zero, System::IntPtr::Zero);

                try {
                    this->richTextBox_code->SelectAll();
                    this->richTextBox_code->SelectionBackColor = Color::White;
                    this->richTextBox_code->SelectionColor = Color::Black;

                    SearchResult* curRes = results;
                    while (curRes != nullptr) {
                        int charIdx = this->richTextBox_code->GetFirstCharIndexFromLine(curRes->line) + curRes->col;
                        if (charIdx >= 0) {
                            this->richTextBox_code->Select(charIdx, curRes->length);
                            this->richTextBox_code->SelectionBackColor = Color::Yellow;
                            this->richTextBox_code->SelectionColor = Color::Black;
                        }
                        curRes = curRes->next;
                    }

                    this->richTextBox_code->Select(currentSel, currentLen);
                    SendMessage(this->richTextBox_code->Handle, CN_EM_SETSCROLLPOS, System::IntPtr::Zero, searchScrollPt);
                }
                finally {
                    SendMessage(this->richTextBox_code->Handle, CN_WM_SETREDRAW, (System::IntPtr)1, System::IntPtr::Zero);
                    this->richTextBox_code->Invalidate();
                }

                DoublyLinkedList::freeSearchResults(results);

                this->lb_check->Text = L"Tìm thấy tất cả " + totalCount.ToString() + L" vị trí chứa '" + this->txt_tukhoa->Text + L"'";
            } else {
                this->lb_check->Text = L"Không tìm thấy từ khóa: '" + this->txt_tukhoa->Text + L"'";
            }
        } else {
            int selStart = this->richTextBox_code->SelectionStart;
            int curLine = this->richTextBox_code->GetLineFromCharIndex(selStart);
            int curCol = selStart - this->richTextBox_code->GetFirstCharIndexFromLine(curLine);

            int foundLine = -1;
            int foundCol = -1;
            bool found = coreDoc->findNext(keyword, curLine, curCol, foundLine, foundCol, matchCase);

            if (found) {
                int charIdx = this->richTextBox_code->GetFirstCharIndexFromLine(foundLine) + foundCol;
                this->richTextBox_code->Select(charIdx, (int)keyword.length());
                this->richTextBox_code->Focus();
                this->lb_check->Text = L"Tìm thấy tại: Dòng " + (foundLine + 1).ToString() + L", Cột " + (foundCol + 1).ToString();
                this->label21->Text = L"Dòng: " + (foundLine + 1).ToString();
                this->label22->Text = L"Cột: " + (foundCol + 1).ToString();
            } else {
                this->lb_check->Text = L"Không tìm thấy từ khóa: '" + this->txt_tukhoa->Text + L"'";
            }
        }
    }

    private: System::Void txt_thaythe_TextChanged(System::Object^ sender, System::EventArgs^ e) {
    }

    private: System::Void btn_thaythe_Click(System::Object^ sender, System::EventArgs^ e) {
        if (coreDoc == nullptr || String::IsNullOrEmpty(this->txt_tukhoa->Text)) {
            this->lb_check->Text = L"Vui lòng nhập từ khóa cần thay thế!";
            return;
        }

        std::string target = ToStdString(this->txt_tukhoa->Text);
        std::string replacement = ToStdString(this->txt_thaythe->Text);
        bool matchCase = this->rb_hoa_thuong->Checked;

        int count = coreDoc->replaceAll(target, replacement, matchCase);

        if (count > 0) {
            int selStart = this->richTextBox_code->SelectionStart;
            this->richTextBox_code->Text = ToSysString(coreDoc->getAllText());
            this->richTextBox_code->SelectionStart = Math::Min(selStart, this->richTextBox_code->Text->Length);
            this->lb_check->Text = L"Đã thay thế thành công " + count.ToString() + L" vị trí!";
            UpdateStatisticsUI();
            this->pictureBox1->Invalidate();
        } else {
            this->lb_check->Text = L"Không tìm thấy từ khóa '" + this->txt_tukhoa->Text + L"' để thay thế!";
        }
    }
#pragma endregion

#pragma region gioi_han_undo/redo (Phuc)
    private:
        std::string NormalizeLF(const std::string& text) {
            std::string out;
            out.reserve(text.length());
            for (size_t i = 0; i < text.length(); ++i) {
                if (text[i] != '\r') {
                    out += text[i];
                }
            }
            return out;
        }

        TextPosition LinearOffsetToPos(const std::string& lfText, int offset) {
            if (offset < 0) offset = 0;
            int maxLen = static_cast<int>(lfText.length());
            int limit = (offset < maxLen) ? offset : maxLen;
            int line = 0;
            int col = 0;
            for (int i = 0; i < limit; ++i) {
                if (lfText[i] == '\n') {
                    line++;
                    col = 0;
                } else {
                    col++;
                }
            }
            return TextPosition(line, col);
        }

        int PosToLinearOffset(const std::string& lfText, const TextPosition& pos) {
            int curLine = 0;
            int curCol = 0;
            for (size_t i = 0; i < lfText.length(); ++i) {
                if (curLine == pos.line && curCol == pos.col) {
                    return static_cast<int>(i);
                }
                if (lfText[i] == '\n') {
                    if (curLine == pos.line) {
                        return static_cast<int>(i);
                    }
                    curLine++;
                    curCol = 0;
                } else {
                    curCol++;
                }
            }
            return static_cast<int>(lfText.length());
        }

        void RecordDiffAction(const std::string& oldText,
                              const std::string& newText,
                              const TextPosition& cursorBefore,
                              const TextPosition& cursorAfter) {
            if (undoManager == nullptr) return;

            size_t oldLen = oldText.length();
            size_t newLen = newText.length();
            size_t minLen = (oldLen < newLen) ? oldLen : newLen;

            size_t prefix = 0;
            while (prefix < minLen && oldText[prefix] == newText[prefix]) {
                prefix++;
            }

            size_t suffix = 0;
            while (suffix < (oldLen - prefix) &&
                   suffix < (newLen - prefix) &&
                   oldText[oldLen - 1 - suffix] == newText[newLen - 1 - suffix]) {
                suffix++;
            }

            size_t removedLen = oldLen - prefix - suffix;
            size_t insertedLen = newLen - prefix - suffix;
            if (removedLen == 0 && insertedLen == 0) {
                return;
            }

            std::string removed = oldText.substr(prefix, removedLen);
            std::string inserted = newText.substr(prefix, insertedLen);
            TextPosition startPos = LinearOffsetToPos(oldText, static_cast<int>(prefix));

            ::Action act;
            if (removedLen == 0) {
                if (inserted == "\n") {
                    act = UndoRedoManager::makeSplitLine(startPos, cursorBefore, cursorAfter);
                } else if (inserted.length() == 1) {
                    act = UndoRedoManager::makeInsertChar(startPos, inserted[0], cursorBefore, cursorAfter);
                } else {
                    act = UndoRedoManager::makeInsertText(startPos, inserted, cursorBefore, cursorAfter);
                }
            } else if (insertedLen == 0) {
                if (removed == "\n") {
                    act = UndoRedoManager::makeMergeLine(startPos, cursorBefore, cursorAfter);
                } else if (removed.length() == 1) {
                    act = UndoRedoManager::makeDeleteChar(startPos, removed[0], cursorBefore, cursorAfter);
                } else {
                    act = UndoRedoManager::makeDeleteText(startPos, removed, cursorBefore, cursorAfter);
                }
            } else {
                act = UndoRedoManager::makeReplaceText(startPos, removed, inserted, cursorBefore, cursorAfter);
            }

            undoManager->recordAction(act);
        }

        void ApplyActionToCoreDoc(const ::Action& act) {
            if (coreDoc == nullptr) return;
            switch (act.type) {
                case ActionType::INSERT_CHAR:
                    if (!act.content.empty()) {
                        coreDoc->insertChar(act.startPos.line, act.startPos.col, act.content[0]);
                    }
                    break;
                case ActionType::DELETE_CHAR:
                    coreDoc->deleteChar(act.startPos.line, act.startPos.col);
                    break;
                case ActionType::INSERT_TEXT:
                    coreDoc->insertTextAt(act.startPos.line, act.startPos.col, act.content);
                    break;
                case ActionType::DELETE_TEXT:
                    coreDoc->deleteRange(act.startPos.line, act.startPos.col, act.endPos.line, act.endPos.col);
                    break;
                case ActionType::INSERT_LINE:
                    coreDoc->insertLine(act.startPos.line, act.content);
                    break;
                case ActionType::DELETE_LINE:
                    coreDoc->deleteLine(act.startPos.line);
                    break;
                case ActionType::SPLIT_LINE:
                    coreDoc->splitLine(act.startPos.line, act.startPos.col);
                    break;
                case ActionType::MERGE_LINE:
                    coreDoc->mergeLines(act.endPos.line);
                    break;
                case ActionType::REPLACE_TEXT:
                {
                    bool multiLine = (act.previousContent.find('\n') != std::string::npos) ||
                                     (act.content.find('\n') != std::string::npos);
                    if (!multiLine) {
                        coreDoc->replaceAt(act.startPos.line,
                                           act.startPos.col,
                                           static_cast<int>(act.previousContent.length()),
                                           act.content);
                    } else {
                        TextPosition oldEnd = UndoRedoManager::computeEndPosition(act.startPos, act.previousContent);
                        coreDoc->deleteRange(act.startPos.line, act.startPos.col, oldEnd.line, oldEnd.col);
                        if (!act.content.empty()) {
                            coreDoc->insertTextAt(act.startPos.line, act.startPos.col, act.content);
                        }
                    }
                    break;
                }
            }
            if (coreDoc->isEmpty()) {
                coreDoc->appendLine("");
            }
        }

        void ExecuteHistoryAction(const ::Action& act, bool isUndo) {
            if (coreDoc == nullptr) return;
            ApplyActionToCoreDoc(act);

            std::string updatedText = coreDoc->getAllText();
            std::string normalized = NormalizeLF(updatedText);

            TextPosition targetCursor = act.cursorAfter;
            coreDoc->clampCursor(targetCursor.line, targetCursor.col);
            int targetOffset = PosToLinearOffset(normalized, targetCursor);

            _isApplyingUndoRedo = true;
            Win32Point undoScrollPt;
            undoScrollPt.x = 0;
            undoScrollPt.y = 0;
            SendMessage(this->richTextBox_code->Handle, CN_EM_GETSCROLLPOS, System::IntPtr::Zero, undoScrollPt);
            SendMessage(this->richTextBox_code->Handle, CN_WM_SETREDRAW, System::IntPtr::Zero, System::IntPtr::Zero);

            try {
                this->richTextBox_code->Text = ToSysString(updatedText);
                int maxLen = this->richTextBox_code->Text->Length;
                int clampedOffset = (targetOffset < 0) ? 0 : ((targetOffset > maxLen) ? maxLen : targetOffset);
                this->richTextBox_code->SelectionStart = clampedOffset;
                this->richTextBox_code->SelectionLength = 0;

                if (lastSyncedText != nullptr) {
                    *lastSyncedText = normalized;
                }
                if (lastCursorPos != nullptr) {
                    *lastCursorPos = targetCursor;
                }

                ApplySyntaxHighlighting();

                this->richTextBox_code->SelectionStart = clampedOffset;
                this->richTextBox_code->SelectionLength = 0;
                SendMessage(this->richTextBox_code->Handle, CN_EM_SETSCROLLPOS, System::IntPtr::Zero, undoScrollPt);
            }
            finally {
                SendMessage(this->richTextBox_code->Handle, CN_WM_SETREDRAW, (System::IntPtr)1, System::IntPtr::Zero);
                this->richTextBox_code->Invalidate();
                _isApplyingUndoRedo = false;
            }

            this->label21->Text = L"Dòng: " + (targetCursor.line + 1).ToString();
            this->label22->Text = L"Cột: " + (targetCursor.col + 1).ToString();
            UpdateStatisticsUI();
            UpdateUndoRedoUI();
            UpdateSyntaxBracketUI();
            this->pictureBox1->Invalidate();
            this->lb_check->Text = isUndo ? L"Đã hoàn tác thao tác!" : L"Đã làm lại thao tác!";
            this->richTextBox_code->Focus();
        }

        void UpdateUndoRedoUI() {
            if (undoManager == nullptr) return;
            this->lb_trangthai->Text = L"Undo: " + undoManager->getUndoCount().ToString()
                + L" | Redo: " + undoManager->getRedoCount().ToString();
            if (undoManager->isUndoUnlimited()) {
                this->label32->Text = L"Limit undo: Không giới hạn";
            } else {
                this->label32->Text = L"Limit undo: " + undoManager->getMaxUndoSteps().ToString() + L" bước";
            }
        }

    private: System::Void btn_undo_Click(System::Object^ sender, System::EventArgs^ e) {
        if (undoManager == nullptr || coreDoc == nullptr) return;
        ::Action invAct;
        if (undoManager->undo(invAct)) {
            ExecuteHistoryAction(invAct, true);
        } else {
            this->lb_check->Text = L"Không còn thao tác để hoàn tác!";
        }
    }
    private: System::Void btn_redo_Click(System::Object^ sender, System::EventArgs^ e) {
        if (undoManager == nullptr || coreDoc == nullptr) return;
        ::Action redoAct;
        if (undoManager->redo(redoAct)) {
            ExecuteHistoryAction(redoAct, false);
        } else {
            this->lb_check->Text = L"Không còn thao tác để làm lại!";
        }
    }
    private: System::Void numericUpDown_K_step_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
        if (undoManager == nullptr) return;
        int k = System::Decimal::ToInt32(this->numericUpDown_K_step->Value);
        if (undoManager->setMaxUndoSteps(k)) {
            UpdateUndoRedoUI();
            if (k == 0) {
                this->lb_check->Text = L"Giới hạn Undo: Không giới hạn";
            } else {
                this->lb_check->Text = L"Đã đặt giới hạn Undo: " + k.ToString() + L" bước";
            }
        }
    }
    private: System::Void lb_trangthai_Click(System::Object^ sender, System::EventArgs^ e) {
        UpdateUndoRedoUI();
    }
    private: System::Void richTextBox_code_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
        if (e->Control && !e->Alt && !e->Shift) {
            if (e->KeyCode == Keys::Z) {
                e->Handled = true;
                e->SuppressKeyPress = true;
                btn_undo_Click(sender, e);
            } else if (e->KeyCode == Keys::Y) {
                e->Handled = true;
                e->SuppressKeyPress = true;
                btn_redo_Click(sender, e);
            }
        }
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

#pragma region Vung_bo_code (Thiện)
    private:
        bool _isHighlighting = false;

        // Setup RichTextBox giong VS Dark Theme - goi 1 lan trong constructor
        void SetupEditorStyle() {
            RichTextBox^ rtb = this->richTextBox_code;
            rtb->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);
            rtb->ForeColor = System::Drawing::Color::FromArgb(220, 220, 220);
            rtb->Font = gcnew System::Drawing::Font(L"Consolas", 11, System::Drawing::FontStyle::Regular);
        }

        void ColorRange(RichTextBox^ rtb, int start, int length, System::Drawing::Color fg) {
            if (start < 0 || length <= 0 || start + length > rtb->Text->Length) return;
            rtb->Select(start, length);
            rtb->SelectionColor = fg;
        }

        private: System::Void syntaxHighlightTimer_Tick(System::Object^ sender, System::EventArgs^ e) {
            if (this->syntaxHighlightTimer != nullptr) {
                this->syntaxHighlightTimer->Stop();
            }
            ApplySyntaxHighlighting();
            UpdateSyntaxBracketUI();
        }

        void ApplySyntaxHighlighting() {
            if (_isHighlighting || this->richTextBox_code == nullptr) return;
            if (!this->richTextBox_code->IsHandleCreated) return;
            _isHighlighting = true;

            RichTextBox^ rtb = this->richTextBox_code;

            // 1. Luu vi tri con tro va toa do cuon (pixel scroll position)
            int selStart = rtb->SelectionStart;
            int selLen = rtb->SelectionLength;
            Win32Point scrollPt;
            scrollPt.x = 0;
            scrollPt.y = 0;
            SendMessage(rtb->Handle, CN_EM_GETSCROLLPOS, System::IntPtr::Zero, scrollPt);

            // 2. KHOA VE (WM_SETREDRAW = 0) - Tuyet doi khong de Windows RichEdit ve giat tren man hinh
            SendMessage(rtb->Handle, CN_WM_SETREDRAW, System::IntPtr::Zero, System::IntPtr::Zero);

            try {
                String^ text = rtb->Text;
                int len = text->Length;
                if (len == 0) return;

                // Reset ve mau mac dinh (nen den, chu xam sang)
                rtb->SelectAll();
                rtb->SelectionBackColor = System::Drawing::Color::FromArgb(30, 30, 30);
                rtb->SelectionColor = System::Drawing::Color::FromArgb(220, 220, 220);

                // 1. Tu khoa C++ - mau xanh duong
                System::Drawing::Color kwColor = System::Drawing::Color::FromArgb(86, 156, 214);
                array<String^>^ keywords = {
                    L"int", L"float", L"double", L"char", L"bool", L"void",
                    L"return", L"if", L"else", L"for", L"while", L"do",
                    L"switch", L"case", L"break", L"continue", L"default",
                    L"class", L"struct", L"new", L"delete", L"nullptr",
                    L"true", L"false", L"const", L"static", L"public",
                    L"private", L"protected", L"namespace", L"using",
                    L"typedef", L"enum", L"template", L"auto", L"long",
                    L"short", L"unsigned", L"signed", L"try", L"catch",
                    L"throw", L"virtual", L"override", L"string"
                };
                for each (String^ kw in keywords) {
                    int pos = 0;
                    while ((pos = text->IndexOf(kw, pos, System::StringComparison::Ordinal)) >= 0) {
                        bool leftOk  = (pos == 0 || (!Char::IsLetterOrDigit(text[pos - 1]) && text[pos - 1] != L'_'));
                        bool rightOk = (pos + kw->Length >= len || (!Char::IsLetterOrDigit(text[pos + kw->Length]) && text[pos + kw->Length] != L'_'));
                        if (leftOk && rightOk)
                            ColorRange(rtb, pos, kw->Length, kwColor);
                        pos += kw->Length;
                    }
                }

                // 2. Chuoi string - mau cam
                System::Drawing::Color strColor = System::Drawing::Color::FromArgb(206, 145, 120);
                int i = 0;
                while (i < len) {
                    if (text[i] == L'"') {
                        int end = i + 1;
                        while (end < len && text[end] != L'"') {
                            if (text[end] == L'\\') end++;
                            end++;
                        }
                        ColorRange(rtb, i, Math::Min(end - i + 1, len - i), strColor);
                        i = end + 1;
                    } else { i++; }
                }

                // 3. Comment // - mau xanh la
                System::Drawing::Color cmtColor = System::Drawing::Color::FromArgb(106, 153, 85);
                i = 0;
                while (i < len - 1) {
                    if (text[i] == L'/' && text[i+1] == L'/') {
                        int end = text->IndexOf(L'\n', i);
                        if (end < 0) end = len;
                        ColorRange(rtb, i, end - i, cmtColor);
                        i = end + 1;
                    } else { i++; }
                }

                // 4. Comment /* */ - mau xanh la
                i = 0;
                while (i < len - 1) {
                    if (text[i] == L'/' && text[i+1] == L'*') {
                        int end = text->IndexOf(L"*/", i + 2);
                        if (end < 0) end = len - 2;
                        ColorRange(rtb, i, end - i + 2, cmtColor);
                        i = end + 2;
                    } else { i++; }
                }

                // 5. Preprocessor #include #define - mau tim
                System::Drawing::Color ppColor = System::Drawing::Color::FromArgb(155, 155, 255);
                i = 0;
                while (i < len) {
                    if (text[i] == L'#') {
                        int end = text->IndexOf(L'\n', i);
                        if (end < 0) end = len;
                        ColorRange(rtb, i, end - i, ppColor);
                        i = end + 1;
                    } else { i++; }
                }

                // 6. So - mau vang xanh nhat
                System::Drawing::Color numColor = System::Drawing::Color::FromArgb(181, 206, 168);
                i = 0;
                while (i < len) {
                    if (Char::IsDigit(text[i])) {
                        bool leftNum = (i == 0 || (!Char::IsLetterOrDigit(text[i-1]) && text[i-1] != L'_'));
                        if (leftNum) {
                            int end = i;
                            while (end < len && (Char::IsDigit(text[end]) || text[end] == L'.')) end++;
                            ColorRange(rtb, i, end - i, numColor);
                            i = end;
                            continue;
                        }
                    }
                    i++;
                }
            }
            finally {
                // 3. Khoi phuc lai chinh xac vi tri con tro va toa do cuon
                rtb->Select(selStart, selLen);
                SendMessage(rtb->Handle, CN_EM_SETSCROLLPOS, System::IntPtr::Zero, scrollPt);

                // 4. MO KHOA VE (WM_SETREDRAW = 1) va ve lai 1 lan duy nhat
                SendMessage(rtb->Handle, CN_WM_SETREDRAW, (System::IntPtr)1, System::IntPtr::Zero);
                rtb->Invalidate();
                _isHighlighting = false;
            }
        }

    private: System::Void richTextBox_code_TextChanged(System::Object^ sender, System::EventArgs^ e) {
        if (coreDoc == nullptr || _isApplyingUndoRedo || _isHighlighting) return;

        std::string fullText = ToStdString(this->richTextBox_code->Text);
        std::string newNormalized = NormalizeLF(fullText);
        TextPosition curBefore = (lastCursorPos != nullptr) ? *lastCursorPos : TextPosition(0, 0);
        TextPosition curAfter = LinearOffsetToPos(newNormalized, this->richTextBox_code->SelectionStart);

        if (lastSyncedText != nullptr) {
            RecordDiffAction(*lastSyncedText, newNormalized, curBefore, curAfter);
            *lastSyncedText = newNormalized;
        }
        if (lastCursorPos != nullptr) {
            *lastCursorPos = curAfter;
        }

        coreDoc->loadFromText(fullText);

        UpdateStatisticsUI();
        UpdateUndoRedoUI();
        this->pictureBox1->Invalidate();

        // Su dung timer debounce: go phim muot ma tuc thoi, khong bi giut lag
        if (this->syntaxHighlightTimer != nullptr) {
            this->syntaxHighlightTimer->Stop();
            this->syntaxHighlightTimer->Start();
        } else {
            ApplySyntaxHighlighting();
        }
    }

    private: System::Void richTextBox_code_SelectionChanged(System::Object^ sender, System::EventArgs^ e) {
        if (this->richTextBox_code == nullptr) return;
        int sel = this->richTextBox_code->SelectionStart;
        int line = this->richTextBox_code->GetLineFromCharIndex(sel);
        int col = sel - this->richTextBox_code->GetFirstCharIndexFromLine(line);
        this->label21->Text = L"Dòng: " + (line + 1).ToString();
        this->label22->Text = L"Cột: " + (col + 1).ToString();
        if (!_isHighlighting && !_isApplyingUndoRedo && lastCursorPos != nullptr && lastSyncedText != nullptr) {
            *lastCursorPos = LinearOffsetToPos(*lastSyncedText, sel);
        }
    }

    private: System::Void UpdateStatisticsUI() {
        if (coreDoc == nullptr) return;
        TextStatistics st = coreDoc->getStatistics();
        this->lb_Words->Text = st.wordCount.ToString("N0");
        this->lb_dong->Text = st.lineCount.ToString("N0") + L" dòng";
        this->label28->Text = st.charCount.ToString("N0") + L" ký tự\r\n(" + st.charNoSpaceCount.ToString("N0") + L" ký tự không cách)";
    }
#pragma endregion

#pragma region Truc_quan_hoa_DSLK (Thiện)
    private: System::Void pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
        if (coreDoc == nullptr) return;
        Graphics^ g = e->Graphics;
        g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

        int totalLines = coreDoc->getSize();
        if (totalLines == 0) {
            System::Drawing::Font^ f = gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Italic);
            g->DrawString(L"Danh sách liên kết kép rỗng (head = tail = NULL)", f, Brushes::Gray, 10, 18);
            return;
        }

        int nodeW = 110;
        int nodeH = 36;
        int startX = 20;
        int startY = 11;
        int gap = 45;

        System::Drawing::Font^ fontNode = gcnew System::Drawing::Font(L"Consolas", 8, FontStyle::Bold);
        System::Drawing::Font^ fontText = gcnew System::Drawing::Font(L"Segoe UI", 8, FontStyle::Regular);
        Pen^ penBox = gcnew Pen(Color::FromArgb(37, 99, 235), 1.5f);
        Pen^ penArrow = gcnew Pen(Color::FromArgb(234, 88, 12), 2.0f);
        penArrow->CustomEndCap = gcnew System::Drawing::Drawing2D::AdjustableArrowCap(4, 4);
        penArrow->CustomStartCap = gcnew System::Drawing::Drawing2D::AdjustableArrowCap(4, 4);

        int maxDraw = Math::Min(totalLines, 8);
        Node* curr = coreDoc->getHead();

        for (int i = 0; i < maxDraw && curr != nullptr; ++i) {
            int x = startX + i * (nodeW + gap);

            System::Drawing::Rectangle rect(x, startY, nodeW, nodeH);
            g->FillRectangle(Brushes::AliceBlue, rect);
            g->DrawRectangle(penBox, rect);

            g->DrawLine(Pens::LightSlateGray, x + 24, startY, x + 24, startY + nodeH);
            g->DrawLine(Pens::LightSlateGray, x + nodeW - 24, startY, x + nodeW - 24, startY + nodeH);

            g->DrawString(L"P", fontNode, Brushes::DarkSlateGray, (float)(x + 6), (float)(startY + 10));
            g->DrawString(L"N", fontNode, Brushes::DarkSlateGray, (float)(x + nodeW - 18), (float)(startY + 10));

            std::string lineStr = curr->lineData;
            if (lineStr.length() > 6) lineStr = lineStr.substr(0, 5) + "..";
            if (lineStr.empty()) lineStr = "(rong)";
            String^ displayText = gcnew String(lineStr.c_str());
            g->DrawString(displayText, fontText, Brushes::DarkBlue, (float)(x + 27), (float)(startY + 10));

            if (i == 0) {
                g->DrawString(L"[HEAD]", fontNode, Brushes::Crimson, (float)(x + 30), (float)(startY - 11));
            }
            if (curr == coreDoc->getTail() || i == totalLines - 1) {
                g->DrawString(L"[TAIL]", fontNode, Brushes::Crimson, (float)(x + 30), (float)(startY + nodeH + 1));
            }

            if (i < maxDraw - 1 && curr->next != nullptr) {
                int arrowStartX = x + nodeW;
                int arrowEndX = arrowStartX + gap;
                int arrowY = startY + nodeH / 2;
                g->DrawLine(penArrow, arrowStartX + 2, arrowY, arrowEndX - 2, arrowY);
            }

            curr = curr->next;
        }

        if (totalLines > maxDraw) {
            int moreX = startX + maxDraw * (nodeW + gap) - 20;
            g->DrawString(L"... (" + (totalLines - maxDraw) + L" dòng nữa)", fontText, Brushes::DarkGray, (float)moreX, (float)(startY + 10));
        }
    }
#pragma endregion




#pragma region bo_sung_nut_thoat
private: System::Void tsb_thoat_Click(System::Object^ sender, System::EventArgs^ e) {
    // 1. Hiển thị thông báo hỏi người dùng
    System::Windows::Forms::DialogResult result = MessageBox::Show(
        L"Bạn có muốn thoát không?",
        L"Xác nhận",
        MessageBoxButtons::YesNo,
        MessageBoxIcon::Question
    );
    // 2. Nếu người dùng bấm "Yes" thì đóng Form
    if (result == System::Windows::Forms::DialogResult::Yes) {
        this->Close();
    }
}
#pragma endregion
};
}
