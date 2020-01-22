#include "libs_call.h"

int nVezes;
char Buffer[20 * 1024 + 1];
char BufferBanco[20 * 1024 + 1];
const char *Mostrador = "|/-\\";
unsigned int IndiceMostrador = 0;
#define NUMBER_OF_STRING 5501
#define MAX_STRING_SIZE 400
#define ARQUIVO_RESPOSTA "IntPos.001"
#define ARQUIVO_STS "IntPos.Sts"
int Sts;
int ProximoComando = 0;
unsigned long TipoCampo = 0;

int Resultado = 0;
char sitefConf[20];
char Valor[20 + 1];
char Restricoes[2048 + 1];

int acaoSitef;
char *acao;
char *iniFileTerminal;
char *fDestinoArquivoSitef;
char destino001[200];
char destinoSTS[200];
GtkWidget *dialog;
char BUFFTEF[NUMBER_OF_STRING][MAX_STRING_SIZE] = {};

void finalizarAplicacaoGTK();

void escrever_mensagem_operador(int Comando, char *msg)
{

	if (msg != "")
	{
		MostrarTelaInicial(0, "");
		gtk_label_set_text(GTK_LABEL(labelInicial), msg);
	}
	else
	{
		gtk_label_set_text(GTK_LABEL(labelInicial), "Aguarde o processamento");
		EscondeTelaInicial();
	}

	while (gtk_events_pending())
	{
		gtk_main_iteration();
	}
	//printf("[%i]  - %s\n",  Comando , msg);
}
int iniciarSitef(char *pSitef, char *pEmpresa, char *pTerminal)
{
	int Sts = ConfiguraIntSiTefInterativo(pIpSiTef, pEmpresa, pTerminal, 0);
}

int LeCampo(short TamMinimo, short TamMaximo, char *pMensagem, char *pCampo)
{

	printf("%s\n", pMensagem);
	printf("%s\n", pCampo);
	return (0);
}

int RotinaColeta(int Comando, unsigned long TipoCampo,
				 unsigned short *TamanhoMinimo, unsigned short TamanhoMaximo,
				 unsigned char *pDadosComando, unsigned char *pCampo)
{
	char c;

	if (Comando != 23)
		nVezes = 0;
	switch (Comando)
	{
	case 1:
	case 2:
	case 3:
	case 4:
		escrever_mensagem_operador(Comando, pDadosComando);
		return (0);
	case 11:
	case 12:
	case 13:
	case 14:
		escrever_mensagem_operador(Comando, "Aguarde o processamento......");
		return (0);
	case 37:
	//fprintf (stderr, "\nColeta confirmacao no PinPad:");
	case 20:
		dialog = gtk_message_dialog_new(GTK_WINDOW(treeviewWindow),
										GTK_DIALOG_DESTROY_WITH_PARENT,
										GTK_MESSAGE_INFO,
										GTK_BUTTONS_OK_CANCEL,
										pDadosComando);
		int response = gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
		if (response == -5)
		{
			Buffer[0] = '\0';
			sprintf(Buffer, "%s", "0");
			TipoCampo = 0;
		}
		else
		{
			Buffer[0] = '\0';
			sprintf(Buffer, "%s", "1");
		}
		printf("response was %d (OK=%d, DELETE_EVENT=%d)\n",
			   response, GTK_RESPONSE_OK, GTK_RESPONSE_DELETE_EVENT);
		return (0);
	case 21:
		MenuTreeview(pDadosComando, pCampo);
		return (0);
	case 22:
		escrever_mensagem_operador(Comando, pDadosComando);
		return (0);
	case 23:
		SleepEx(1000, false);
		fprintf(stderr, "\r%c [%d]", Mostrador[IndiceMostrador], ++nVezes);
		if (++IndiceMostrador == strlen(Mostrador))
			IndiceMostrador = 0;
		if (nVezes > 30)
			return (0);
		return (0);

	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	case 38:
		//fprintf(stderr, "\nComando: %d, TipoCampo: %d", Comando, TipoCampo);
		//fprintf(stderr, "TamanhoMinimo: %d, TamanhoMaximo: %d pCampo: %s , pDadosComando %s", TamanhoMinimo, TamanhoMaximo, pDadosComando, pCampo);
		MostrarTelaInicial(1, pCampo);
		return 0;
		//return (LeCampo(*TamanhoMinimo, TamanhoMaximo, pDadosComando, pCampo));
	}

	return (-1);
}

