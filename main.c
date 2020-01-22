#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _LINUX
#ifdef _LINUX
  #include <dlfcn.h>
  #include <unistd.h>
#else
  #include <windows.h>  
#endif
#define false                           0
#define true                            (!false)
/*
 *  Tipos de dados
 */
#ifdef _LINUX
typedef char * HINSTANCE;
typedef unsigned int HANDLE;
  #define __stdcall
  #define SleepEx(x,y)                    sleep (((x) < 1000)? 1 : ((x) / 1000))
#endif

#define CALLBACK __stdcall

char *pEmpresa; 
char *pTerminal;
char *pIpSiTef;
char *pDataFiscal;
char *pHoraFiscal = "170000";
char *pCupom ;
unsigned short TamanhoMinimo = 0;
unsigned short TamanhoMaximo = 0; 

void finalizarAplicacaoGTK();
void DestruirTela();
int ContinuaSitef(char *comando); 

void atualizarTransacaoBanco(char *pCupom, char *pDataFiscal, char *pHoraFiscal, char *Valor, char * BANDEIRA,  char *NSU , char *BufferBanco);
#include "incs/treeviewGlade.h" 
#include "incs/telaInicialGlade.h"  
#include "incs/treeview.h" 
#include "incs/sitef.h"
#include "incs/ini.h" 
#include "incs/mysql_connect.h"




typedef struct
{
	const char* ipServer;
	const char* codLoja;
	const char* codPDV;
} configuration;



static int handler(void* user, const char* section, const char* name,const char* value)
{
	configuration* pconfig = (configuration*)user;
    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
	if (MATCH("CONFIGURACAO", "ipServer")) {

		pconfig->ipServer = strdup(value);
	} else if (MATCH("CONFIGURACAO", "codLoja")) {
		pconfig->codLoja = strdup(value);
	} else if (MATCH("CONFIGURACAO", "codPDV")) {
		pconfig->codPDV = strdup(value);
	} else {
        return 0;  /* unknown section/name, error */
	}

	return 1;
}

void quit_app(){
	gtk_main_quit();
}
void DestruirTela(){
	AbortarSitef();
	gtk_main_quit();
} 

	

	void finalizarAplicacaoGTK(){
		g_timeout_add(250,(GSourceFunc)quit_app,NULL); 
	}

	int main(int argc, char *argv[]) {

		iniFileTerminal = (argv[1]);

	//Primeiro argumento = IP
	//Segundo Argumento = ID Empresa
	//Terceiro Argumento terminal
	//Quarto argumento Cupom fiscal
	//Quinto argumento DataFiscal
	//Sexto argumento Valor sem separador decimal
	//Argumento -h MOSTRA AS INFOS
		configuration config;

		if (ini_parse(iniFileTerminal, handler, &config) < 0) {
			printf("Can't load 'test.ini'\n");
			return 1;
		}else{
			printf("Arquivo Lido : ipServer=%s, codLoja=%s, codPDV=%s\n",
				config.ipServer, config.codLoja, config.codPDV);
		}
		pIpSiTef = config.ipServer;
		pEmpresa = config.codLoja;
		pTerminal = config.codPDV;
		executarBancoDeDados();
		acao = (argv[2]);
		pCupom = (argv[3]);
		pDataFiscal= (argv[4]);
		pHoraFiscal= (argv[5]);
			strcpy (Valor,(argv[6]));
		strcpy(destino001,argv[7]);
		strcpy(destinoSTS,argv[7]);
		printf("DESTINO 001 %s\n",destino001);
		printf("Destino STS %s\n",destinoSTS);
		strcat(destino001,ARQUIVO_RESPOSTA);
		strcat(destinoSTS,ARQUIVO_STS);
		printf("DESTINO 001 %s\n",destino001);
                printf("Destino STS %s\n",destinoSTS);

		remove(destino001);
		remove(destinoSTS);
		if(strcmp(acao,"CRT") == 0){
			acaoSitef = 0 ;
		}else if(strcmp(acao,"CRTD") == 0){
			acaoSitef = 2;
		}else if(strcmp(acao,"CRTC") == 0){ 
			acaoSitef = 3 ;   
		}else if(strcmp(acao,"ADM")  == 0){
			acaoSitef = 110;
		}
		else{
			acaoSitef = 0 ;
		}   
		if(acaoSitef != 110){

			IniciarTransacaoBanco(pDataFiscal,pHoraFiscal , pCupom);
		}
		gtk_init(&argc, &argv);     
		TelaInicial();
		gtk_main();
		return 0;
	}
