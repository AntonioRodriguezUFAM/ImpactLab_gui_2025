#pragma once


#include <thread> // Inclua esta linha para usar std::thread
#include <algorithm> // Inclua esta linha para usar std::min

namespace pavicgui2024 {
//#include "include/Diagnostic.h"





	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Imaging; // <-- Adicione esta linha para BitmapData, ImageLockMode, PixelFormat

	using namespace std; // Assuming Diagnostics is in the std namespace

	//================================================================================
	// // --- Início da função auxiliar para aplicar o filtro sépia parcialmente ---
	//// Esta função será executada pelas threads.
	//// Ela precisa ser definida fora da classe do formulário para ser usada com std::thread de forma mais simples.
	void ApplySepiaFilterPartial(Bitmap^ inputImage, Bitmap^ outputImage, int startY, int endY) {
		for (int i = 0; i < inputImage->Width; i++) {
			for (int j = startY; j < endY; j++) {
				// Passo 1: Obter a cor do pixel atual
				Color pixelColor = inputImage->GetPixel(i, j);

				// Passo 2: Extrair os valores originais de Vermelho, Verde e Azul
				int r = pixelColor.R;
				int g = pixelColor.G;
				int b = pixelColor.B;

				// Passo 3: Calcular os novos valores de pixel usando a Fórmula Sépia
				double tr = 0.393 * r + 0.769 * g + 0.189 * b;
				double tg = 0.349 * r + 0.686 * g + 0.168 * b;
				double tb = 0.272 * r + 0.534 * g + 0.131 * b;

				// Passo 4: Limitar os valores ao intervalo 0-255
				int newR = Math::Min(255, (int)tr);
				int newG = Math::Min(255, (int)tg);
				int newB = Math::Min(255, (int)tb);

				outputImage->SetPixel(i, j, Color::FromArgb(newR, newG, newB));
			}
		}
	}
	// --- Fim da função auxiliar ---
	// 
	// ==================================================================================
	//================================================================================
	// // --- Início da função auxiliar para aplicar o filtro sépia parcialmente ---
	//// Esta função será executada pelas threads.
	//// Ela precisa ser definida fora da classe do formulário para ser usada com std::thread de forma mais simples.
	void ApplySepiaFilterWindow(Bitmap^ inputImage, Bitmap^ outputImage, int startX, int endX, int startY, int endY) {
		for (int i = startX; i < endX; i++) {
			for (int j = startY; j < endY; j++) {
				// Passo 1: Obter a cor do pixel atual
				Color pixelColor = inputImage->GetPixel(i, j);

				// Passo 2: Extrair os valores originais de Vermelho, Verde e Azul
				int r = pixelColor.R;
				int g = pixelColor.G;
				int b = pixelColor.B;

				// Passo 3: Calcular os novos valores de pixel usando a Fórmula Sépia
				double tr = 0.393 * r + 0.769 * g + 0.189 * b;
				double tg = 0.349 * r + 0.686 * g + 0.168 * b;
				double tb = 0.272 * r + 0.534 * g + 0.131 * b;

				// Passo 4: Limitar os valores ao intervalo 0-255
				int newR = Math::Min(255, (int)tr);
				int newG = Math::Min(255, (int)tg);
				int newB = Math::Min(255, (int)tb);

				outputImage->SetPixel(i, j, Color::FromArgb(newR, newG, newB));
			}
		}
	}
	// --- Fim da função auxiliar ---
	// 
	// 
	//================================================================================
	//================================================================================
	// --- Início da função auxiliar para aplicar o filtro sépia parcialmente ---
	// Esta função será executada pelas threads e operará em dados brutos.
	// Ela precisa ser definida fora da classe do formulário.
	void ApplySepiaFilterPartialRaw(IntPtr inputScan0, int inputStride, IntPtr outputScan0, int outputStride, int width, int bytesPerPixel, int startY, int endY) {
		// Converter IntPtr para ponteiros de bytes não gerenciados
		unsigned char* ptrInput = (unsigned char*)inputScan0.ToPointer();
		unsigned char* ptrOutput = (unsigned char*)outputScan0.ToPointer();

		for (int j = startY; j < endY; j++) {
			for (int i = 0; i < width; i++) {
				// Calcular o offset para o pixel atual na linha
				long offsetInput = (long)j * inputStride + (long)i * bytesPerPixel;
				long offsetOutput = (long)j * outputStride + (long)i * bytesPerPixel;

				// Obter os valores de cor (assumindo formato BGR ou BGRA)
				int b = ptrInput[offsetInput];
				int g = ptrInput[offsetInput + 1];
				int r = ptrInput[offsetInput + 2];
				// Se for 32bpp (BGRA), o quarto byte é o canal alfa.
				// int a = (bytesPerPixel == 4) ? ptrInput[offsetInput + 3] : 255; // Linha comentada por enquanto, se precisar de alfa, descomente e ajuste

				// Aplicar a fórmula Sépia
				double tr = 0.393 * r + 0.769 * g + 0.189 * b;
				double tg = 0.349 * r + 0.686 * g + 0.168 * b;
				double tb = 0.272 * r + 0.534 * g + 0.131 * b;

				// Limitar os valores ao intervalo 0-255
				int newR = Math::Min(255, (int)tr);
				int newG = Math::Min(255, (int)tg);
				int newB = Math::Min(255, (int)tb);

				// Definir os novos valores de pixel na imagem de saída
				ptrOutput[offsetOutput] = (unsigned char)newB;
				ptrOutput[offsetOutput + 1] = (unsigned char)newG;
				ptrOutput[offsetOutput + 2] = (unsigned char)newR;
				// Se for 32bpp (BGRA), manter o canal alfa original ou definir como 255
				// if (bytesPerPixel == 4) ptrOutput[offsetOutput + 3] = (unsigned char)a; // Linha comentada por enquanto, se precisar de alfa, descomente e ajuste
			}
		}
	}
	// --- Fim da função auxiliar ---
	//==============================================================


