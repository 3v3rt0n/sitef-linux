#include <mysql.h>

 MYSQL *con;
  MYSQL_RES *result;
  MYSQL_ROW row = NULL;
   my_ulonglong rows;

void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

MYSQL *conectarMysql(char *hostname, char *username, char *password, char *database)
{
    MYSQL *con = mysql_init(NULL);
    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }
    else
    {
        if (mysql_real_connect(con, hostname, username, password, database, 0, NULL, 0) == NULL)
        {
            finish_with_error(con);
        }
        else
        {
            return con;
        }
    }
    return NULL;
}

void executarBancoDeDados(){
  char sql[2048 * 100] = "";
  con = conectarMysql("epoc3.sys", "epoc2", "p0c2p0c2", "epoc3");
  mysql_query(con, "CREATE DATABASE IF NOT EXISTS spool_tef");
  mysql_close(con);
  con = conectarMysql("epoc3.sys", "epoc2", "p0c2p0c2", "spool_tef");
  mysql_query(con, "CREATE TABLE  IF NOT EXISTS `transacao_tef` (  `cod_spool` BIGINT(14) NOT NULL AUTO_INCREMENT,  `cod_fidel` BIGINT(14) NULL,  `data` VARCHAR(45) NULL,  `hora` VARCHAR(45) NULL,  `valor` VARCHAR(45) NULL,  `bandeira` VARCHAR(100) NULL,  `nsu` BIGINT(14) NULL,  `via` LONGTEXT NULL,  PRIMARY KEY (`cod_spool`))");
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
}


void IniciarTransacaoBanco(char *pDataFiscal , char *pHoraFiscal , char *pCupom ){

  char sql[2048 * 100] = "";
    con = conectarMysql("epoc3.sys", "epoc2", "p0c2p0c2", "spool_tef");
    sprintf(sql, "Select * from transacao_tef where cod_fidel = %s and data = %s and hora = %s", pCupom, pDataFiscal,pHoraFiscal);
    if (mysql_query(con, sql))
    {
      finish_with_error(con);
    }
    result = mysql_store_result(con);

    if (result == NULL)
    {
      finish_with_error(con);
    }
    rows = mysql_num_rows(result);
    if (rows <= 0)
    sprintf(sql, " insert into transacao_tef (cod_fidel,data,hora) VALUES (%s,'%s','%s')", pCupom, pDataFiscal, pHoraFiscal);
    mysql_real_query(con, sql, strlen(sql));
    fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
}

void atualizarTransacaoBanco(char *pCupom, char *pDataFiscal, char *pHoraFiscal, char *Valor, char * BANDEIRA,  char *NSU , char *BufferBanco){
  con = conectarMysql("epoc3.sys", "epoc2", "p0c2p0c2", "spool_tef");
      char sql[2048 * 100] = "";
    sprintf(sql, "  Update  transacao_tef set valor = '%s' ,     bandeira = '%s' , nsu = '%s' ,     via = '%s' where cod_fidel = %s and data='%s' and hora = '%s' " , Valor,BANDEIRA,NSU,BufferBanco,pCupom,pDataFiscal,pHoraFiscal);
    printf("SQL = = = %s = = = \n\n" , sql);
  mysql_real_query(con, sql, strlen(sql));
    mysql_close(con);

}
