#pragma once

#include <queue>
#include <cliext\vector>

namespace Sort {

	using namespace System;
	
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	/// <summary>
	/// Summary for MyForm
	/// </summary>

	// ������ ��� �������� ������� ��������� �����
	std::vector<std::vector<int>> edges;
	
	int value;
	//��������� ������� ��� ����������
	int start{ 0 };
	
	public ref class MyForm : public System::Windows::Forms::Form
	{
	
	
	public:

		
		bool Progress, Pause;//��������� ���������
	private: System::Windows::Forms::TrackBar^ trackBar1;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::NumericUpDown^ numericUpDown3;
	private: System::Windows::Forms::Label^ label5;
	public:
	private: System::Windows::Forms::Button^ buttonContinue;
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			ew = gcnew EventWaitHandle(false, EventResetMode::AutoReset);//�����, ���������� �� �����
			
			this->Icon = gcnew  System::Drawing::Icon("icon2.ico");
			
		}

	public:
		
		bool getBitmap;
		EventWaitHandle ^ew;
		String^ str = gcnew String("");
		// ��������� "�����"
		ref struct Vert {
			int x;	// ������ �������
			int y;	// ������ �������
			int color = 0; // ����
		};
		// ��������� "�������"
		ref struct Vertex {
			int N; // �����
			int color; // ����
		};
		//������ ��� �������� �����
		cliext::vector<Vert^>^ rebra = gcnew cliext::vector<Vert^>();
		// ������ ��� �������� ������
		cliext::vector<Vertex^>^ vertex = gcnew cliext::vector<Vertex^>();
		cliext::vector<Vert^>^ rebraO = gcnew cliext::vector<Vert^>();
		cliext::vector<Vertex^>^ vertexO = gcnew cliext::vector<Vertex^>();
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  �������ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ����������ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ������ToolStripMenuItem;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::NumericUpDown^ numericUpDown2;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::ToolStripMenuItem^ �����ToolStripMenuItem;
	private: System::Windows::Forms::Button^ buttonPause;
	private: System::Windows::Forms::Timer^ timer1;
	public: cli::array<int>^ arr2;
	public:	void BFS() {
		str = "";
		button1->BeginInvoke(gcnew InvokeDelegateSetButtonState(this, &MyForm::InvertButton1State));
		button2->BeginInvoke(gcnew InvokeDelegateSetButtonState(this, &MyForm::InvertButton2State));
		// ����� ��� ���������� �����
		EventWaitHandle ^ewh = gcnew EventWaitHandle(false, EventResetMode::AutoReset);
		// ������������� �����
		std::queue<int> q;
		//������ ��������� �� ��������� ������� �� ���������
		std::vector<int>d(edges.size(), -1);
		//������ ���������� ������
		std::vector<int>mark(edges.size(), 0);
		// �������������: ���� ���������� ��� ��������� �������
		q.push(start);
		d[start] = 0;
		mark[start] = 1;
		str = Convert::ToString(numericUpDown2->Value);
		// ������� ���� - ���� ���� ����� �������
		while (!q.empty())
		{
			// ����� ������ �� ���
			int v = q.front();
			//�������� ������� ������
			vertex[v]->color = 1;
			// ������������ ��������� �������
			pictureBox1->BeginInvoke(gcnew InvokeDelegateRepaintGraph(this, &MyForm::repaint2), vertex->size(), rebra, vertex);
			Thread::Sleep(value*1000);
			q.pop();
			// ����������� �� ���� �� �������
			for (int i = 0; i < (int)edges[v].size(); ++i)
			{
				// ���� ����� �����
				if (mark[edges[v][i]] == 0)
				{
					// �� ��������� ����������
					d[edges[v][i]] = d[v] + 1;
					// � �� ���������� �����
					mark[edges[v][i]] = 1;
					// �������� ������� ������
					vertex[edges[v][i]]->color = 1;
					//������� ����� �� ��������� ������� �� ����� � �������� ��� ������
					for (int t = 0; t < rebra->size(); t++) {
						if ((rebra[t]->x == v && rebra[t]->y == edges[v][i]) || (rebra[t]->x == edges[v][i] && rebra[t]->y == v)) {
							rebra[t]->color = 1;
							str = str + " " + (edges[v][i] + 1);
						}
					}
					// �������������� ����
					pictureBox1->BeginInvoke(gcnew InvokeDelegateRepaintGraph(this, &MyForm::repaint2), vertex->size(), rebra, vertex);
					Thread::Sleep(500);
					//��������� ���������� ������� � �������
					q.push(edges[v][i]);
				}
			}
			if (Pause==true && Progress== false)
			{
				ew->WaitOne();
			}

		}
		// ������������� ������
		
		button2->BeginInvoke(gcnew InvokeDelegateSetButtonState(this, &MyForm::InvertButton2State));
		buttonPause->BeginInvoke(gcnew InvokeDelegateSetButtonState(this, &MyForm::disEnabled));
		MessageBox::Show("���������", "��������", MessageBoxButtons::OK);

	};
	delegate void InvokeDelegateRepaintGraph(int count, cliext::vector <Vert^>^ reb, cliext::vector <Vertex^>^ vertex);
	delegate void InvokeDelegateSetButtonState();
	private: Thread ^myThread;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
				
			}
		}
	private: System::Windows::Forms::GroupBox^  groupBox1;
	protected:
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Button^  button2;
		   
