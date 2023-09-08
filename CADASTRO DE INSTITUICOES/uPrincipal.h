//---------------------------------------------------------------------------

#ifndef uPrincipalH
#define uPrincipalH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.Mask.hpp>
#include "UtilUnit.h"
#include <Data.DB.hpp>
#include <Data.DBXMSSQL.hpp>
#include <Data.SqlExpr.hpp>
#include <Data.FMTBcd.hpp>
#include <Vcl.Grids.hpp>
#include "uLista.h"

//-------------------------------------------------------

class TfrmCadInst : public TForm{


__published:	// IDE-managed Components
	TOpenPictureDialog *abrir;
	TBitBtn *btnGravar;
	TLabel *lbImagem;
	TBitBtn *btnRemove;
	TEdit *TeditNome;
	TSQLConnection *conexao;
	TSQLQuery *SQLQuery;
	TBitBtn *btnUsar;
	TBitBtn *btnEditar;
	TLabel *Label1;
	TLabel *Label3;
	TPanel *plnPrincipal;
	TBitBtn *btnLogo;
	void __fastcall btnGravarClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall btnUsarClick(TObject *Sender);
	void __fastcall btnRemoveClick(TObject *Sender);
	void __fastcall btnLogoClick(TObject *Sender);
	void __fastcall btnEditarClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmCadInst(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCadInst *frmCadInst;
//---------------------------------------------------------------------------
#endif
