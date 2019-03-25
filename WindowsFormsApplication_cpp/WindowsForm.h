#pragma once
#include"DataManager.h"
#include"DotNetUtilities.h"
#include <msclr\marshal_cppstd.h>

namespace WindowsFormsApplication_cpp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// WindowsForm 的摘要
	/// </summary>
	public ref class WindowsForm : public System::Windows::Forms::Form
	{
	public:
		WindowsForm(void)
		{
			InitializeComponent();
			dataManager = new DataManager();
			lastInputLength = -1;
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~WindowsForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::MenuStrip^  menuStrip2;
	private: System::Windows::Forms::ToolStripMenuItem^  FileToolStripMenuItem;

	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::ToolStripMenuItem^  LoadVectorToolStripMenuItem;



	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel1;
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel2;
	private: System::Windows::Forms::Label^  OutputLabel;
	private: System::Windows::Forms::TextBox^  Output;

	private: System::Windows::Forms::Label^  InputLabel;
	private: System::Windows::Forms::TextBox^  Input;
	private: System::Windows::Forms::Label^  VectorLabel;
	private: System::Windows::Forms::ListBox^  VectorList;



	protected:















	protected:

	private:
		/// <summary>
			DataManager* dataManager;
			String^ userInput;
			int lastInputLength;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::ToolStripMenuItem^  LoadMatrixToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog2;
	private: int contextOP = 0;

			 /// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip2 = (gcnew System::Windows::Forms::MenuStrip());
			this->FileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->LoadVectorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->LoadMatrixToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->InputLabel = (gcnew System::Windows::Forms::Label());
			this->Input = (gcnew System::Windows::Forms::TextBox());
			this->VectorLabel = (gcnew System::Windows::Forms::Label());
			this->VectorList = (gcnew System::Windows::Forms::ListBox());
			this->flowLayoutPanel2 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->OutputLabel = (gcnew System::Windows::Forms::Label());
			this->Output = (gcnew System::Windows::Forms::TextBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->openFileDialog2 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->menuStrip2->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->flowLayoutPanel1->SuspendLayout();
			this->flowLayoutPanel2->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip2
			// 
			this->menuStrip2->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->FileToolStripMenuItem });
			this->menuStrip2->Location = System::Drawing::Point(0, 0);
			this->menuStrip2->Name = L"menuStrip2";
			this->menuStrip2->Size = System::Drawing::Size(384, 24);
			this->menuStrip2->TabIndex = 1;
			this->menuStrip2->Text = L"menuStrip2";
			// 
			// FileToolStripMenuItem
			// 
			this->FileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->LoadVectorToolStripMenuItem,
					this->LoadMatrixToolStripMenuItem
			});
			this->FileToolStripMenuItem->Name = L"FileToolStripMenuItem";
			this->FileToolStripMenuItem->Size = System::Drawing::Size(38, 20);
			this->FileToolStripMenuItem->Text = L"File";
			// 
			// LoadVectorToolStripMenuItem
			// 
			this->LoadVectorToolStripMenuItem->Name = L"LoadVectorToolStripMenuItem";
			this->LoadVectorToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->LoadVectorToolStripMenuItem->Text = L"Load Vector";
			this->LoadVectorToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::LoadVectorToolStripMenuItem_Click);
			// 
			// LoadMatrixToolStripMenuItem
			// 
			this->LoadMatrixToolStripMenuItem->Name = L"LoadMatrixToolStripMenuItem";
			this->LoadMatrixToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->LoadMatrixToolStripMenuItem->Text = L"Load Matrix";
			this->LoadMatrixToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::LoadMatrixToolStripMenuItem_Click);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel1, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel2, 0, 0);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 24);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 1;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(384, 338);
			this->tableLayoutPanel1->TabIndex = 2;
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Controls->Add(this->InputLabel);
			this->flowLayoutPanel1->Controls->Add(this->Input);
			this->flowLayoutPanel1->Controls->Add(this->VectorLabel);
			this->flowLayoutPanel1->Controls->Add(this->VectorList);
			this->flowLayoutPanel1->Location = System::Drawing::Point(195, 3);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(186, 332);
			this->flowLayoutPanel1->TabIndex = 0;
			// 
			// InputLabel
			// 
			this->InputLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->InputLabel->AutoSize = true;
			this->InputLabel->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(136)));
			this->InputLabel->Location = System::Drawing::Point(3, 0);
			this->InputLabel->Name = L"InputLabel";
			this->InputLabel->Size = System::Drawing::Size(41, 16);
			this->InputLabel->TabIndex = 0;
			this->InputLabel->Text = L"Input";
			// 
			// Input
			// 
			this->Input->Location = System::Drawing::Point(3, 19);
			this->Input->Multiline = true;
			this->Input->Name = L"Input";
			this->Input->Size = System::Drawing::Size(180, 158);
			this->Input->TabIndex = 1;
			this->Input->TextChanged += gcnew System::EventHandler(this, &WindowsForm::Input_TextChanged);
			// 
			// VectorLabel
			// 
			this->VectorLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->VectorLabel->AutoSize = true;
			this->VectorLabel->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(136)));
			this->VectorLabel->Location = System::Drawing::Point(3, 180);
			this->VectorLabel->Name = L"VectorLabel";
			this->VectorLabel->Size = System::Drawing::Size(47, 16);
			this->VectorLabel->TabIndex = 2;
			this->VectorLabel->Text = L"Vector";
			// 
			// VectorList
			// 
			this->VectorList->FormattingEnabled = true;
			this->VectorList->ItemHeight = 12;
			this->VectorList->Location = System::Drawing::Point(3, 199);
			this->VectorList->Name = L"VectorList";
			this->VectorList->Size = System::Drawing::Size(180, 124);
			this->VectorList->TabIndex = 3;
			// 
			// flowLayoutPanel2
			// 
			this->flowLayoutPanel2->Controls->Add(this->OutputLabel);
			this->flowLayoutPanel2->Controls->Add(this->Output);
			this->flowLayoutPanel2->Location = System::Drawing::Point(3, 3);
			this->flowLayoutPanel2->Name = L"flowLayoutPanel2";
			this->flowLayoutPanel2->Size = System::Drawing::Size(186, 332);
			this->flowLayoutPanel2->TabIndex = 1;
			// 
			// OutputLabel
			// 
			this->OutputLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->OutputLabel->AutoSize = true;
			this->OutputLabel->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(136)));
			this->OutputLabel->Location = System::Drawing::Point(3, 0);
			this->OutputLabel->Name = L"OutputLabel";
			this->OutputLabel->Size = System::Drawing::Size(52, 16);
			this->OutputLabel->TabIndex = 0;
			this->OutputLabel->Text = L"Output";
			// 
			// Output
			// 
			this->Output->Font = (gcnew System::Drawing::Font(L"新細明體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->Output->Location = System::Drawing::Point(3, 19);
			this->Output->Multiline = true;
			this->Output->Name = L"Output";
			this->Output->ReadOnly = true;
			this->Output->Size = System::Drawing::Size(183, 313);
			this->Output->TabIndex = 1;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &WindowsForm::openFileDialog1_FileOk);
			// 
			// openFileDialog2
			// 
			this->openFileDialog2->FileName = L"openFileDialog2";
			this->openFileDialog2->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &WindowsForm::openFileDialog2_FileOk);
			// 
			// WindowsForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(384, 362);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->menuStrip2);
			this->Name = L"WindowsForm";
			this->Text = L"VectorExample";
			this->Load += gcnew System::EventHandler(this, &WindowsForm::WindowsForm_Load);
			this->menuStrip2->ResumeLayout(false);
			this->menuStrip2->PerformLayout();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel1->PerformLayout();
			this->flowLayoutPanel2->ResumeLayout(false);
			this->flowLayoutPanel2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void WindowsForm_Load(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void LoadVectorToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
{
	//開啟Dialog
	openFileDialog1->ShowDialog();
}
private: System::Void LoadMatrixToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	 //開啟Dialog
	 openFileDialog2->ShowDialog();
}
private: System::Void Input_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	//當Input textbox中的輸入改變時，便會進入此函式
	//取得向量資料
	std::map<std::string,Vector>& vectors = dataManager->GetVectors();
	msclr::interop::marshal_context context;

	//判斷輸入自元為'\n'，並防止取到字串-1位置
	if (Input->Text->Length-1 >= 0 &&Input->Text[Input->Text->Length - 1] == '\n')
	{
		Output->Text = "";
		//將使用者輸入字串(在userInput中)，依空白作切割
		array<String^> ^userCommand = userInput->Split(' ');
		//Vector環境
		if (contextOP == 0) {
			//字串比較，若指令為"print"的情況
			if (userCommand[0] == "Print")
			{
				//定意輸出暫存
				String^ outputTemp = "";
				std::string vname = context.marshal_as<std::string>(userCommand[1]);
				//若變數名稱與指令變數名稱符合
				if (vectors.count(vname))
				{
					Vector& target = vectors[vname];
					//將輸出格式存入暫存
					outputTemp += "[";
					//將輸出資料存入暫存
					for (unsigned int j = 0; j < target.Data.size(); j++)
					{
						outputTemp += target.Data[j].ToString();
						if (j != target.Data.size() - 1)
							outputTemp += ",";
					}
					//將輸出格式存入暫存，並且換行
					outputTemp += "]" + Environment::NewLine;
					//輸出暫存資訊
					Output->Text += userCommand[1] + " = " + outputTemp;
				}
			}
			else if (userCommand[0] == "Norm") {
				std::string left_v = context.marshal_as<std::string>(userCommand[1]);
				//std::string right_v = context.marshal_as<std::string>(userCommand[2]);
				if (vectors.count(left_v) == 0) {
					Output->Text += "Error, vector " + userCommand[1] + " undefined." + Environment::NewLine;
				}
				else {
					double val = length(vectors[left_v])[0];
					Output->Text += "Norm(" + userCommand[1] + ") = " + val.ToString() + Environment::NewLine;
				}
			}
			else if (userCommand[0] == "Normal") {
				std::string left_v = context.marshal_as<std::string>(userCommand[1]);
				if (vectors.count(left_v) == 0) {
					Output->Text += "Error, vector " + userCommand[1] + " undefined." + Environment::NewLine;
				}
				else {
					Vector vec = nrmlz(vectors[left_v]);
					Output->Text += "Normal(" + userCommand[1] + ") = [ ";
					for (int i = 0; i < vec.dim(); i++) {
						Output->Text += vec[i].ToString() + " ";
					}
					Output->Text += "]"+ Environment::NewLine;
				}
			}
			else if (userCommand[0] == "Cross") {

			}
			else if (userCommand[0] == "Com") {

			}
			else if (userCommand[0] == "Proj") {

			}
			else if (userCommand[0] == "Area") {

			}
			else if (userCommand[0] == "isParallel") {

			}
			else if (userCommand[0] == "isOrthogonal") {

			}
			else if (userCommand[0] == "angle") {

			}
			else if (userCommand[0] == "Calc") {
				
				std::vector<std::string> formula;//函式
				for (int i = 1; i < userCommand->Length; ++i) {
					formula.push_back(context.marshal_as<std::string>(userCommand[i]));
				}

				Flink * HEAD;
				Flink * Cur;
				try {
					//把函式轉換成後序式
					Infix2Postfix(formula);
					
					//轉換成Token Chain
					int length = 0;
					for (auto i = formula.begin(); i != formula.end(); ++i,++length) {
						if (length == 0) {
							HEAD = new Flink;
							Cur = HEAD;
						}
						else {
							Cur->next = new Flink;
							Cur->next->prev = Cur;
							Cur = Cur->next;
						}
						
						if (VectorOps.count(*i) == 0) {
							if (vectors.count(*i) == 0) {
								std::string msg = "no such instance" + *i;
								throw std::exception(msg.c_str(), -1);
							}
							Cur->type = Flink_e::vector;
							Cur->value.vec = new Vector(vectors[*i]);
						}
						else {
							Cur->type = Flink_e::op;
							Cur->value.op = new std::string(*i);
						}
					}

					//執行每個Op，將計算結果加入Chain中
					while (length >1) {
						Cur = HEAD;
						while (Cur->type != Flink_e::op) {
							if (Cur == nullptr)throw std::exception("Error, Incorrect Formula", -1);
							Cur = Cur->next;
						}
						Flink * v2 = Cur->prev;
						Flink * v1 = v2->prev;
						Flink * vRet = new Flink;
						vRet->value.vec = new Vector(std::move(VectorOps[*(Cur->value.op)].two(*v1->value.vec, *v2->value.vec)));
						//setup
						vRet->type = Flink_e::vector;
						vRet->next = Cur->next;
						if(vRet->next != nullptr) vRet->next->prev = vRet;
						if (v1 == HEAD) HEAD = vRet;
						else {
							vRet->prev = v1->prev;
							vRet->prev->next = vRet;
						}
						//cleanup
						delete v1;
						delete v2;
						delete Cur;
						length -= 2;
					}

					//紀錄
					Output->Text += "result = [ ";
					for(auto i = HEAD->value.vec->Data.begin(), j = HEAD->value.vec->Data.end() ;  i != j ; ++i){
						Output->Text += (*i).ToString() + " ";
					}
					Output->Text += "]" + Environment::NewLine;

					//清理
					Cur = HEAD;
					for (; length > 0; --length) {
						HEAD = Cur;
						Cur = HEAD->next;
						delete HEAD;
					}
				}
				catch (std::exception& e) {
					Output->Text += gcnew String(e.what()) + Environment::NewLine;
				}
				
			}
			else
			{
				Output->Text += "-Command not found-" + Environment::NewLine;
			}
		}
		//Matrix環境
		else {

		}

		userInput = "";
	}
	else
	{
		//將使用者輸入字串(在Text box中)，依'\n'作切割
		array<String^> ^userCommand = Input->Text->Split('\n');
		//並將最後一行，作為目前使用者輸入指令
		userInput = userCommand[userCommand->Length-1];
	}

}
private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) 
{
	//在Dialog按下OK便會進入此函式
	//字串轉制string^ to string
	std::string tempFileName;
	MarshalString(openFileDialog1->FileName, tempFileName);
	//將檔案路徑名稱傳入dataManager
	dataManager->SetFileName(tempFileName);
	//從讀取讀取向量資料
	if (dataManager->LoadVectorData())
	{
		//將VectorList中項目先做清除
		VectorList->Items->Clear();	
		//取得所有向量資料
		std::map<std::string,Vector>& vectors = dataManager->GetVectors();

		for (auto it = vectors.begin(); it != vectors.end() ; it++)
		{
			//將檔案名稱存入暫存
			std::string tempString = it->first;
			//將輸出格式存入暫存
			tempString += " [";
			//將輸出資料存入暫存
			for (unsigned int j = 0; j<it->second.Data.size(); j++)
			{
				std::string scalarString = std::to_string(it->second.Data[j]);
				tempString += scalarString.substr(0, scalarString.size() - 5);
				if (j != it->second.Data.size() - 1)
					tempString += ",";
			}
			//將輸出格式存入暫存
			tempString += "]";
			//將項目加入VectorList中
			VectorList->Items->Add(gcnew String(tempString.c_str()));
		}
		Output->Text += "-Vector datas have been loaded-" + Environment::NewLine;
	}
}
private: System::Void openFileDialog2_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
	//TODO:LOADMATRIX
}








};
}