private: System::ComponentModel::IContainer^ components;

	//private: cli::array<int>^ arr;
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
			this->components = (gcnew System::ComponentModel::Container());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->numericUpDown3 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->buttonContinue = (gcnew System::Windows::Forms::Button());
			this->buttonPause = (gcnew System::Windows::Forms::Button());
			this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->�������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->����������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�����ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->button1);
			this->groupBox1->Controls->Add(this->numericUpDown3);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->numericUpDown1);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->groupBox1->Location = System::Drawing::Point(75, 27);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(665, 70);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"�������� ������";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(297, 34);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(131, 24);
			this->label4->TabIndex = 12;
			this->label4->Text = L"���-�� �����";
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(486, 28);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(173, 34);
			this->button1->TabIndex = 3;
			this->button1->Text = L"�������������";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// numericUpDown3
			// 
			this->numericUpDown3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->numericUpDown3->Location = System::Drawing::Point(434, 32);
			this->numericUpDown3->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown3->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown3->Name = L"numericUpDown3";
			this->numericUpDown3->Size = System::Drawing::Size(46, 29);
			this->numericUpDown3->TabIndex = 11;
			this->numericUpDown3->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(6, 34);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(191, 24);
			this->label1->TabIndex = 1;
			this->label1->Text = L"���������� ������";
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->numericUpDown1->Location = System::Drawing::Point(203, 31);
			this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 20, 0, 0, 0 });
			this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(66, 31);
			this->numericUpDown1->TabIndex = 0;
			this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &MyForm::numericUpDown1_ValueChanged);
			// 
			// groupBox2
			// 
			this->groupBox2->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->groupBox2->Controls->Add(this->label5);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->trackBar1);
			this->groupBox2->Controls->Add(this->buttonContinue);
			this->groupBox2->Controls->Add(this->buttonPause);
			this->groupBox2->Controls->Add(this->numericUpDown2);
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Controls->Add(this->pictureBox1);
			this->groupBox2->Controls->Add(this->button2);
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->groupBox2->Location = System::Drawing::Point(12, 103);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(734, 527);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"���������� BFS-������";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(6, 233);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(196, 24);
			this->label3->TabIndex = 4;
			this->label3->Text = L"�������� ���������";
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(10, 196);
			this->trackBar1->Minimum = 1;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(212, 45);
			this->trackBar1->TabIndex = 10;
			this->trackBar1->Value = 1;
			// 
			// buttonContinue
			// 
			this->buttonContinue->Enabled = false;
			this->buttonContinue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonContinue->Location = System::Drawing::Point(6, 120);
			this->buttonContinue->Name = L"buttonContinue";
			this->buttonContinue->Size = System::Drawing::Size(216, 32);
			this->buttonContinue->TabIndex = 9;
			this->buttonContinue->Text = L"����������";
			this->buttonContinue->UseVisualStyleBackColor = true;
			this->buttonContinue->Click += gcnew System::EventHandler(this, &MyForm::buttonContinue_Click);
			// 
			// buttonPause
			// 
			this->buttonPause->Enabled = false;
			this->buttonPause->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonPause->Location = System::Drawing::Point(6, 158);
			this->buttonPause->Name = L"buttonPause";
			this->buttonPause->Size = System::Drawing::Size(216, 32);
			this->buttonPause->TabIndex = 8;
			this->buttonPause->Text = L"�����";
			this->buttonPause->UseVisualStyleBackColor = true;
			this->buttonPause->Click += gcnew System::EventHandler(this, &MyForm::buttonPause_Click);
			// 
			// numericUpDown2
			// 
			this->numericUpDown2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->numericUpDown2->Location = System::Drawing::Point(47, 23);
			this->numericUpDown2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 20, 0, 0, 0 });
			this->numericUpDown2->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown2->Name = L"numericUpDown2";
			this->numericUpDown2->Size = System::Drawing::Size(46, 29);
			this->numericUpDown2->TabIndex = 7;
			this->numericUpDown2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown2->ValueChanged += gcnew System::EventHandler(this, &MyForm::numericUpDown2_ValueChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(6, 25);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(35, 24);
			this->label2->TabIndex = 6;
			this->label2->Text = L"��";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(228, 18);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(500, 500);
			this->pictureBox1->TabIndex = 5;
			this->pictureBox1->TabStop = false;
			// 
			// button2
			// 
			this->button2->Enabled = false;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(6, 82);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(87, 32);
			this->button2->TabIndex = 4;
			this->button2->Text = L"�����";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->�������ToolStripMenuItem,
					this->�����ToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(758, 24);
			this->menuStrip1->TabIndex = 3;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// �������ToolStripMenuItem
			// 
			this->�������ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->����������ToolStripMenuItem,
					this->������ToolStripMenuItem
			});
			this->�������ToolStripMenuItem->Name = L"�������ToolStripMenuItem";
			this->�������ToolStripMenuItem->Size = System::Drawing::Size(65, 20);
			this->�������ToolStripMenuItem->Text = L"�������";
			// 
			// ����������ToolStripMenuItem
			// 
			this->����������ToolStripMenuItem->Name = L"����������ToolStripMenuItem";
			this->����������ToolStripMenuItem->Size = System::Drawing::Size(149, 22);
			this->����������ToolStripMenuItem->Text = L"� ���������";
			this->����������ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::����������ToolStripMenuItem_Click);
			// 
			// ������ToolStripMenuItem
			// 
			this->������ToolStripMenuItem->Name = L"������ToolStripMenuItem";
			this->������ToolStripMenuItem->Size = System::Drawing::Size(149, 22);
			this->������ToolStripMenuItem->Text = L"������";
			this->������ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::������ToolStripMenuItem_Click);
			// 
			// �����ToolStripMenuItem
			// 
			this->�����ToolStripMenuItem->Name = L"�����ToolStripMenuItem";
			this->�����ToolStripMenuItem->Size = System::Drawing::Size(54, 20);
			this->�����ToolStripMenuItem->Text = L"�����";
			this->�����ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::�����ToolStripMenuItem_Click_1);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(6, 273);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(0, 24);
			this->label5->TabIndex = 11;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(758, 633);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"��������� ���������� ����� � ����� ������ BFS";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		// ������� ����� ��������� ������1
	private: void InvertButton1State() {
		button1->Enabled = !button1->Enabled;
	}
	public: void getBitmapOrig(Bitmap ^img) {
		Bitmap^ orig = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
		orig = img;
		   }


		   // ������� ����� ��������� ������2
	private: void InvertButton2State() {
		button2->Enabled = !button2->Enabled;
	}

		   //���������� ������� ����� � ����������
	private: void disEnabled(){
		buttonPause->Enabled = false;
		buttonContinue->Enabled = false;
		label5->Text = str;
	}
		   //�������� �������� �������� ��������� �������
	public: int getTBValue(int val) {
		return val = trackBar1->Value * 1000;
	}
		   //������� ����������� �����
	private: void repaint2(int count, cliext::vector <Vert^>^ reb, cliext::vector <Vertex^>^ vertex)
	{
		// ���������� ������ � ������ ������� ���������� �����
		int pW = pictureBox1->Width, pH = pictureBox1->Height;
		// ������� ������ Bitmap
		Bitmap^ img = gcnew Bitmap(pW, pH);
		Graphics^ g = Graphics::FromImage(img);

		//������� ��������
		int mX = int(pW / 2);
		int mY = int(pH / 2);

		g->ScaleTransform(1, -1); //�������������� ��� Y ��� �������� ����������
		g->TranslateTransform((float)mX, -(float)mY); //������� ������� ���������� �� ����������� ����
		int n = count; // ���������� ������

		// ������ �������
		int R = pH / 2 - 30;
		// ��������� ����
		double alfa = 0;
		// ������� ������
		SolidBrush^ drawBrush = gcnew SolidBrush(Color::White);
		//��� ����� ��� ���������
		Pen^ pen = gcnew Pen(Color::Black, 1);
		// � ����� ��������� ���������� ������� ������
		cli::array<Vert^>^ v = gcnew cli::array<Vert^>(n);
		for (int i = 0; i < n; i++)
		{
			// ��������� ����� ��������� �������
			double x = R * Math::Sin(alfa);
			double y = R * Math::Cos(alfa);
			alfa += 2 * 3.14 / n;
			// ��������� � ������� ������
			v[i] = gcnew Vert;
			v[i]->x = x;
			v[i]->y = y;
		}
		// � ����� ������������ �����
		for (int i = 0; i < reb->size(); i++)
		{
			// ���� ����� �� ���� �������� ������, ������ ��� ������ ������ ������
			if (reb->at(i)->color == 0) {
				pen->Color = Color::Black;
				pen->Width = 1;
			}
			// ���� ����� ���� �������� ������, ������ ��� ������� ������� ������
			else {
				pen->Color = Color::Red;
				pen->Width = 2;
			}
			// ������ �����
			g->DrawLine(pen, v[reb->at(i)->x]->x, v[reb->at(i)->x]->y, v[reb->at(i)->y]->x, v[reb->at(i)->y]->y);
		}

		// � ����� ������ �������
		for (int i = 0; i < n; i++)
		{
			// ���� ������� �������� ������ - ������ � �����
			drawBrush->Color = vertex[i]->color == 0 ? Color::White : Color::Gray;
			g->FillEllipse(drawBrush, RectangleF(v[i]->x - 20, v[i]->y - 20, 40, 40));
			g->DrawEllipse(Pens::Green, RectangleF(v[i]->x - 20, v[i]->y - 20, 40, 40));
		}
		alfa = 0;
		SolidBrush^ drawBrush1 = gcnew SolidBrush(Color::Black);
		// ������ ������ ������� ������ �������
		System::Drawing::Font^ font = gcnew System::Drawing::Font("Tahoma", 8, FontStyle::Bold);
		g->ScaleTransform(1, -1); //�������������� ��� Y ��� �������� ����������
		for (int i = 0; i < n; i++)
		{// ���������� ���������� �������
			double x = R * Math::Sin(alfa);
			double y = (R - R * Math::Cos(alfa)) - R;
			alfa += 2 * 3.14 / n;
			// ������� ������� ������ �������
			g->DrawString("A" + (i + 1), font, drawBrush1, x - 10, y - 10);
		}

		delete g; //������������ �������� ���������� ���������
		this->pictureBox1->Image = img;
		if (getBitmap)
		{
			vertexO = vertex;
			rebraO = rebra;
		}
	}

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	// ���� ���������� ������ ����� < 2, �� �������
	getBitmap = true;
	int	count = System::Convert::ToInt32(numericUpDown1->Value);
	if (count < 2) return;

	//������ ��� �������� ������� ��������� �����
	cli::array<cli::array<int>^>^ matr = gcnew cli::array <cli::array<int>^>(count);
	for (int i = 0; i < count; i++)
	{
		matr[i] = gcnew cli::array<int>(count);
	}
	// �������� ������� ��������� ������� ��������� �����
	Random generator;
	int value;
	int threshold = System::Convert::ToInt32(numericUpDown3->Value);
	for (int i = 0; i < count; i++)
		{
			if (threshold != 0) {//���� �������� ����� �� ���������
				for (int j = i; j < count; j++)
				{
					if (i != j) {
						if (threshold != 0) {
							value = generator.Next() % 2;
							matr[i][j] = value;
							matr[j][i] = matr[i][j];
							if (value == 1)
								threshold--;
						}
						else
						{
							matr[i][j] = 0;
							matr[j][i] = matr[i][j];
						}
					}

				}

			}
			else//���� �������� ����� ���������
			{
				for (int j = i; j < count; j++)
					if (i != j) {
						matr[i][j] = 0;
						matr[j][i] = matr[i][j];
					}
			}
			if (threshold != 0)//���� ������ ���-�� ����� �� ���� ����������
			{
				for (int j = i; j < count; j++)
				{
					if(threshold!=0)
						if (i != j) 
							if (matr[i][j] != 1)
							{
								matr[i][j] = 1;
								matr[j][i] = matr[i][j];
								threshold--;
							}
						
				}
			}
		}
	// ������� ������ �����
	rebra->clear();
	// �� ����� ��������� ������ �����
	for (int i = 0; i < count; i++)
		for (int j = i; j < count; j++) 
		if(matr[i][j]!=0)
		{// ���� ����� ��������� ���� �����, ������� �����
			Vert^ a = gcnew Vert;
			a->x = i;
			a->y = j;
			a->color = 0;
			rebra->push_back(a);
		}
	//������� ������ ������
	vertex->clear();
	// � ����� ��������� ������ ������ � ������ �����������
	for (int i = 0; i < count; ++i)
	{
		Vertex^ a = gcnew Vertex;
		a->N = i;
		a->color = 0;
		vertex->push_back(a);
	}
	// �������������� ����
	repaint2(count, rebra, vertex);
	edges.clear();
	edges.resize(count);
	// � ����� ��������� ������� ��������� � "������ �������", ����� ���� ������ ��������� �������� BFS
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
		{
			if (matr[i][j] > 0) {
				edges[i].push_back(j);
			}
		}
	}
	button2->Enabled = true;
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	getBitmap = true;
	if (numericUpDown2->Value > numericUpDown1->Value)
		MessageBox::Show("��� ����� ������� � �����!");
	else
	{
		start = Convert::ToInt32(numericUpDown2->Value) - 1;
		// ���������, ���� �� ����� � ��� ��������� �������
		if (edges[start].size() == 0) {
			MessageBox::Show("�� ��������� ������� ��� �����!", "������!");
		}
		else {
			// ��������� ����� ���������� BFS-������
			repaint2(System::Convert::ToInt32(numericUpDown1->Value), rebraO, vertexO);
			button1->Enabled = false;
			myThread = gcnew Thread(gcnew ThreadStart(this, &MyForm::BFS));
			button1->Enabled = false;
			buttonPause->Enabled  = true;
			value = trackBar1->Value;
			myThread->Start();
		}
	}
}

