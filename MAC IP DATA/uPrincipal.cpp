//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "uPrincipal.h"
#include <SysUtils.hpp>
#include <windows.h>
#include <iphlpapi.h>
#include <string>
#include <windows.h>
#include <iphlpapi.h>
#include <System.SysUtils.hpp>
#include <winsock.h>
#include <sstream>

#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "wsock32.lib")


TForm1 *Form1;



UnicodeString GetLocalIP();
AnsiString GetIpMachine();
AnsiString GetMACAddress();

__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}


void __fastcall TForm1::FormCreate(TObject *Sender)
{

	// teste
        TDateTime dt = Now();
        AnsiString dtStr = FormatDateTime("dd/mm/yyyy hh:nn:ss", dt);

         lbDate->Caption = dtStr;
         lbModulo->Caption = GetMACAddress();
         //Edit1->Text = GetLocalIP();
         Edit1->Text = GetIpMachine();

}




UnicodeString GetLocalIP()
{
    IP_ADAPTER_INFO* pAdapterInfo = NULL;
    ULONG ulOutBufLen = 0;

    // Obter o tamanho necessário do buffer
    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW)
    {
        // Alocar o buffer com o tamanho necessário
        pAdapterInfo = reinterpret_cast<IP_ADAPTER_INFO*>(new BYTE[ulOutBufLen]);

        // Obter as informações dos adaptadores de rede
        if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == NO_ERROR)
        {
            IP_ADAPTER_INFO* pAdapter = pAdapterInfo;

            while (pAdapter)
            {
                if (pAdapter->IpAddressList.IpAddress.String[0] != '\0')
                {
                    // Retornar o primeiro endereço IP encontrado
                    std::string ipAddress = pAdapter->IpAddressList.IpAddress.String;
                    delete[] reinterpret_cast<BYTE*>(pAdapterInfo);
                    return UnicodeString(ipAddress.c_str());
                }

                pAdapter = pAdapter->Next;
            }
        }
    }

    delete[] reinterpret_cast<BYTE*>(pAdapterInfo);
    return L"";
}






AnsiString GetIpMachine()
{
    WSADATA wsaData;
    WSAStartup(0x0101, &wsaData);

    hostent* pHostEnt = gethostbyname("");
    in_addr** pAddressList = reinterpret_cast<in_addr**>(pHostEnt->h_addr_list);

    AnsiString ipAddress = inet_ntoa(*pAddressList[0]);

    WSACleanup();

    return ipAddress.Trim();
}




AnsiString GetMACAddress()
{
    IP_ADAPTER_INFO* pAdapterInfo = NULL;
    ULONG ulOutBufLen = 0;

    // Obter o tamanho necessário do buffer
    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW)
    {
        // Alocar o buffer com o tamanho necessário
        pAdapterInfo = reinterpret_cast<IP_ADAPTER_INFO*>(new BYTE[ulOutBufLen]);

        // Obter as informações dos adaptadores de rede
        if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == NO_ERROR)
        {
            IP_ADAPTER_INFO* pAdapter = pAdapterInfo;

            while (pAdapter)
            {
                if (pAdapter->AddressLength > 0)
                {
                    std::stringstream ss;
                    for (DWORD i = 0; i < pAdapter->AddressLength; i++)
                    {
                        if (i > 0)
                            ss << ":";

                        ss << std::hex << static_cast<int>(pAdapter->Address[i]);
                    }

                    delete[] reinterpret_cast<BYTE*>(pAdapterInfo);
                    return AnsiString(ss.str().c_str());
                }

                pAdapter = pAdapter->Next;
            }
        }
    }

    delete[] reinterpret_cast<BYTE*>(pAdapterInfo);
    return "";
}





/*

TStringList* GetLocalIP()
{
    IP_ADAPTER_INFO* pAdapterInfo = NULL;
    ULONG ulOutBufLen = 0;

    TStringList* ipList = new TStringList();

    // Obter o tamanho necessário do buffer
    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW)
    {
        // Alocar o buffer com o tamanho necessário
        pAdapterInfo = reinterpret_cast<IP_ADAPTER_INFO*>(new BYTE[ulOutBufLen]);

        // Obter as informações dos adaptadores de rede
        if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == NO_ERROR)
        {
            IP_ADAPTER_INFO* pAdapter = pAdapterInfo;

            while (pAdapter)
            {
                if (pAdapter->IpAddressList.IpAddress.String[0] != '\0')
                {
                    // Adicionar o endereço IP à lista
                    std::string ipAddress = pAdapter->IpAddressList.IpAddress.String;
                    ipList->Add(UnicodeString(ipAddress.c_str()));
                }

                pAdapter = pAdapter->Next;
            }
        }
    }

    delete[] reinterpret_cast<BYTE*>(pAdapterInfo);
    return ipList;
}

*/