void SalvarResposta(const char BUFFTEF[NUMBER_OF_STRING][MAX_STRING_SIZE], int resposta)
{
	char delim[] = "\n";
	char *ptr = "";
	char str[1024];
	int length = 0;
	FILE *file_ptr = fopen(destino001, "w");
	FILE *file_ptr_sts;
	char BANDEIRA[100];
	char NSU[10];
	if (resposta == 0)
	{
		file_ptr_sts = fopen(destinoSTS, "w");
	}
	fprintf(file_ptr, "%s = %s\n", "000-000", acao);
	for (int i = 0; i < NUMBER_OF_STRING; i++)
	{
		if (strlen(BUFFTEF[i]) > 0)
		{
			fprintf(file_ptr, "%i = %s\n", i, BUFFTEF[i]);
			length+= sprintf(BufferBanco+length,  "%i = %s\n", i, BUFFTEF[i]);
			if (resposta == 0)
			{
				fprintf(file_ptr_sts, "%i = %s\n", i, BUFFTEF[i]);
			}

if(i == 133){
					if (strlen(BUFFTEF[i]) > 0){
				strcpy(NSU, BUFFTEF[i]);
					}
			}

			if(i == 135){
					if (strlen(BUFFTEF[i]) > 0){
				strcpy(NSU, BUFFTEF[i]);
					}
			}
			if (i == 30)
			{
				fprintf(file_ptr, "%s = %s\n", "030-000", BUFFTEF[i]);
				length+= sprintf(BufferBanco+length, "%s = %s\n", "030-000", BUFFTEF[i]);

				if (resposta == 0)
				{
					fprintf(file_ptr_sts, "%s = %s\n", "030-000", BUFFTEF[i]);
				}
			}
			if (i == 156)
			{
				fprintf(file_ptr, "%s = %s\n", "010-000", BUFFTEF[i]);
				strcpy(BANDEIRA, BUFFTEF[i]);
				length+= sprintf(BufferBanco+length, "%s = %s\n", "010-000", BUFFTEF[i]);
				if (resposta == 0)
				{
					fprintf(file_ptr_sts, "%s = %s\n", "010-000", BUFFTEF[i]);
				}
			}
			else if (i == 9)
			{
				fprintf(file_ptr, "%s = %s\n", "009-000", BUFFTEF[i]);
				length+= sprintf(BufferBanco+length, "%s = %s\n", "009-000", BUFFTEF[i]);
				if (resposta == 0)
				{
					fprintf(file_ptr_sts, "%s = %s\n", "009-000", BUFFTEF[i]);
				}
			}
			else if (i == 121)
			{
				ptr = strtok(BUFFTEF[i], delim);
				while (ptr != NULL)
				{
					fprintf(file_ptr, "%s = %s\n", "VIA1", ptr);
					length+= sprintf(BufferBanco+length, "%s = %s\n", "VIA1", ptr);
					ptr = strtok(NULL, delim);
				}
				fprintf(file_ptr, "%s = %s\n", "VIA1", "\n\n\n\n");
					length+= sprintf(BufferBanco+length, "%s = %s\n", "VIA1", "\n\n\n\n");
			}
			else if (i == 122)
			{
				fprintf(file_ptr, "%s = %s\n", "VIA1", "\n\n\n\n\n\n");
				length+= sprintf(BufferBanco+length, "%s = %s\n", "VIA1", "\n\n\n\n");
				fprintf(file_ptr, "%s = %s\n", "CORTAPAPEL", "SIM");
				length+= sprintf(BufferBanco+length, "%s = %s\n", "CORTAPAPEL", "SIM");
				fprintf(file_ptr, "%s = %s\n", "VIA2", "\n\n\n\n\n\n");
				length+= sprintf(BufferBanco+length, "%s = %s\n", "VIA2", "\n\n\n\n\n\n");

				ptr = strtok(BUFFTEF[i], delim);
				while (ptr != NULL)
				{
					fprintf(file_ptr, "%s = %s\n", "VIA2", ptr);
					length+= sprintf(BufferBanco+length,"%s = %s\n", "VIA2", ptr);
					ptr = strtok(NULL, delim);
				}
			}
		}


		
	}
	fprintf(file_ptr, "%s = %.2f\n", "003-000", (float)atoi(Valor) / (float)100);
		length+= sprintf(BufferBanco+length,"%s = %.2f\n", "003-000", (float)atoi(Valor) / (float)100);
	if (resposta == 0)
	{
		fprintf(file_ptr_sts, "%s = %.2f\n", "003-000", (float)atoi(Valor) / (float)100);
		fclose(file_ptr_sts);
	}
	fclose(file_ptr);
	atualizarTransacaoBanco(pCupom,pDataFiscal,pHoraFiscal, Valor,BANDEIRA,NSU,BufferBanco);

}