private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {

}
private: System::Void ����������ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	// �������� ���� - �� ���������
	MessageBox::Show("���������: ���������� ���������� ����� � ���������� ������ BFS\n������: v1.0\n���: 2023\n������������: ��������, ������, �����, �����");
}
private: System::Void ������ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	// �������� ���� - ������
	MessageBox::Show("� ������ ���� ����� ����������� ����� ������ � ���������� �����, �� ������ ���� ����������� ����� �������, � ������� ����� �������� ������ BFS");
}
private: System::Void �����ToolStripMenuItem_Click_1(System::Object^ sender, System::EventArgs^ e) {
	if (MessageBox::Show("�� ������������� ������ �����?",
		"����� �� ���������", MessageBoxButtons::YesNo,
		MessageBoxIcon::Question, MessageBoxDefaultButton::Button1) == System::Windows::Forms::DialogResult::Yes)
		Application::Exit();
}
private: System::Void buttonPause_Click(System::Object^ sender, System::EventArgs^ e) {
	buttonContinue->Enabled = true;
	buttonPause->Enabled = false;
	Pause = true;
	Progress = false;
}
private: System::Void buttonContinue_Click(System::Object^ sender, System::EventArgs^ e) {
	buttonContinue->Enabled = false;
	buttonPause->Enabled = true;
	Pause = false;
	Progress = true;
	ew->Set();
}
private: System::Void numericUpDown2_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void numericUpDown1_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	int max = System::Convert::ToInt32(numericUpDown1->Value);
	numericUpDown3->Maximum = (max * (max - 1) / 2);
}
};
}
