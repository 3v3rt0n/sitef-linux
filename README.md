# sitef
 É necessário instalar o gtk2  "apt-get ou yum install gtk2-devel "

depois alterar o make.sh da pasta para o destino do binário no seu sistema

depois é só executar esse comando de teste

./make.sh
./sitef config_sitef.ini  CRT 123 14062019 180000 329 /usr/local/share/files/Resp/
o Clisitef.ini deste sistema está como homologação, entao precisa trocar para o seu específico


ONDE:
1 - Parametro = Um arquivo ini que configura o ip do sitef , o nome do equipamento e o numero da loja
2- Parametro = TIPO {
CRT  - Escolhe no fluxo se é  debito ou credito
CRTD - Entra direto no fluxo do debito
CRTC - Entra direto no fluxo do credito
ADM  - Entra no fluxo do ADM
}

3 - Parametro = Numero do cupom vinculado (caso nao use coloque 0 )
4 - Parametro = Data em formato ddmmyyyy
5 - Parametro = Hora em formato hhmmss
6 - Parametro = Valor absoluto (sem virgulas ou ponto, no caso do exemplo o valor é 3,29)
7 - Parametro = Destino do arquivo de retorno do sitef, pois no caso estamos utilizando transferencia de arquivo para poder ser compativel com todos os sistemas (
vide IntPos.001_*  para ver as respectivas RESPOSTAS do sistema 

)


