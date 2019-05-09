//---------------------------------------------------------------------------

#ifndef SQLiteH
#define SQLiteH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "VirtualTrees.hpp"
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <string>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TVirtualStringTree *VirtualStringTree1;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TButton *Button5;
	TLabel *Label1;
	//
	void __fastcall TableGetText(TBaseVirtualTree *Sender, PVirtualNode Node, TColumnIndex Column,
		  TVSTTextType TextType, UnicodeString &CellText);
	void __fastcall Button1Click(TObject *Sender); //Кнопка на открытие БД
	void __fastcall Button2Click(TObject *Sender); //Кнопка на очистку БД
	void __fastcall Button3Click(TObject *Sender); //Кнопка на стирание строки в БД
	void __fastcall Button4Click(TObject *Sender); //Кнопка выхода из программы
	void __fastcall Button5Click(TObject *Sender); //Кнопка изменения цветовой схемы программы
private:	// User declarations
public:		// User declarations
//
	typedef struct {
	int ArtistId;
	UnicodeString Name;
	} downloadTab;
//
	__fastcall TForm1(TComponent* Owner);
//
};
//
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
