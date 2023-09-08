#include <iostream>
#include <fstream>
#include <string>
#include <vcl.h>
#include <cstdlib>
#include <ctime>
#include <Jpeg.hpp>
#include <pngimage.hpp>
#include "uPrincipal.h"
#include "UtilUnit.h"

using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TStringGrid *grid;
TfrmCadInst *frmCadInst;


TBitmap *BmpImg = NULL;
TBitmap *BmpImg1 = new TBitmap();
TJPEGImage *JpgImg = NULL;
TPngImage *pngImg = NULL;
TListBox * lstEscolas;
TSQLConnection *SQLConnection2;
TMemoryStream *StreamImagem;
TOpenDialog *AbreLogo;
TBitmap** imagensDoBanco = NULL;
TBitmap *BmpImgGrid = new TBitmap();
TImage *imagem = new TImage(NULL);
int identificador = NULL;


//---------------------------------------------------------------------------
__fastcall TfrmCadInst::TfrmCadInst(TComponent* Owner)
	: TForm(Owner)
{
}


TMemoryStream* converteParaMemoryStream(TImage *imagem);
TSQLConnection* ConectaBD();


//---------------------------------------------------------------------------

void __fastcall TfrmCadInst::btnGravarClick(TObject *Sender){


		if(TeditNome->Text == ""){
           ShowMessage("Informe um nomo para a institui��o");
           return;
        }else if(imagem->Picture == NULL){
           ShowMessage("Selecione logo para a institui��o");
           return;
        }


	TSQLConnection* conexao = ConectaBD();

	if(conexao == NULL){
		ShowMessage("Falha ao conectar ao banco de dados");
	}

    // Cria o comando SQL INSERT com um par�metro do tipo image
	TSQLQuery* query = new TSQLQuery(NULL);
	query->SQLConnection = conexao;

	// Campo nome da tabela
	AnsiString nomeIntituicao = TeditNome->Text;

	// Campo imagem da tabela
	TMemoryStream* logo = converteParaMemoryStream(imagem);


	// se identificador for = null usar o comando INSERT, SE != NULL usar UPDATE.
	if(identificador == NULL){
		query->SQL->Text = "INSERT INTO dbo.INSTITUICAO(nomeIntituicao, logoIntituicao) VALUES ('" + nomeIntituicao + "' , Convert(varbinary(max),:logoInstituicao))";
		query->ParamByName("logoInstituicao")->LoadFromStream(logo, ftBlob);
	}else{	
		query->SQL->Text = "UPDATE dbo.INSTITUICAO SET nomeIntituicao = '" + nomeIntituicao + "', logoIntituicao = Convert(varbinary(max),:logoInstituicao) WHERE idInstifuicao = '" + identificador + "';";
		query->ParamByName("logoInstituicao")->LoadFromStream(logo, ftBlob);
	}


    try {
    	// Executa da query e limpa os dados dos componentes
        query->ExecSQL();
        ShowMessage("Gravado !");
        TeditNome->Text = "";
        imagem->Picture = NULL;

        // coloca novamente "sua logo aqui" no bot�o de imagem
		TBitmap* bitmap = new TBitmap();
		bitmap->LoadFromFile(ExtractFileDir(Application->ExeName)+"\\logo.bmp");

		// ajusta do �cone "sua logo aqui" ao tamanho do bot�o.
	    TBitmap* BmpImgAux = new TBitmap();
		BmpImgAux->Width = btnLogo->Width;
		BmpImgAux->Height = btnLogo->Height;
		BmpImgAux->Canvas->StretchDraw(TRect(0, 0, BmpImgAux->Width, BmpImgAux->Height), bitmap);
		btnLogo->Glyph = BmpImgAux;
		delete bitmap;
		delete BmpImgAux;

    }catch(...) {

        ShowMessage("Erro ao executar a query");

    }

		identificador = NULL;
		btnEditar->Caption = "Editar";
		btnUsar->Enabled = true;
		btnRemove->Enabled = true;
    	
    	delete conexao;
	    delete query;

	    // inicia o form novamente para que o mesmo retorne atualizado.
		TfrmLista *frmLista = dynamic_cast<TfrmLista*>(Application->MainForm->FindComponent("frmLista"));		
	   	delete frmLista;
	    frmLista = new TfrmLista(this);
	    frmLista->grid->Parent = plnPrincipal;
	    frmLista->grid->Align = alClient;

}



TMemoryStream* converteParaMemoryStream(TImage *imagemLogo){

	TMemoryStream* stream = new TMemoryStream();
	try {
	   imagemLogo->Picture->Bitmap->SaveToStream(stream);
	   return(stream);
	}
	catch(...){
	   ShowMessage("Erro ao criar o objeto Memory Stream");
	}

}


