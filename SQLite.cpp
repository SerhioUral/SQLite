//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "sqlite3.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include "SQLite.h"
//---------------------------------------------------------------------------
#pragma link "VirtualTrees"
#pragma resource "*.dfm"

using namespace std;

TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TableGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
		  TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)

{
  if(!Node) return;
  downloadTab *Info = (downloadTab *)Sender->GetNodeData(Node);
  switch(Column)
{
	case 0: CellText = Info->ArtistId;
	break;
	case 1: CellText = Info->Name;
	break;
}

}
//---------------------------------------------------------------------------



//Кнопка на открытие БД
void __fastcall TForm1::Button1Click(TObject *Sender)
{
int count;
const char * Path = "C:\\Users\\Filatov Sergey\\Desktop\\SQLite\\chinook.db";
sqlite3* baza;
int op = sqlite3_open(Path, &baza);
const char * TableSh = "SELECT * FROM artists;";
sqlite3_stmt * pStatement;
sqlite3_stmt * pStatementCount;
int Conclusion = sqlite3_prepare_v2(baza, TableSh, -1, &pStatement, NULL);
if (Conclusion != SQLITE_OK)
{
	cout << "Ошибка запроса!" << endl;
	sqlite3_close(baza);
	sqlite3_finalize(pStatement);
}
const char * sumStr = "SELECT count(*) FROM artists;";
int queryTotal = sqlite3_prepare_v2(baza, sumStr, -1, &pStatementCount, NULL);
PVirtualNode optedNode = VirtualStringTree1->AddChild(VirtualStringTree1->RootNode);
downloadTab *Info = (downloadTab*) VirtualStringTree1->GetNodeData(optedNode);
int result1 = sqlite3_step(pStatementCount);
if (result1 == SQLITE_ROW)
{
count = sqlite3_column_int(pStatementCount, 0);
}
else return;
sqlite3_finalize(pStatementCount);
VirtualStringTree1->Clear();
VirtualStringTree1->NodeDataSize = sizeof(downloadTab);
VirtualStringTree1->BeginUpdate();
for (int i = 0; i < count; i++) {
	PVirtualNode entryNode = VirtualStringTree1->AddChild(VirtualStringTree1->RootNode);
	downloadTab *Info = (downloadTab*) VirtualStringTree1->GetNodeData(entryNode);
	int Conclusion = sqlite3_step(pStatement);
	if (Conclusion == SQLITE_ROW)
	{
		Info->ArtistId = sqlite3_column_int(pStatement, 0);
		Info->Name = (UnicodeString)(char *)sqlite3_column_text(pStatement, 1);
	}
}
VirtualStringTree1->EndUpdate();
sqlite3_close(baza);
sqlite3_finalize(pStatement);
}
//---------------------------------------------------------------------------

//Кнопка на очистку БД
void __fastcall TForm1::Button2Click(TObject *Sender)
{
int count;
const char * Path = "C:\\Users\\Filatov Sergey\\Desktop\\SQLite\\chinook.db";
sqlite3* baza;
int op = sqlite3_open(Path, &baza);
char *Error = 0;
string Delete = "DELETE FROM artists;";
int deleteTable = sqlite3_exec(baza, Delete.c_str(), NULL, NULL, &Error);
if (Error != 0)
{
	cout << "Ошибка удаления таблицы!" << endl;
	sqlite3_close(baza);
}
const char * TableSh = "SELECT * FROM artists;";
sqlite3_stmt * pStatement;
sqlite3_stmt * pStatementCount;
int Conclusion = sqlite3_prepare_v2(baza, TableSh, -1, &pStatement, NULL);
if (Conclusion != SQLITE_OK)
{
	cout << "Ошибка запроса!" << endl;
	sqlite3_close(baza);
	sqlite3_finalize(pStatement);
}
const char * sumStr = "SELECT count(*) FROM artists;";
int queryCount = sqlite3_prepare_v2(baza, sumStr, -1, &pStatementCount, NULL);
PVirtualNode optedNode = VirtualStringTree1->AddChild(VirtualStringTree1->RootNode);
downloadTab *Info = (downloadTab*) VirtualStringTree1->GetNodeData(optedNode);
int result1 = sqlite3_step(pStatementCount);
if (result1 == SQLITE_ROW)
{
count = sqlite3_column_int(pStatementCount, 0);
}
else return;
sqlite3_finalize(pStatementCount);
VirtualStringTree1->Clear();
VirtualStringTree1->NodeDataSize = sizeof(downloadTab);
VirtualStringTree1->BeginUpdate();
for (int i = 0; i < count; i++) {
	PVirtualNode entryNode = VirtualStringTree1->AddChild(VirtualStringTree1->RootNode);
	downloadTab *Info = (downloadTab*) VirtualStringTree1->GetNodeData(entryNode);
	int Conclusion = sqlite3_step(pStatement);
	if (Conclusion == SQLITE_ROW)
	{
		Info->ArtistId = sqlite3_column_int(pStatement, 0);
		Info->Name = (UnicodeString)(char*)sqlite3_column_text(pStatement, 1);
	}
}
VirtualStringTree1->EndUpdate();
sqlite3_close(baza);
sqlite3_finalize(pStatement);
}
//---------------------------------------------------------------------------

//Кнопка на стирание строки в БД
void __fastcall TForm1::Button3Click(TObject *Sender)
{
if (!VirtualStringTree1->SelectedCount) {
	return;
}
const char * Path = "C:\\Users\\Filatov Sergey\\Desktop\\SQLite\\chinook.db";
sqlite3* baza;
int op = sqlite3_open(Path, &baza);
string insertQuery = "DELETE FROM artists WHERE ArtistId = ";
vector<int> indexVector;
PVirtualNode optedNode = VirtualStringTree1->GetFirstSelected();
downloadTab *Info = (downloadTab *)VirtualStringTree1->GetNodeData(optedNode);
indexVector.push_back(Info->ArtistId);
for (int i = 0; i < VirtualStringTree1->SelectedCount - 1; i++) {
	optedNode = VirtualStringTree1->GetNextSelected(optedNode);
	downloadTab *Info = (downloadTab *)VirtualStringTree1->GetNodeData(optedNode);
	indexVector.push_back(Info->ArtistId);
}
char *Error = 0;
VirtualStringTree1->DeleteSelectedNodes();
for (vector<int>::iterator a = indexVector.begin();
	a != indexVector.end(); ++a){
	string subString = to_string(*a);
	string tempQuery = insertQuery;
	tempQuery += subString;
	int ex = sqlite3_exec(baza, tempQuery.c_str(), NULL, NULL, &Error);
	if( ex != SQLITE_OK ) {
		return;
	}
}
sqlite3_close(baza);
}
//---------------------------------------------------------------------------

//Кнопка выхода из программы
void __fastcall TForm1::Button4Click(TObject *Sender)
{
Form1->Close();
}
//---------------------------------------------------------------------------

//Кнопка изменения цветовой схемы программы
void __fastcall TForm1::Button5Click(TObject *Sender)
{
if (VirtualStringTree1->Color == clWindow) {
	Form1->Color = clGradientActiveCaption;
	VirtualStringTree1->Color = clGradientInactiveCaption;
	Button5->Caption = "Классический стиль";
}
else {
	Form1->Color = clBtnFace;
	VirtualStringTree1->Color = clWindow;
	Button5->Caption = "Стиль автора";
}
}
//---------------------------------------------------------------------------



