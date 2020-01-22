
extern int (__stdcall ConfiguraIntSiTefInterativo) (char *pEnderecoIP, char *pCodigoLoja,	char *pNumeroTerminal,	short ConfiguraResultado);

extern int (__stdcall IniciaFuncaoSiTefInterativo) (int Modalidade, char *pValor,
	char *pNumeroCuponFiscal,
	char *pDataFiscal, char *pHorario,
	char *pOperador, char *pRestricoes);

extern int (__stdcall IniciaFuncaoAASiTefInterativo) (int Modalidade, char *pValor,
	char *pNumeroCuponFiscal,
	char *pDataFiscal, char *pHorario,
	char *pOperador, char *pRestricoes,
	char *pProdutos);

extern int (__stdcall DesfazTransacaoSiTefInterativo) (char *pDadosDesfazimento);

extern int (__stdcall FuncoesGerenciaisSiTefInterativo) (char *pNumeroCuponFiscal,
	char *pDataFiscal, char *pHorario,
	char *pOperador);

extern int (__stdcall IniciaCancelamentoIdentificadoSiTefInterativo) (char *pNumeroCuponFiscal,
	char *pDataFiscal, char *pHorario,
	char *pOperador, char *pChaveTrnCancelamento);

extern int (__stdcall CorrespondenteBancarioSiTefInterativo) (char *pNumeroCuponFiscal,
	char *pDataFiscal, char *pHorario,
	char *pOperador, char *pRestricoes);

extern int (__stdcall ValidaCampoCodigoEmBarras) (char *pCodigoEmBarras, short *pTipo);

extern void (__stdcall FinalizaTransacaoSiTefInterativo) (short Confirma, 
	char *pNumeroCuponFiscal,
	char *pDataFiscal, char *pHorario);

extern void (__stdcall FinalizaTransacaoSiTefInterativoBonus) (short Confirma, char *pNumeroCuponFiscal,
	char *pDataFiscal, char *pHorario,
	char *pValorTotalCupon, char *pValorTotalBonus);

extern int (__stdcall ContinuaFuncaoSiTefInterativo) (int *pProximoComando, unsigned long *pTipoCampo,
	unsigned short *pTamanhoMinimo, unsigned short *pTamanhoMaximo,
	char *pBuffer, int TamMaxBuffer, int ContinuaNavegacao);

extern int (__stdcall EnviaRecebeSiTefDireto) (short RedeDestino, short FuncaoSiTef, short OffsetCartao,
	char *pDadosTx, short TamDadosTx, 
	char *pDadosRx, short TamMaxDadosRx, short *pCodigoResposta, 
	short TempoEsperaRx, char *pNumeroCupon, char *pDataFiscal, 
	char *pHorario, char *pOperador, short TipoTransacao);

extern int (__stdcall ForneceParametroEnviaRecebeSiTefDireto) (short IndiceParametro, char *pParametro, 
	short ParametroCartao, short Delimitador);
extern void (__stdcall ForneceParametroEnviaRecebeSiTefDiretoA) (char *pResultado, char *pIndiceParametro, 
	char *pParametro, char *pParametroCartao, 
	char *pDelimitador);

extern int (__stdcall LeCartaoInterativo) (char *pMsgDisplay);

extern int (__stdcall LeCartaoDireto) (char *pMsgDisplay, char *pTrilha1, char *pTrilha2);

extern int (__stdcall LeCartaoDiretoEx) (char *pMsgDisplay, char *pTrilha1, char *pTrilha2,
	unsigned short Timeout,
	short (CALLBACK *pTestaCancelamento) (void));

extern int (__stdcall LeSenhaDireto) (char *pChaveSeguranca, char *pSenha);

extern int (__stdcall VerificaPresencaPinPad) (void);

extern int (__stdcall SEObtemChaveSeguranca) (char *pChaveSeguranca,
	char *pCartao, char *pChaveAbertura,
	char *pResultado);

extern int (__stdcall SEObtemSenhaCliente) (char *pSenhaAberta, char *pSenhaCapturada, 
	char *pChaveSeguranca, char *pChaveAbertura,
	char *pResultado);

extern int (__stdcall AbrePinPad) (void);
extern int (__stdcall FechaPinPad) (void);
extern int (__stdcall EscreveMensagemPinPad) (char *pMsgDisplay);
extern int (__stdcall EscreveMensagemPermanentePinPad) (char *pMsgDisplay);
extern int (__stdcall LeCampoPinPad) (char *pMsgDisplay, int TamMaximo, int eSenha, char *pCampo);
extern int (__stdcall LeTeclaPinPad) (void);
extern int (__stdcall LeSimNaoPinPad) (char *pMsgDisplay);

extern int (__stdcall IniciaFuncaoSiTefInterativoConsultaVidalink) (char *pCodigoAutorizacao,
	char *pCodigoProduto,
	char *pNumeroCuponFiscal,
	char *pDataFiscal, char *pHorario,
	char *pOperador);
extern int (__stdcall InformaProdutoVendaVidalink) (short IndiceProduto,
	char *pCodigoProduto,
	short Quantidade,
	char *pValorVenda);
extern int (__stdcall IniciaFuncaoSiTefInterativoVendaVidalink) (char *pCodigoAutorizacao,
	short NumeroProdutos,
	char *pNumeroCuponFiscal,
	char *pDataFiscal, char *pHorario,
	char *pOperador);
extern int (__stdcall IniciaFuncaoSiTefInterativoCancelamentoVidalink) (short ParcialTotal,
	short NumeroProdutos,
	char *pNumeroCuponOriginal,
	char *pDataOriginal,
	char *pNumeroDocumentoOriginal,
	char *pIdentificacaoPdvOriginal,
	char *pCuponFiscal,
	char *pDataFiscal, char *pHorario,
	char *pOperador);

extern int (__stdcall IniciaFuncaoSiTefInterativoConsultaPBM) (char *pCodigoAutorizacao,
	char *pCodigoProduto,
	char *pNumeroCuponFiscal,
	char *pDataFiscal, char *pHorario,
	char *pOperador, char *pParametrosAdicionais);

extern int (__stdcall ConsultaParametrosSiTef) (int TipoConsulta, char *Reservado, char *Saida);
extern int (__stdcall RegistraBonusOffLineSiTef) (char *ValorBonus, char *ValorCupom,
	char *NumeroCuponFiscal, char *DataFiscal, 
	char *Horario, char *Operador, char *Supervisor);

extern void (__stdcall FinalizaFuncaoSiTefInterativo) (short Confirma, char *pNumeroCuponFiscal,
	char *pDataFiscal, char *pHorario, 
	char *pParametrosAdicionais);

extern int (__stdcall ObtemParametrosSiTef) (int TipoConsulta, char *pParamAdic);