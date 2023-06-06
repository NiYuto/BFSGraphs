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

	// массив для хранения матрицы смежности графа
	std::vector<std::vector<int>> edges;
	
	int value;
	//стартовая вершина для построения
	int start{ 0 };
	
	public ref class MyForm : public System::Windows::Forms::Form
	{
	
	
	public:

		
		bool Progress, Pause;//состояние программы
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
			ew = gcnew EventWaitHandle(false, EventResetMode::AutoReset);//ивент, отвечающий за паузу
			
			this->Icon = gcnew  System::Drawing::Icon("icon2.ico");
			
		}

	public:
		
		bool getBitmap;
		EventWaitHandle ^ew;
		String^ str = gcnew String("");
		// структура "Ребро"
		ref struct Vert {
			int x;	// первая вершина
			int y;	// вторая вершина
			int color = 0; // цвет
		};
		// структура "Вершина"
		ref struct Vertex {
			int N; // номер
			int color; // цвет
		};
		//массив для хранения ребер
		cliext::vector<Vert^>^ rebra = gcnew cliext::vector<Vert^>();
		// массив для хранения вершин
		cliext::vector<Vertex^>^ vertex = gcnew cliext::vector<Vertex^>();
		cliext::vector<Vert^>^ rebraO = gcnew cliext::vector<Vert^>();
		cliext::vector<Vertex^>^ vertexO = gcnew cliext::vector<Vertex^>();
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  справкаToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  оПрограммеToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  помощьToolStripMenuItem;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::NumericUpDown^ numericUpDown2;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::ToolStripMenuItem^ выходToolStripMenuItem;
	private: System::Windows::Forms::Button^ buttonPause;
	private: System::Windows::Forms::Timer^ timer1;
	public: cli::array<int>^ arr2;
	public:	void BFS() {
		str = "";
		button1->BeginInvoke(gcnew InvokeDelegateSetButtonState(this, &MyForm::InvertButton1State));
		button2->BeginInvoke(gcnew InvokeDelegateSetButtonState(this, &MyForm::InvertButton2State));
		// ивент для реализации паузы
		EventWaitHandle ^ewh = gcnew EventWaitHandle(false, EventResetMode::AutoReset);
		// промежуточный буфер
		std::queue<int> q;
		//массив растояний от стартовой вершины до остальных
		std::vector<int>d(edges.size(), -1);
		//массив помеченных вершин
		std::vector<int>mark(edges.size(), 0);
		// Инициализация: есть информация про начальную вершину
		q.push(start);
		d[start] = 0;
		mark[start] = 1;
		str = Convert::ToString(numericUpDown2->Value);
		// Главный цикл - пока есть серые вершины
		while (!q.empty())
		{
			// Берем первую из них
			int v = q.front();
			//помечаем вершину цветом
			vertex[v]->color = 1;
			// отрисовываем выделение вершины
			pictureBox1->BeginInvoke(gcnew InvokeDelegateRepaintGraph(this, &MyForm::repaint2), vertex->size(), rebra, vertex);
			Thread::Sleep(value*1000);
			q.pop();
			// Пробегаемся по всем ее соседям
			for (int i = 0; i < (int)edges[v].size(); ++i)
			{
				// Если сосед белый
				if (mark[edges[v][i]] == 0)
				{
					// То вычисляем расстояние
					d[edges[v][i]] = d[v] + 1;
					// И он становится серым
					mark[edges[v][i]] = 1;
					// помечаем вершину цветом
					vertex[edges[v][i]]->color = 1;
					//находим ребро от начальной вершины до новой и помечаем его цветом
					for (int t = 0; t < rebra->size(); t++) {
						if ((rebra[t]->x == v && rebra[t]->y == edges[v][i]) || (rebra[t]->x == edges[v][i] && rebra[t]->y == v)) {
							rebra[t]->color = 1;
							str = str + " " + (edges[v][i] + 1);
						}
					}
					// перерисовываем граф
					pictureBox1->BeginInvoke(gcnew InvokeDelegateRepaintGraph(this, &MyForm::repaint2), vertex->size(), rebra, vertex);
					Thread::Sleep(500);
					//добавляем помеченную вершину в очередь
					q.push(edges[v][i]);
				}
			}
			if (Pause==true && Progress== false)
			{
				ew->WaitOne();
			}

		}
		// разблокировка кнопок
		
		button2->BeginInvoke(gcnew InvokeDelegateSetButtonState(this, &MyForm::InvertButton2State));
		buttonPause->BeginInvoke(gcnew InvokeDelegateSetButtonState(this, &MyForm::disEnabled));
		MessageBox::Show("Завершено", "Внимание", MessageBoxButtons::OK);

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
			this->справкаToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->оПрограммеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->помощьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->выходToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
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
			this->groupBox1->Text = L"Исходные данные";
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
			this->label4->Text = L"Кол-во ребер";
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(486, 28);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(173, 34);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Сгенерировать";
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
			this->label1->Text = L"Количество вершин";
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
			this->groupBox2->Text = L"Построение BFS-дерева";
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
			this->label3->Text = L"Скорость отрисовки";
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
			this->buttonContinue->Text = L"Продолжить";
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
			this->buttonPause->Text = L"Пауза";
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
			this->label2->Text = L"От";
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
			this->button2->Text = L"Старт";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->справкаToolStripMenuItem,
					this->выходToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(758, 24);
			this->menuStrip1->TabIndex = 3;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// справкаToolStripMenuItem
			// 
			this->справкаToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->оПрограммеToolStripMenuItem,
					this->помощьToolStripMenuItem
			});
			this->справкаToolStripMenuItem->Name = L"справкаToolStripMenuItem";
			this->справкаToolStripMenuItem->Size = System::Drawing::Size(65, 20);
			this->справкаToolStripMenuItem->Text = L"Справка";
			// 
			// оПрограммеToolStripMenuItem
			// 
			this->оПрограммеToolStripMenuItem->Name = L"оПрограммеToolStripMenuItem";
			this->оПрограммеToolStripMenuItem->Size = System::Drawing::Size(149, 22);
			this->оПрограммеToolStripMenuItem->Text = L"О программе";
			this->оПрограммеToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::оПрограммеToolStripMenuItem_Click);
			// 
			// помощьToolStripMenuItem
			// 
			this->помощьToolStripMenuItem->Name = L"помощьToolStripMenuItem";
			this->помощьToolStripMenuItem->Size = System::Drawing::Size(149, 22);
			this->помощьToolStripMenuItem->Text = L"Помощь";
			this->помощьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::помощьToolStripMenuItem_Click);
			// 
			// выходToolStripMenuItem
			// 
			this->выходToolStripMenuItem->Name = L"выходToolStripMenuItem";
			this->выходToolStripMenuItem->Size = System::Drawing::Size(54, 20);
			this->выходToolStripMenuItem->Text = L"Выход";
			this->выходToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::выходToolStripMenuItem_Click_1);
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
			this->Text = L"Генерация случайного графа и поиск дерева BFS";
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
		// функция смены состояния кнопки1
	private: void InvertButton1State() {
		button1->Enabled = !button1->Enabled;
	}
	public: void getBitmapOrig(Bitmap ^img) {
		Bitmap^ orig = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
		orig = img;
		   }


		   // функция смены состояния кнопки2
	private: void InvertButton2State() {
		button2->Enabled = !button2->Enabled;
	}

		   //отключение кнопоко паузы и продолжить
	private: void disEnabled(){
		buttonPause->Enabled = false;
		buttonContinue->Enabled = false;
		label5->Text = str;
	}
		   //получить значение скорости отрисовки графика
	public: int getTBValue(int val) {
		return val = trackBar1->Value * 1000;
	}
		   //функция перерисовки графа
	private: void repaint2(int count, cliext::vector <Vert^>^ reb, cliext::vector <Vertex^>^ vertex)
	{
		// определяем высоту и ширину области построения графа
		int pW = pictureBox1->Width, pH = pictureBox1->Height;
		// создаем объект Bitmap
		Bitmap^ img = gcnew Bitmap(pW, pH);
		Graphics^ g = Graphics::FromImage(img);

		//находим середину
		int mX = int(pW / 2);
		int mY = int(pH / 2);

		g->ScaleTransform(1, -1); //переворачиваем ось Y для удобства восприятия
		g->TranslateTransform((float)mX, -(float)mY); //смещаем нулевую координату на пересечение осей
		int n = count; // количество вершин

		// радиус вершины
		int R = pH / 2 - 30;
		// начальный угол
		double alfa = 0;
		// заливка вершин
		SolidBrush^ drawBrush = gcnew SolidBrush(Color::White);
		//тип линии для рисования
		Pen^ pen = gcnew Pen(Color::Black, 1);
		// в цикле заполняем координаты центров вершин
		cli::array<Vert^>^ v = gcnew cli::array<Vert^>(n);
		for (int i = 0; i < n; i++)
		{
			// вычисляем центр очередной вершины
			double x = R * Math::Sin(alfa);
			double y = R * Math::Cos(alfa);
			alfa += 2 * 3.14 / n;
			// сохраняем в массиве вершин
			v[i] = gcnew Vert;
			v[i]->x = x;
			v[i]->y = y;
		}
		// в цикле отрисовываем ребра
		for (int i = 0; i < reb->size(); i++)
		{
			// если ребро не было помечено цветом, рисуем его черной тонкой линией
			if (reb->at(i)->color == 0) {
				pen->Color = Color::Black;
				pen->Width = 1;
			}
			// если ребро было помечено цветом, рисуем его зеленой толстой линией
			else {
				pen->Color = Color::Red;
				pen->Width = 2;
			}
			// рисуем линию
			g->DrawLine(pen, v[reb->at(i)->x]->x, v[reb->at(i)->x]->y, v[reb->at(i)->y]->x, v[reb->at(i)->y]->y);
		}

		// в цикле рисуем вершины
		for (int i = 0; i < n; i++)
		{
			// если вершина помечена цветом - рисуем её серой
			drawBrush->Color = vertex[i]->color == 0 ? Color::White : Color::Gray;
			g->FillEllipse(drawBrush, RectangleF(v[i]->x - 20, v[i]->y - 20, 40, 40));
			g->DrawEllipse(Pens::Green, RectangleF(v[i]->x - 20, v[i]->y - 20, 40, 40));
		}
		alfa = 0;
		SolidBrush^ drawBrush1 = gcnew SolidBrush(Color::Black);
		// задаем мшрифт надписи внутри вершины
		System::Drawing::Font^ font = gcnew System::Drawing::Font("Tahoma", 8, FontStyle::Bold);
		g->ScaleTransform(1, -1); //переворачиваем ось Y для удобства восприятия
		for (int i = 0; i < n; i++)
		{// определяем координаты вершины
			double x = R * Math::Sin(alfa);
			double y = (R - R * Math::Cos(alfa)) - R;
			alfa += 2 * 3.14 / n;
			// выводим надпись внутри вершины
			g->DrawString("A" + (i + 1), font, drawBrush1, x - 10, y - 10);
		}

		delete g; //освобождение ресурсов устройства рисования
		this->pictureBox1->Image = img;
		if (getBitmap)
		{
			vertexO = vertex;
			rebraO = rebra;
		}
	}

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	// если количество вершин графа < 2, то выходим
	getBitmap = true;
	int	count = System::Convert::ToInt32(numericUpDown1->Value);
	if (count < 2) return;

	//массив для хранения матрицы смежности графа
	cli::array<cli::array<int>^>^ matr = gcnew cli::array <cli::array<int>^>(count);
	for (int i = 0; i < count; i++)
	{
		matr[i] = gcnew cli::array<int>(count);
	}
	// случаным образом формируем матрицу смежности графа
	Random generator;
	int value;
	int threshold = System::Convert::ToInt32(numericUpDown3->Value);
	for (int i = 0; i < count; i++)
		{
			if (threshold != 0) {//если максимум ребер не достигнут
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
			else//если максимум ребер достигнут
			{
				for (int j = i; j < count; j++)
					if (i != j) {
						matr[i][j] = 0;
						matr[j][i] = matr[i][j];
					}
			}
			if (threshold != 0)//если нужное кол-во ребер не было достигнуто
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
	// очищаем массив ребер
	rebra->clear();
	// вы цикле заполняем массив ребер
	for (int i = 0; i < count; i++)
		for (int j = i; j < count; j++) 
		if(matr[i][j]!=0)
		{// если между вершинами есть связь, создаем ребро
			Vert^ a = gcnew Vert;
			a->x = i;
			a->y = j;
			a->color = 0;
			rebra->push_back(a);
		}
	//осищаем массив вершин
	vertex->clear();
	// в цикле заполняем массив вершин с цветом поумолчанию
	for (int i = 0; i < count; ++i)
	{
		Vertex^ a = gcnew Vertex;
		a->N = i;
		a->color = 0;
		vertex->push_back(a);
	}
	// перерисовываем граф
	repaint2(count, rebra, vertex);
	edges.clear();
	edges.resize(count);
	// в цикле заполняем матрицу смежности в "ужатом формате", чтобы было удобно применить алгоритм BFS
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
		MessageBox::Show("Нет такой вершины в графе!");
	else
	{
		start = Convert::ToInt32(numericUpDown2->Value) - 1;
		// проверяем, есть ли ребра в для выбранной вершины
		if (edges[start].size() == 0) {
			MessageBox::Show("Из выбранной вершины нет ребер!", "Ошибка!");
		}
		else {
			// запускаем поток нахождения BFS-дерева
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
private: System::Void оПрограммеToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	// открытие окна - по программе
	MessageBox::Show("Программа: построение случайного графа и построение дерева BFS\nВерсия: v1.0\nГод: 2023\nРазработчики: Лопаткин, Синцов, Юрлов, Юрьев");
}
private: System::Void помощьToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	// открытие окна - помощь
	MessageBox::Show("В первом поле ввода указывается число вершин в генерируем графе, во втором поле указывается номер вершины, с которой будет искаться дерево BFS");
}
private: System::Void выходToolStripMenuItem_Click_1(System::Object^ sender, System::EventArgs^ e) {
	if (MessageBox::Show("Вы действительно хотите выйти?",
		"Выход из програииы", MessageBoxButtons::YesNo,
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
