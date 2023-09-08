//---------------------------------------------------------------------------


#pragma hdrstop

#include "UtilUnit.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)



int AutoSizeStringGrid(TStringGrid *StrGrid, int col, int linha)
{
	int largura;

	largura = StrGrid->Canvas->TextWidth(StrGrid->Cells[col][linha]);
	StrGrid->ColWidths[col] = largura = largura + 5;
    return largura;
}

//fun��o para gerar efeito zebrado ao gerar stringgrid
void PintaStringGrid(TStringGrid *StrGrid, int col, int linha, TRect &Rect)
{
	 if(linha > 0) //linhas de dados
	 { // testa se n�o � a primeira linha (fixa)
		 if((linha % 2) == 0)
		 { // verifica se a linha � par
         	StrGrid->Canvas->Font->Color = clBlack;
			StrGrid->Canvas->Brush->Color = clGradientInactiveCaption;//cor de fundo
		 }
	 }
	 else //linha de t�tulo
	 {
		 StrGrid->Canvas->Brush->Color = clBtnFace;
	 }
	 if (StrGrid->Canvas->TextWidth(StrGrid->Cells[col][linha]) > StrGrid->ColWidths[col])
	 {
		StrGrid->ColWidths[col] = StrGrid->Canvas->TextWidth(StrGrid->Cells[col][linha]) + 4;
	 }
	 StrGrid->Canvas->Font->Color = clBlack;
	 StrGrid->Canvas->FillRect(Rect); // redesenha a celula
	 SetTextAlign(StrGrid->Canvas->Handle,TA_CENTER|VTA_CENTER);
	 StrGrid->Canvas->TextOut(Rect.Left+ ((Rect.Right-Rect.Left)/2),Rect.Top,StrGrid->Cells[col][linha]); // reimprime  o texto.
}


//---------------------------------------------------------------------------
TStringList *listaArquivos(String caminho, String tipo)
{
	TStringList *resultado = new TStringList();
	TSearchRec sr;
	if(FindFirst(caminho.Trim() +"*."+tipo.Trim(), faAnyFile, sr) == 0)
	{
		resultado->Add(sr.Name);//necess�rio para leitura do primeiro arquivo
		while(FindNext(sr) == 0)
		{
		 resultado->Add(sr.Name);
        }
	}
	return resultado;
}

//---------------------------------------------------------------------------
//fun��o que converte string para array de char, necess�ria devido a bug durante convers�o
//para messagebox
char* StringParaChar(String origem)
{
	char *aux = new char[Trim(origem).Length()+1];
	for(int i = 1;i <= origem.Length( );i++)
		aux[i-1] = origem[i];
	aux[origem.Length()]='\0';
	return aux;
}

//---------------------------------------------------------------------------
//fun��o para ler um campo de arquivo INI, recebe nome da se��o, nome do campoe valor padr�o (opcional)
//retorna valor do campo
String LeUmCampoIni(String secao, String campo,String padrao)
{
	TIniFile *pArq = new TIniFile(ExtractFileDir(Application->ExeName)+"\\Easy.ini");
	String aux = pArq->ReadString(secao,campo,padrao);
	pArq->~TIniFile( );
	return  aux.Trim( );
}

float LeUmCampoIniFloat(String secao, String campo,float padrao)
{
	TIniFile *pArq = new TIniFile(ExtractFileDir(Application->ExeName)+"\\Easy.ini");
	float aux = pArq->ReadFloat(secao,campo,padrao);
	pArq->~TIniFile( );
	return  aux;
}

//fun��o para gravar um campo no arquivo INI, recebe nome da se��o, nome do campoe valor padr�o (opcional)
//retorna true se gravar
void GravaUmCampoIni(String secao, String campo, String valor)
{
	TIniFile *pArq = new TIniFile(ExtractFileDir(Application->ExeName)+"\\Easy.ini");
	pArq->WriteString(secao,campo,valor.Trim());
	pArq->~TIniFile( );
}

//------------------------------------------------------------------------------

// Fun��o para verificar se a String � um n�mero, aceitando . e , entre os d�gitos
bool verificaSeEhNumero(String valor) {
	for (int i=1; i <= valor.Length(); i++)
	{
	  if((valor.SubString(i,1)==".") || (valor.SubString(i,1)==",")) //Pula se o caractere corrente for . ou ,
	  {
		continue;
	  }

	  if(IsNumber(valor, i) == false)
	  {
		return false;
	  }
	}
   return true;
}


//---------------------------------------------------------------------------

//Fun��o para pintar e centralizar formul�rio filho em rela��o ao Pai (formPrincipal)
void centralizaForm(TForm *formPrincipal, TForm *formFilho)
{
   formFilho->Left = (formPrincipal->Width/2) - (formFilho->Width/2);
   formFilho->Top = (formPrincipal->Height/2) - (formFilho->Height/2);
}

//---------------------------------------------------------------------------
//fun��o que pega diret�rio padr�o
String diretorioPadraoExpRelatorios( )
{
	return LeUmCampoIni("Configuracao","exporta_relatorio","");
}


//---------------------------------------------------------------------------
void gravaDiretorioPadraoExpRelatorios(String dirNovo)
{
	String dirAtual = LeUmCampoIni("Configuracao","exporta_relatorio","");
	if((dirAtual.Trim() != dirNovo.Trim()) && (dirNovo.Trim() != "" ))
	{
		TIniFile *pArq = new TIniFile(ExtractFileDir(Application->ExeName)+"\\Easy.ini");
		pArq->WriteString("Configuracao","exporta_relatorio",dirNovo);
		pArq->~TIniFile( );
	}
}

//----------------------------------------------------------------------------