	/// <summary>
	/// Summary for Pavic_gui_2024_Form
	/// </summary>
	public ref class Pavic_gui_2024_Form : public System::Windows::Forms::Form
	{
	public:
		Pavic_gui_2024_Form(void)
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
		~Pavic_gui_2024_Form()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ bt_open;
	protected:
	private: System::Windows::Forms::Button^ bt_close;
	private: System::Windows::Forms::Button^ bt_exit;
	private: System::Windows::Forms::PictureBox^ pbox_input;
	private: System::Windows::Forms::PictureBox^ pbox_copy;
	private: System::Windows::Forms::PictureBox^ pbox_output;
	private: System::Windows::Forms::Button^ bt_copy;
	private: System::Windows::Forms::Button^ bt_filter_bw;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ bt_close_copy;
	private: System::Windows::Forms::Button^ bt_close_output;

	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ label12;
	private: System::Diagnostics::Stopwatch^ copyStopwatch;
	private: System::Diagnostics::Stopwatch^ filterStopwatch;
	private: System::Windows::Forms::Button^ bt_filter_Sepia;
	private: System::Windows::Forms::Button^ bt_filter_Sepia_MultiThread;
	private: System::Windows::Forms::Button^ bt_filter_Sepia_top;
	private: System::Windows::Forms::Button^ bt_filter_Sepia_botton;


	private: System::Windows::Forms::Label^ lb_timer;
	private: System::Windows::Forms::TextBox^ textB_Time;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ bt_filter_Sepia_left;
	private: System::Windows::Forms::Button^ bt_filter_Sepia_Thread;





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
			this->bt_open = (gcnew System::Windows::Forms::Button());
			this->bt_close = (gcnew System::Windows::Forms::Button());
			this->bt_exit = (gcnew System::Windows::Forms::Button());
			this->pbox_input = (gcnew System::Windows::Forms::PictureBox());
			this->pbox_copy = (gcnew System::Windows::Forms::PictureBox());
			this->pbox_output = (gcnew System::Windows::Forms::PictureBox());
			this->bt_copy = (gcnew System::Windows::Forms::Button());
			this->bt_filter_bw = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->bt_close_copy = (gcnew System::Windows::Forms::Button());
			this->bt_close_output = (gcnew System::Windows::Forms::Button());
			this->bt_filter_Sepia = (gcnew System::Windows::Forms::Button());
			this->bt_filter_Sepia_MultiThread = (gcnew System::Windows::Forms::Button());
			this->bt_filter_Sepia_top = (gcnew System::Windows::Forms::Button());
			this->bt_filter_Sepia_botton = (gcnew System::Windows::Forms::Button());
			this->lb_timer = (gcnew System::Windows::Forms::Label());
			this->textB_Time = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->bt_filter_Sepia_left = (gcnew System::Windows::Forms::Button());
			this->bt_filter_Sepia_Thread = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbox_input))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbox_copy))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbox_output))->BeginInit();
			this->SuspendLayout();
			// 
			// bt_open
			// 
			this->bt_open->Location = System::Drawing::Point(9, 10);
			this->bt_open->Margin = System::Windows::Forms::Padding(2);
			this->bt_open->Name = L"bt_open";
			this->bt_open->Size = System::Drawing::Size(142, 37);
			this->bt_open->TabIndex = 0;
			this->bt_open->Text = L"Open";
			this->bt_open->UseVisualStyleBackColor = true;
			this->bt_open->Click += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::bt_open_Click);
			// 
			// bt_close
			// 
			this->bt_close->Location = System::Drawing::Point(291, 192);
			this->bt_close->Margin = System::Windows::Forms::Padding(2);
			this->bt_close->Name = L"bt_close";
			this->bt_close->Size = System::Drawing::Size(95, 28);
			this->bt_close->TabIndex = 1;
			this->bt_close->Text = L"Close";
			this->bt_close->UseVisualStyleBackColor = true;
			this->bt_close->Click += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::bt_close_Click);
			// 
			// bt_exit
			// 
			this->bt_exit->Location = System::Drawing::Point(9, 93);
			this->bt_exit->Margin = System::Windows::Forms::Padding(2);
			this->bt_exit->Name = L"bt_exit";
			this->bt_exit->Size = System::Drawing::Size(142, 37);
			this->bt_exit->TabIndex = 2;
			this->bt_exit->Text = L"Exit";
			this->bt_exit->UseVisualStyleBackColor = true;
			this->bt_exit->Click += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::bt_exit_Click);
			// 
			// pbox_input
			// 
			this->pbox_input->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->pbox_input->Location = System::Drawing::Point(13, 225);
			this->pbox_input->Margin = System::Windows::Forms::Padding(2);
			this->pbox_input->Name = L"pbox_input";
			this->pbox_input->Size = System::Drawing::Size(374, 331);
			this->pbox_input->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pbox_input->TabIndex = 3;
			this->pbox_input->TabStop = false;
			this->pbox_input->Click += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::pbox_input_Click);
			// 
			// pbox_copy
			// 
			this->pbox_copy->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->pbox_copy->Location = System::Drawing::Point(416, 225);
			this->pbox_copy->Margin = System::Windows::Forms::Padding(2);
			this->pbox_copy->Name = L"pbox_copy";
			this->pbox_copy->Size = System::Drawing::Size(374, 331);
			this->pbox_copy->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pbox_copy->TabIndex = 4;
			this->pbox_copy->TabStop = false;
			// 
			// pbox_output
			// 
			this->pbox_output->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->pbox_output->Location = System::Drawing::Point(815, 225);
			this->pbox_output->Margin = System::Windows::Forms::Padding(2);
			this->pbox_output->Name = L"pbox_output";
			this->pbox_output->Size = System::Drawing::Size(374, 331);
			this->pbox_output->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pbox_output->TabIndex = 5;
			this->pbox_output->TabStop = false;
			// 
			// bt_copy
			// 
			this->bt_copy->Location = System::Drawing::Point(9, 51);
			this->bt_copy->Margin = System::Windows::Forms::Padding(2);
			this->bt_copy->Name = L"bt_copy";
			this->bt_copy->Size = System::Drawing::Size(142, 37);
			this->bt_copy->TabIndex = 6;
			this->bt_copy->Text = L"Copy";
			this->bt_copy->UseVisualStyleBackColor = true;
			this->bt_copy->Click += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::bt_copy_Click);
			// 
			// bt_filter_bw
			// 
			this->bt_filter_bw->Location = System::Drawing::Point(216, 11);
			this->bt_filter_bw->Margin = System::Windows::Forms::Padding(2);
			this->bt_filter_bw->Name = L"bt_filter_bw";
			this->bt_filter_bw->Size = System::Drawing::Size(142, 37);
			this->bt_filter_bw->TabIndex = 7;
			this->bt_filter_bw->Text = L"Filter BW";
			this->bt_filter_bw->UseVisualStyleBackColor = true;
			this->bt_filter_bw->Click += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::bt_filter_bw_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(1078, 576);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(128, 13);
			this->label1->TabIndex = 8;
			this->label1->Text = L" Antonio Souto Rodriguez";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(7, 576);
			this->label2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(94, 13);
			this->label2->TabIndex = 9;
			this->label2->Text = L" PAVIC LAB: 2024";
			// 
			// bt_close_copy
			// 
			this->bt_close_copy->Location = System::Drawing::Point(694, 192);
			this->bt_close_copy->Margin = System::Windows::Forms::Padding(2);
			this->bt_close_copy->Name = L"bt_close_copy";
			this->bt_close_copy->Size = System::Drawing::Size(95, 28);
			this->bt_close_copy->TabIndex = 10;
			this->bt_close_copy->Text = L"Close";
			this->bt_close_copy->UseVisualStyleBackColor = true;
			this->bt_close_copy->Click += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::bt_close_copy_Click);
			// 
			// bt_close_output
			// 
			this->bt_close_output->Location = System::Drawing::Point(1094, 192);
			this->bt_close_output->Margin = System::Windows::Forms::Padding(2);
			this->bt_close_output->Name = L"bt_close_output";
			this->bt_close_output->Size = System::Drawing::Size(95, 28);
			this->bt_close_output->TabIndex = 11;
			this->bt_close_output->Text = L"Close";
			this->bt_close_output->UseVisualStyleBackColor = true;
			this->bt_close_output->Click += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::bt_close_output_Click);
			// 
			// bt_filter_Sepia
			// 
			this->bt_filter_Sepia->Location = System::Drawing::Point(216, 52);
			this->bt_filter_Sepia->Margin = System::Windows::Forms::Padding(2);
			this->bt_filter_Sepia->Name = L"bt_filter_Sepia";
			this->bt_filter_Sepia->Size = System::Drawing::Size(142, 37);
			this->bt_filter_Sepia->TabIndex = 12;
			this->bt_filter_Sepia->Text = L"Filter Sepia";
			this->bt_filter_Sepia->UseVisualStyleBackColor = true;
			this->bt_filter_Sepia->Click += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::bt_filter_Sepia_Click);
			// 
			// bt_filter_Sepia_MultiThread
			// 
			this->bt_filter_Sepia_MultiThread->Location = System::Drawing::Point(216, 93);
			this->bt_filter_Sepia_MultiThread->Margin = System::Windows::Forms::Padding(2);
			this->bt_filter_Sepia_MultiThread->Name = L"bt_filter_Sepia_MultiThread";
			this->bt_filter_Sepia_MultiThread->Size = System::Drawing::Size(142, 37);
			this->bt_filter_Sepia_MultiThread->TabIndex = 13;
			this->bt_filter_Sepia_MultiThread->Text = L"Filter Sepia MultiThread";
			this->bt_filter_Sepia_MultiThread->UseVisualStyleBackColor = true;
			this->bt_filter_Sepia_MultiThread->Click += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::bt_filter_Sepia_MultiThread_Click);
			// 
			// bt_filter_Sepia_top
			// 
			this->bt_filter_Sepia_top->Location = System::Drawing::Point(362, 11);
			this->bt_filter_Sepia_top->Margin = System::Windows::Forms::Padding(2);
			this->bt_filter_Sepia_top->Name = L"bt_filter_Sepia_top";
			this->bt_filter_Sepia_top->Size = System::Drawing::Size(142, 37);
			this->bt_filter_Sepia_top->TabIndex = 14;
			this->bt_filter_Sepia_top->Text = L"Filter Sepia- Top";
			this->bt_filter_Sepia_top->UseVisualStyleBackColor = true;
			this->bt_filter_Sepia_top->Click += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::bt_filter_Sepia_left_Click);
			// 
			// bt_filter_Sepia_botton
			// 
			this->bt_filter_Sepia_botton->Location = System::Drawing::Point(508, 11);
			this->bt_filter_Sepia_botton->Margin = System::Windows::Forms::Padding(2);
			this->bt_filter_Sepia_botton->Name = L"bt_filter_Sepia_botton";
			this->bt_filter_Sepia_botton->Size = System::Drawing::Size(142, 37);
			this->bt_filter_Sepia_botton->TabIndex = 15;
			this->bt_filter_Sepia_botton->Text = L"Filter Sepia - Botton";
			this->bt_filter_Sepia_botton->UseVisualStyleBackColor = true;
			this->bt_filter_Sepia_botton->Click += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::button2_Click);
			// 
			// lb_timer
			// 
			this->lb_timer->AutoSize = true;
			this->lb_timer->Location = System::Drawing::Point(739, 75);
			this->lb_timer->Name = L"lb_timer";
			this->lb_timer->Size = System::Drawing::Size(33, 13);
			this->lb_timer->TabIndex = 16;
			this->lb_timer->Text = L"Timer";
			// 
			// textB_Time
			// 
			this->textB_Time->Location = System::Drawing::Point(742, 91);
			this->textB_Time->Name = L"textB_Time";
			this->textB_Time->Size = System::Drawing::Size(161, 20);
			this->textB_Time->TabIndex = 17;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(508, 53);
			this->button1->Margin = System::Windows::Forms::Padding(2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(142, 37);
			this->button1->TabIndex = 19;
			this->button1->Text = L"Filter Sepia - Right";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::button1_Click_1);
			// 
			// bt_filter_Sepia_left
			// 
			this->bt_filter_Sepia_left->Location = System::Drawing::Point(362, 53);
			this->bt_filter_Sepia_left->Margin = System::Windows::Forms::Padding(2);
			this->bt_filter_Sepia_left->Name = L"bt_filter_Sepia_left";
			this->bt_filter_Sepia_left->Size = System::Drawing::Size(142, 37);
			this->bt_filter_Sepia_left->TabIndex = 18;
			this->bt_filter_Sepia_left->Text = L"Filter Sepia- Left";
			this->bt_filter_Sepia_left->UseVisualStyleBackColor = true;
			this->bt_filter_Sepia_left->Click += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::bt_filter_Sepia_left_Click_1);
			// 
			// bt_filter_Sepia_Thread
			// 
			this->bt_filter_Sepia_Thread->Location = System::Drawing::Point(362, 94);
			this->bt_filter_Sepia_Thread->Margin = System::Windows::Forms::Padding(2);
			this->bt_filter_Sepia_Thread->Name = L"bt_filter_Sepia_Thread";
			this->bt_filter_Sepia_Thread->Size = System::Drawing::Size(142, 37);
			this->bt_filter_Sepia_Thread->TabIndex = 20;
			this->bt_filter_Sepia_Thread->Text = L"Filter Sepia- Thread";
			this->bt_filter_Sepia_Thread->UseVisualStyleBackColor = true;
			this->bt_filter_Sepia_Thread->Click += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::bt_filter_Sepia_Thread_Click);
			// 
			// Pavic_gui_2024_Form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1251, 617);
			this->Controls->Add(this->bt_filter_Sepia_Thread);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->bt_filter_Sepia_left);
			this->Controls->Add(this->textB_Time);
			this->Controls->Add(this->lb_timer);
			this->Controls->Add(this->bt_filter_Sepia_botton);
			this->Controls->Add(this->bt_filter_Sepia_top);
			this->Controls->Add(this->bt_filter_Sepia_MultiThread);
			this->Controls->Add(this->bt_filter_Sepia);
			this->Controls->Add(this->bt_close_output);
			this->Controls->Add(this->bt_close_copy);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->bt_filter_bw);
			this->Controls->Add(this->bt_copy);
			this->Controls->Add(this->pbox_output);
			this->Controls->Add(this->pbox_copy);
			this->Controls->Add(this->pbox_input);
			this->Controls->Add(this->bt_exit);
			this->Controls->Add(this->bt_close);
			this->Controls->Add(this->bt_open);
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"Pavic_gui_2024_Form";
			this->Text = L"PROJECT: IMPACTLAB LAB 2025";
			this->Load += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::Pavic_gui_2024_Form_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbox_input))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbox_copy))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbox_output))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void bt_open_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ ofd = gcnew OpenFileDialog();
		if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			pbox_input->ImageLocation = ofd->FileName;
		}
	}
