# sitef
 É necessário instalar o gtk2  "apt-get ou yum install gtk2-devel "<br />

depois alterar o make.sh da pasta para o destino do binário no seu sistema<br />

depois é só executar esse comando de teste<br /><br />

./make.sh <br />
./sitef config_sitef.ini  CRT 123 14062019 180000 329 /usr/local/share/files/Resp/<br />
o Clisitef.ini deste sistema está como homologação, entao precisa trocar para o seu específico<br />
<br />

ONDE:<br />
1 - Parametro = Um arquivo ini que configura o ip do sitef , o nome do equipamento e o numero da loja<br />
2- Parametro = TIPO {<br />
CRT  - Escolhe no fluxo se é  debito ou credito<br />
CRTD - Entra direto no fluxo do debito<br />
CRTC - Entra direto no fluxo do credito<br />
ADM  - Entra no fluxo do ADM<br />
}<br /><br />

3 - Parametro = Numero do cupom vinculado (caso nao use coloque 0 )<br />
4 - Parametro = Data em formato ddmmyyyy<br />
5 - Parametro = Hora em formato hhmmss<br />
6 - Parametro = Valor absoluto (sem virgulas ou ponto, no caso do exemplo o valor é 3,29)<br />
7 - Parametro = Destino do arquivo de retorno do sitef, pois no caso estamos utilizando transferencia de arquivo para poder ser compativel com todos os sistemas (<br />
vide IntPos.001_*  para ver as respectivas RESPOSTAS do sistema <br />
<br />
)<br />


