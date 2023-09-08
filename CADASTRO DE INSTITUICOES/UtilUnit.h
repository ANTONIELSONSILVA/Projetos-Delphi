//---------------------------------------------------------------------------

#ifndef UtilUnitH
#define UtilUnitH
//---------------------------------------------------------------------------
#include <Forms.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>
#include <IniFiles.hpp>
#include "Character.hpp"

int AutoSizeStringGrid(TStringGrid *StrGrid, int col, int linha);
TStringList *listaArquivos(String caminho, String tipo);
char* StringParaChar(String origem);
String LeUmCampoIni(String secao, String campo,String padrao="");
float LeUmCampoIniFloat(String secao, String campo,float padrao=0);
void GravaUmCampoIni(String secao, String campo, String valor="");
void PintaStringGrid(TStringGrid *StrGrid, int col, int linha, TRect &Rect);
bool verificaSeEhNumero(String valor);
//fun��o que retorna diret�rio padr�o
String diretorioPadraoExpRelatorios( );

//fun��o que recebe um diretorio, compara com diret�rio atual de exportacao de relat�rios e grava
//se for diferente
void gravaDiretorioPadraoExpRelatorios(String dirNovo);

void centralizaForm(TForm *formPrincipal, TForm *formFilho);

//template <typename T, int S>

#endif