private: System::Void bt_close_Click(System::Object^ sender, System::EventArgs^ e) {

	pbox_input->Image = nullptr;

	
}
private: System::Void bt_copy_Click(System::Object^ sender, System::EventArgs^ e) {
	//copyStopwatch = gcnew System::Diagnostics.Stopwatch();
	//copyStopwatch->Start();
	pbox_copy->Image = pbox_input->Image;

	//copyStopwatch->Stop();
	lb_timer->Text = "Tempo de cópia: ";//+copyStopwatch->ElapsedMilliseconds.ToString() + " ms";
	textB_Time->Text = "Impact labd 2025";

}
private: System::Void bt_filter_bw_Click(System::Object^ sender, System::EventArgs^ e) {

	// Get the input image
	Bitmap^ inputImage = (Bitmap^)pbox_input->Image;

	// Create a new output image with the same dimensions
	Bitmap^ outputImage = gcnew Bitmap(inputImage->Width, inputImage->Height);

	// Apply the black and white filter
	for (int i = 0; i < inputImage->Width; i++) {
		for (int j = 0; j < inputImage->Height; j++) {
			Color pixelColor = inputImage->GetPixel(i, j);
			int grayValue = (int)(0.299 * pixelColor.R + 0.587 * pixelColor.G + 0.114 * pixelColor.B);
			outputImage->SetPixel(i, j, Color::FromArgb(grayValue, grayValue, grayValue));
		}
	}

	// Display the output image
	pbox_output->Image = outputImage;
}
private: System::Void bt_exit_Click(System::Object^ sender, System::EventArgs^ e) {
	Application::Exit();
}
private: System::Void bt_close_copy_Click(System::Object^ sender, System::EventArgs^ e) {
	pbox_copy->Image = nullptr;
	
}
private: System::Void bt_close_output_Click(System::Object^ sender, System::EventArgs^ e) {
	pbox_output->Image = nullptr;
}
private: System::Void Pavic_gui_2024_Form_Load(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void pbox_input_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void bt_filter_Sepia_Click(System::Object^ sender, System::EventArgs^ e) {
	// Get the input image
	Bitmap^ inputImage = (Bitmap^)pbox_input->Image;

	// Create a new output image with the same dimensions
	Bitmap^ outputImage = gcnew Bitmap(inputImage->Width, inputImage->Height);

	// Apply the black and white filter
	for (int i = 0; i < inputImage->Width; i++) {
		for (int j = 0; j < inputImage->Height; j++) {
			// Step:1 Get the color of the current pixel
			Color pixelColor = inputImage->GetPixel(i, j);

			// Step : 2  Extract original Red, Green, annd Blue Values
			int r = pixelColor.R;
			int g = pixelColor.G;
			int b = pixelColor.B;
			// Step: 3 Calculate the new pixel values using Sepia Formula
			/*	tr = 0.393R + 0.769G + 0.189B
				tg = 0.349R + 0.686G + 0.168B
				tb = 0.272R + 0.534G + 0.131B
				*/
			double tr = 0.393*r + 0.769*g + 0.189*b;
			double tg = 0.349 * r + 0.686 * g + 0.168 * b;
			double tb = 0.272 * r + 0.534 * g + 0.131*b;

			// Step : 4 Clamp the values  0- 255 range 
			int newR = Math::Min(255, (int)tr);
			int newG = Math::Min(255, (int)tg);
			int newB = Math::Min(255, (int)tb);

			//outputImage->SetPixel(i, j, Color::FromArgb(tr, tg, tb));
			outputImage->SetPixel(i, j, Color::FromArgb(newR, newG, newB));

			/*	tr = 0.393R + 0.769G + 0.189B
				tg = 0.349R + 0.686G + 0.168B
				tb = 0.272R + 0.534G + 0.131B*/

		}
	}

	// Display the output image
	pbox_output->Image = outputImage;
}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void bt_filter_Sepia_MultiThread_Click(System::Object^ sender, System::EventArgs^ e) {
	// Get the input image
	Bitmap^ inputImage = (Bitmap^)pbox_input->Image;

	// Create a new output image with the same dimensions
	Bitmap^ outputImage = gcnew Bitmap(inputImage->Width, inputImage->Height);
	//// Bloquear os bits das imagens para acesso direto aos dados brutos
	//Imaging::BitmapData^ bmpDataInput = inputImage->LockBits(
	//	Drawing::Rectangle(0, 0, inputImage->Width, inputImage->Height),
	//	Imaging::ImageLockMode::ReadOnly,
	//	inputImage->PixelFormat); // Use o PixelFormat original

	//Imaging::BitmapData^ bmpDataOutput = outputImage->LockBits(
	//	Drawing::Rectangle(0, 0, outputImage->Width, outputImage->Height),
	//	Imaging::ImageLockMode::WriteOnly,
	//	outputImage->PixelFormat); // Use o PixelFormat original

	//// Calcular o ponto médio para dividir a imagem
	//int midY = inputImage->Height / 2;

	//// Calcular bytes por pixel
	//int bytesPerPixel = Bitmap::GetPixelFormatSize(inputImage->PixelFormat) / 8;

	//
	//// Criar as threads, passando os ponteiros para os dados brutos e outros parâmetros
	//std::thread t1(&ApplySepiaFilterPartialRaw, bmpDataInput->Scan0, bmpDataInput->Stride, bmpDataOutput->Scan0, bmpDataOutput->Stride, inputImage->Width, bytesPerPixel, 0, midY);
	//std::thread t2(&ApplySepiaFilterPartialRaw, bmpDataInput->Scan0, bmpDataInput->Stride, bmpDataOutput->Scan0, bmpDataOutput->Stride, inputImage->Width, bytesPerPixel, midY, inputImage->Height);



	//// void ApplySepiaFilterPartialRaw(IntPtr inputScan0, int inputStride, IntPtr outputScan0, int outputStride, int width, int bytesPerPixel, int startY, int endY) {
	//// Esperar que ambas as threads concluam sua execução
	//t1.join();
	//t2.join();

	//// Desbloquear os bits das imagens APÓS as threads terminarem
	//inputImage->UnlockBits(bmpDataInput);
	//outputImage->UnlockBits(bmpDataOutput);


	// Display the output image
	//pbox_output->Image = outputImage;

}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	// Get the input image
	Bitmap^ inputImage = (Bitmap^)pbox_input->Image;

	// Create a new output image with the same dimensions
	Bitmap^ outputImage = gcnew Bitmap(inputImage->Width, inputImage->Height);

	// Apply the black and white filter
	// inputImage->Width -->> X
	// inputImage->Height -->> Y



	//Image Botton !!
	int startY_Botton = inputImage->Height / 2;
	int endY_Botton = inputImage->Height;


	// Filtro  Botton
	ApplySepiaFilterPartial(inputImage, outputImage, startY_Botton, endY_Botton);


	// Display the output image
	//pbox_copy->Image = outputImage;
	pbox_output->Image = outputImage;

}
private: System::Void bt_filter_Sepia_left_Click(System::Object^ sender, System::EventArgs^ e) {

	// Get the input image
	Bitmap^ inputImage = (Bitmap^)pbox_input->Image;

	// Create a new output image with the same dimensions
	Bitmap^ outputImage = gcnew Bitmap(inputImage->Width, inputImage->Height);

	// Apply the black and white filter
	// inputImage->Width -->> X
	// inputImage->Height -->> Y
	
	//Image Top !!
	int startY_Top = 0;
	int endY_Top = inputImage->Height/2;

	//Image Botton !!
	int startY_Botton = inputImage->Height / 2;
	int endY_Botton = inputImage->Height;
	// Timer Start
	// Filtro  Top
	ApplySepiaFilterPartial(inputImage, outputImage, startY_Top, endY_Top);
	//Timer End

	// Filtro  Botton
	//ApplySepiaFilterPartial(inputImage, outputImage, startY_Botton, endY_Botton);

	// Display the output image
	pbox_copy->Image = outputImage;
	//pbox_output->Image = outputImage;
}
private: System::Void bt_filter_Sepia_left_Click_1(System::Object^ sender, System::EventArgs^ e) {

	// Get the input image
	Bitmap^ inputImage = (Bitmap^)pbox_input->Image;

	// Create a new output image with the same dimensions
	Bitmap^ outputImage = gcnew Bitmap(inputImage->Width, inputImage->Height);

	// Apply the black and white filter
	// inputImage->Width -->> X
	// inputImage->Height -->> Y

	//Image Top !!
	int startY_Top = 0;
	int endY_Top = inputImage->Height / 2;

	//Image Botton !!
	int startY_Botton = inputImage->Height / 2;
	int endY_Botton = inputImage->Height;

	// Image Left
	int startX_left = 0;
	int endX_left = inputImage->Width/2;

	// Image Right
	int startX_Right = inputImage->Width / 2;
	int endX_Right = inputImage->Width ;

	// Filtro  Top-Left
	ApplySepiaFilterWindow(inputImage, outputImage, startX_left, endX_left, startY_Top, endY_Top);

	// Filtro  Botton
	//ApplySepiaFilterPartial(inputImage, outputImage, startY_Botton, endY_Botton);

	// Display the output image
	pbox_copy->Image = outputImage;
	//pbox_output->Image = outputImage;

}
private: System::Void button1_Click_1(System::Object^ sender, System::EventArgs^ e) {
	// Get the input image
	Bitmap^ inputImage = (Bitmap^)pbox_input->Image;

	// Create a new output image with the same dimensions
	Bitmap^ outputImage = gcnew Bitmap(inputImage->Width, inputImage->Height);

	// Apply the black and white filter
	// inputImage->Width -->> X
	// inputImage->Height -->> Y

	//Image Top !!
	int startY_Top = 0;
	int endY_Top = inputImage->Height / 2;

	//Image Botton !!
	int startY_Botton = inputImage->Height / 2;
	int endY_Botton = inputImage->Height;

	// Image Left
	int startX_left = 0;
	int endX_left = inputImage->Width / 2;

	// Image Right
	int startX_Right = inputImage->Width / 2;
	int endX_Right = inputImage->Width;

	// Filtro  Botton - Right
	ApplySepiaFilterWindow(inputImage, outputImage, startX_Right, endX_Right, startY_Botton, endY_Botton);

	// Filtro  Botton
	//ApplySepiaFilterPartial(inputImage, outputImage, startY_Botton, endY_Botton);

	// Display the output image
	//pbox_copy->Image = outputImage;
	pbox_output->Image = outputImage;

}
private: System::Void bt_filter_Sepia_Thread_Click(System::Object^ sender, System::EventArgs^ e) {

	// Get the input image
	Bitmap^ inputImage = (Bitmap^)pbox_input->Image;

	// Create a new output image with the same dimensions
	Bitmap^ outputImage = gcnew Bitmap(inputImage->Width, inputImage->Height);

	// Apply the black and white filter
	// inputImage->Width -->> X
	// inputImage->Height -->> Y

	//Image Top !!
	int startY_Top = 0;
	int endY_Top = inputImage->Height / 2;

	//Image Botton !!
	int startY_Botton = inputImage->Height / 2;
	int endY_Botton = inputImage->Height;

	// Image Left
	int startX_left = 0;
	int endX_left = inputImage->Width / 2;

	// Image Right
	int startX_Right = inputImage->Width / 2;
	int endX_Right = inputImage->Width;


	//  Filter with threads 

	//// Criar as threads, passando os ponteiros para os dados brutos e outros parâmetros
	//std::thread t1(&ApplySepiaFilterPartialRaw, bmpDataInput->Scan0, bmpDataInput->Stride, bmpDataOutput->Scan0, bmpDataOutput->Stride, inputImage->Width, bytesPerPixel, 0, midY);
	
	//std::thread t1(ApplySepiaFilterWindow,inputImage, outputImage, startX_Right, endX_Right, startY_Botton, endY_Botton);
	
	//ApplySepiaFilterWindow(inputImage, outputImage, startX_Right, endX_Right, startY_Botton, endY_Botton);


	// void ApplySepiaFilterPartialRaw(IntPtr inputScan0, int inputStride, IntPtr outputScan0, int outputStride, int width, int bytesPerPixel, int startY, int endY) {
	// Esperar que ambas as threads concluam sua execução
	//t1.join();

	// Filtro  Botton - Right
	ApplySepiaFilterWindow(inputImage, outputImage, startX_Right, endX_Right, startY_Botton, endY_Botton);

	// Filtro  Botton
	//ApplySepiaFilterPartial(inputImage, outputImage, startY_Botton, endY_Botton);

	// Display the output image
	//pbox_copy->Image = outputImage;
	pbox_output->Image = outputImage;
}
};
}