TSQLConnection* ConectaBD()
{

	TSQLConnection *SQLConnection2 = new TSQLConnection(NULL);
	SQLConnection2->ConnectionName = "MSSQLConnection";
	SQLConnection2->DriverName = "MSSQL";
	SQLConnection2->GetDriverFunc = "getSQLDriverMSSQL";
	SQLConnection2->KeepConnection = true;
	SQLConnection2->LibraryName = "dbxmss.dll";
	SQLConnection2->LoginPrompt = false;
	SQLConnection2->LoadParamsOnConnect = false;
	SQLConnection2->Name = "SQLConnection2";
	SQLConnection2->Tag = 0;
	SQLConnection2->VendorLib = "oledb";
	SQLConnection2->Params->Clear();
	SQLConnection2->Params->Append("DriverName=MSSQL");
	SQLConnection2->Params->Append("HostName=localhost\\KAPTUREALL");
	SQLConnection2->Params->Append("DataBase=Easy51");
	SQLConnection2->Params->Append("User_Name=sa");
	SQLConnection2->Params->Append("Password=K4ptur34ll");
	SQLConnection2->Params->Append("BlobSize=-1");
	SQLConnection2->Params->Append("ErrorResourceFile=");
	SQLConnection2->Params->Append("LocaleCode=0000");
	SQLConnection2->Params->Append("MSSQL TransIsolation=ReadCommited");
	SQLConnection2->Params->Append("OS Authentication=False");
	SQLConnection2->Params->Append("Prepare SQL=False");
	try
	{
		SQLConnection2->Connected = true;
		return SQLConnection2;
	}
	catch(Exception &ex)
	{
		delete SQLConnection2;
		return NULL;
	}

}

void __fastcall TfrmCadInst::FormCreate(TObject *Sender)
{


	frmLista = new TfrmLista(this);
	frmLista->grid->Parent = plnPrincipal;
    frmLista->grid->Align = alClient;
    frmLista->Color = clWebSteelBlue;

    // Cria um objeto TBitmap
	TBitmap* bitmap = new TBitmap();
	// Carrega a imagem BMP a partir de um arquivo
	bitmap->LoadFromFile(ExtractFileDir(Application->ExeName)+"\\logo.bmp");

    TBitmap* BmpImgAux = new TBitmap();

	BmpImgAux->Width = btnLogo->Width;
	BmpImgAux->Height = btnLogo->Height;
	BmpImgAux->Canvas->StretchDraw(TRect(0, 0, BmpImgAux->Width, BmpImgAux->Height), bitmap);
	btnLogo->Glyph = BmpImgAux;

	// Libera a mem�ria do objeto TBitmap
	delete bitmap;
	delete BmpImgAux;
    

}


void __fastcall TfrmCadInst::btnUsarClick(TObject *Sender)
{

	TfrmLista *frmLista = dynamic_cast<TfrmLista*>(Application->MainForm->FindComponent("frmLista"));

    AnsiString aux;
    TBitmap* BitmapParaCampoImagem = new TBitmap();

	int linhaSelecionada = frmLista->grid->Row;

	aux = frmLista->vetorLogos[linhaSelecionada].nome;
	BitmapParaCampoImagem = frmLista->vetorLogos[linhaSelecionada].bitmap;

    // salvar imagem como .bmp
    // e editar o arquivo Easy.ini
    TIniFile * pArq = new TIniFile(ExtractFileDir(Application->ExeName)+"\\Easy.ini");

    pArq->WriteString("Configuracao","NomeEscola",aux);

    delete pArq;

    BitmapParaCampoImagem->SaveToFile(ExtractFileDir(Application->ExeName) + "\\img\\logo.bmp");

    ShowMessage("Feito");

    delete BitmapParaCampoImagem;


}



//---------------------------------------------------------------------------
void __fastcall TfrmCadInst::btnRemoveClick(TObject *Sender)
{
	
	TfrmLista *frmLista = dynamic_cast<TfrmLista*>(Application->MainForm->FindComponent("frmLista"));

	// grid->Row retorno a linha seleciona que ser� deletada
 	int linhaSelecionada = frmLista->grid->Row;


 	// verifico na struct qual � o id do banco naquela linha 
 	int id = frmLista->vetorLogos[linhaSelecionada].id;

	// converto de int para string 
 	AnsiString idString = IntToStr(id);

 	// inicio a conex�o com o banco
	TSQLConnection* Conexao = ConectaBD();
    TSQLQuery *query = new TSQLQuery(NULL);
    query->SQLConnection = Conexao;

    // monto a query para deletar de acorde com o id selecionado
    query->SQL->Add("Delete from dbo.INSTITUICAO where idInstifuicao = " + idString);
    // executo a query
    query->ExecSQL();

    // libero os ponteiros
    delete query;
    delete Conexao;

   	delete frmLista;

    frmLista = new TfrmLista(this);
    frmLista->grid->Parent = plnPrincipal;
    frmLista->grid->Align = alClient;

}

