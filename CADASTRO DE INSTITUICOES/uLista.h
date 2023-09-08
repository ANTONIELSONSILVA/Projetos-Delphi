//---------------------------------------------------------------------------

#ifndef uListaH
#define uListaH
//---------------------------------------------------------------------------

#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.Mask.hpp>
#include "UtilUnit.h"
#include <Data.DB.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Data.DBXMSSQL.hpp>
#include <Data.SqlExpr.hpp>
#include <Data.FMTBcd.hpp>


//---------------------------------------------------------------------------
class TfrmLista : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *grid;
	TSQLConnection *SQLConnection1;
	TSQLQuery *SQLQuery1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall gridDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State);
	void __fastcall gridClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TfrmLista(TComponent* Owner);

	struct logos {
      int id;
      AnsiString nome;
      TBitmap *bitmap;
    };

    logos *vetorLogos;

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmLista *frmLista;
//---------------------------------------------------------------------------
#endif