void AbortarSitef()
{

	char delim[] = "\n";
	char *ptr = "";

	FILE *file_ptr = fopen(destino001, "w");
	FILE *file_ptr_sts;
	file_ptr_sts = fopen(destinoSTS, "w");
	fprintf(file_ptr, "%s = %s\n", "000-000", acao);
	//fprintf(file_ptr, "%s = %s\n", "009-000", "1");
	fprintf(file_ptr, "%s = %s\n", "030-000", "CANCELADO POR FALTA DE COMUNICAÇÃO");
	fclose(file_ptr);

	fprintf(file_ptr_sts, "%s = %s\n", "000-000", acao);
	fprintf(file_ptr_sts, "%s = %s\n", "009-000", "1");
	fprintf(file_ptr_sts, "%s = %s\n", "030-000", "CANCELADO POR FALTA DE COMUNICAÇÃO");
	fclose(file_ptr_sts);
}

int RotinaResultado(unsigned long TipoCampo, unsigned char *pResultado)
{
	char Retorno[5 + 1];
	strcpy(BUFFTEF[TipoCampo], pResultado);
	printf("%i = %s\n" , TipoCampo , pResultado );
	return (0);
}

int ChamaDll(int Tipo)
{
	*Restricoes = '\0';
	Sts = IniciaFuncaoSiTefInterativo(acaoSitef, Valor, pCupom, pDataFiscal, pHoraFiscal, pTerminal, Restricoes);
	return (Sts);
}

int ContinuaSitef(char *comando)
{

	int confirmar = 1;
	if (strcmp(comando, "-1") != 0)
	{

		//printf(" VEM DE BUFFER PROXIMO COMANDO BUFFER: %s\n", comando);
		Buffer[0] = '\0';
		sprintf(Buffer, "%s", comando);
	}

	Sts = ContinuaFuncaoSiTefInterativo(&ProximoComando, &TipoCampo, &TamanhoMinimo, &TamanhoMaximo, Buffer, sizeof(Buffer), Resultado);
	printf("Proximo: %i - Tipo: %i = Sts %i\n", ProximoComando, TipoCampo, Sts);
	if (Sts != 10000)
	{

		if (Sts == 0)
		{

			//printf("TAMANHO DO BUFFER %s = %i\n", BUFFTEF[121], strlen(BUFFTEF[121]));
			if (strlen(BUFFTEF[121]) > 0)
			{
				strcpy(BUFFTEF[30], " ");
				strcpy(BUFFTEF[9], "0");

				confirmar = 1;
			}
			else
			{
				confirmar = 0;
				strcpy(BUFFTEF[30], Buffer);
			}

			printf("FINALIZADO SISTEMA COMPLETO \n\n\n\n");
			printf("RESULTADO = %s\n\n\n" , BUFFTEF);
			FinalizaTransacaoSiTefInterativo(confirmar, pCupom, pDataFiscal, "170000");
			
			
			
			SalvarResposta(BUFFTEF, confirmar);
			finalizarAplicacaoGTK();
		}
		else
		{

			return -1;
		}
	}
	if (ProximoComando == 0)
	{
		Resultado = RotinaResultado(TipoCampo, Buffer);
	}
	else
	{
		Resultado = RotinaColeta(ProximoComando, TipoCampo, &TamanhoMinimo, TamanhoMaximo, Buffer, Buffer);
		//printf("Resultado do comando %i : %i\n", ProximoComando, Resultado);
	}
	if (ProximoComando == 21 || ProximoComando == 30 || ProximoComando == 31 || ProximoComando == 32 || ProximoComando == 33 || ProximoComando == 34 || ProximoComando == 35 || ProximoComando == 38)
	{
		//printf("RETORNOU OU 21 ou 30\n ");
		Sts = -1;
		Resultado = 0;
		return Sts;
	}
	if (Resultado == -1)
	{
		Sts = -1;
	}
	if (ProximoComando == 22 && TipoCampo == -1)
	{

		//printf("TAMANHO DO BUFFER %s = %i\n", BUFFTEF[121], strlen(BUFFTEF[121]));
		if (strlen(BUFFTEF[121]) > 0)
		{
			strcpy(BUFFTEF[30], " ");
			strcpy(BUFFTEF[9], "0");

			confirmar = 1;
		}
		else
		{
			confirmar = 0;
			strcpy(BUFFTEF[30], Buffer);
		}
		printf("FINALIZANDO O CUPOM SITEF FIDELIDADE %i\n", atoi(pCupom));


	
		FinalizaTransacaoSiTefInterativo(confirmar, pCupom, pDataFiscal, "170000");
		SalvarResposta(BUFFTEF, confirmar);
		finalizarAplicacaoGTK();
	}
	return Sts;
}
