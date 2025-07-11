#pragma once



namespace pavicgui2024 {
//#include "include/Diagnostic.h"



	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std; // Assuming Diagnostics is in the std namespace

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
			// Pavic_gui_2024_Form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1251, 617);
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
	//label11->Text = "Tempo de cópia: " + copyStopwatch->ElapsedMilliseconds.ToString() + " ms";

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

	// 2 threads
	// Imagen = data
	int midY = inputImage->Height / 2;
	X=0, Y=0 
	--------------------- T1
	--------------------- 
	--------------------- Y/2 T2
	---------------------
	--------------------- X= Width, Y = Height


	// Criar as threads

	std::thread t1( func, var);
	std::thread t2(func, var);

	// Thread Main

	t1.join();
	t2.join();



	// Display the output image
	pbox_output->Image = outputImage;

}
};
}