void __fastcall TfrmCadInst::btnLogoClick(TObject *Sender)
{

	TBitmap* BmpImgAux = new TBitmap();

	BmpImgAux->Width = btnLogo->Width;
	BmpImgAux->Height = btnLogo->Height;



  	TOpenDialog *AbreLogo = new TOpenDialog(NULL);
	AbreLogo->Filter = "Imagem |*.bmp;*.jpg;*.png";
	AbreLogo->Execute( );


	if (AbreLogo->FileName.Trim( ) != "")
	{
		BmpImg = new TBitmap();
		BmpImg->Canvas->Brush->Style = bsClear;
		BmpImg->Transparent = true;
		if (ExtractFileExt(AbreLogo->FileName).UpperCase() == ".JPG")
		{
			JpgImg = new TJPEGImage();
			JpgImg->LoadFromFile(AbreLogo->FileName);
			BmpImg->Assign(JpgImg);
		}
		else if (ExtractFileExt(AbreLogo->FileName).UpperCase() == ".BMP")
		{
			BmpImg->LoadFromFile(AbreLogo->FileName);
		}
		else if (ExtractFileExt(AbreLogo->FileName).UpperCase() == ".PNG")
		{
			pngImg = new TPngImage( );
			pngImg->Transparent = true;
			//todos esses comandos para converter png em bitmap s�o necess�rios
			//porque algumas imagens em png ficavam com fundo preto ao converter
			pngImg->Canvas->Brush->Style = bsClear;
			pngImg->Canvas->Brush->Color = clWhite;
			pngImg->LoadFromFile(AbreLogo->FileName);
			pngImg->Transparent = true;
			BmpImg->Height = pngImg->Height;
			BmpImg->Width = pngImg->Width;
			BmpImg->Canvas->Brush->Style = bsSolid;
			BmpImg->Canvas->Brush->Color = clWhite;
			BmpImg->Canvas->FillRect(Rect(0,0,pngImg->Width,pngImg->Height));
			pngImg->Draw(BmpImg->Canvas,Rect(0,0,pngImg->Width,pngImg->Height));
			pngImg->RemoveTransparency();
		}

		BmpImgAux->Canvas->StretchDraw(TRect(0, 0, BmpImgAux->Width, BmpImgAux->Height), BmpImg);
		imagem->Picture->Bitmap = BmpImg;
		btnLogo->Glyph = BmpImgAux;
    	// deixa a imagem centralizada
    	imagem->Stretch = True;


	}

	//delete bitmap;
	delete BmpImgAux;


}
//---------------------------------------------------------------------------

void __fastcall TfrmCadInst::btnEditarClick(TObject *Sender)
{

	// Carregar o imagem da Row selecionada no Timage.
	// Carregar o nome da Institui��o no Tedit.
	// Carrega o id na vari�vel identificador
	// alterar o caption do bot�o Editar para cancelar
	// desativar os bot�es Usar e Remover
	// Para identificar a a��o do bot�o Editar/Cancelar, verificar a vari�vel "identificador"
	// se for null carrega os dados e desativa os bot�es e caption para cancelar
	// se != de null limpa os dados, ativa os bot�es e muda a caption para Editar.
	// colocar tamb�m as a��es no bot�o de grava para que depois de atualizar os dados,
	// tudo retorne como no inicio



	if(identificador == NULL){

		TBitmap *BmpAux = new TBitmap();
		TfrmLista *frmLista = dynamic_cast<TfrmLista*>(Application->MainForm->FindComponent("frmLista"));
	 	int linhaSelecionada = frmLista->grid->Row;

	 	BmpAux = frmLista->vetorLogos[linhaSelecionada].bitmap;
		TBitmap* BmpImgAux = new TBitmap();
		BmpImgAux->Width = btnLogo->Width;
		BmpImgAux->Height = btnLogo->Height;
		BmpImgAux->Canvas->StretchDraw(TRect(0, 0, BmpImgAux->Width, BmpImgAux->Height), BmpAux);
		btnLogo->Glyph = BmpImgAux;
		imagem->Picture->Bitmap = BmpImgAux;
		TeditNome->Text = frmLista->vetorLogos[linhaSelecionada].nome;

		identificador = frmLista->vetorLogos[linhaSelecionada].id;

		btnEditar->Caption = "Cancelar";

		btnUsar->Enabled = false;
		btnRemove->Enabled = false;


		//delete bitmap;
		delete BmpAux;
		delete BmpImgAux;


	}else{
		
		TBitmap* bitmap = new TBitmap();
		bitmap->LoadFromFile(ExtractFileDir(Application->ExeName)+"\\logo.bmp");
		// ajusta do �cone "sua logo aqui" ao tamanho do bot�o.
	    TBitmap* BmpImgAux = new TBitmap();
		BmpImgAux->Width = btnLogo->Width;
		BmpImgAux->Height = btnLogo->Height;
		BmpImgAux->Canvas->StretchDraw(TRect(0, 0, BmpImgAux->Width, BmpImgAux->Height), bitmap);
		btnLogo->Glyph = BmpImgAux;
		imagem->Picture->Bitmap = NULL;
		TeditNome->Text = "";

		identificador = NULL;
		btnEditar->Caption = "Editar";
		btnUsar->Enabled = true;
		btnRemove->Enabled = true;

		delete bitmap;
		delete BmpImgAux;
		

	}

}
