#include <iostream>
#include <string.h>
#include "src/sqlite/sqlite3.h"
#include <vector>

using namespace std;

static int callback(void* data, int argc, char** argv, char** azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char*)data);
  
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
  
    printf("\n");
    return 0;
}

int main()
{
	sqlite3* db;
	int exit = 0;
    char* messageError;

	exit = sqlite3_open("test.db",&db);
	if(exit)
    {
		cerr << "Nao e possivel abrir o banco de dados: " << sqlite3_errmsg(db) << endl;
	}else {
		cout << "Banco de dados aberto " << endl;
	}

    string commitCmd = "BEGIN;";
    exit = sqlite3_exec(db,commitCmd.c_str(),NULL,0,&messageError);
	if(exit)
    {
		cerr << "Nao e possivel iniciar transacao: " << messageError << endl;
        sqlite3_free(messageError);
	}else {
		cout << "Transacao aberta " << endl;
	}

	string tableCmd = "CREATE TABLE IF NOT EXISTS GRAFICOS_ID (IndexID INTEGER PRIMARY KEY AUTOINCREMENT, Material TEXT NOT NULL);";
	exit = sqlite3_exec(db, tableCmd.c_str(),NULL,0,&messageError);
	if(exit!=SQLITE_OK)
    {
		cerr << "Nao e possivel criar tabela: " << messageError << endl;
        sqlite3_free(messageError);
	}else {
		cout << "Tabela Criada " << endl;
	}

    string insertCmd = "INSERT INTO GRAFICOS_ID (Material) VALUES ('titanio');";
	exit = sqlite3_exec(db, insertCmd.c_str(),NULL,0,&messageError);
	if(exit!=SQLITE_OK)
    {
		cerr << "Nao e possivel inserir valores: " << messageError << endl;
        sqlite3_free(messageError);
	}else {
		cout << "Valores inseridos " << endl;
	}

    string queryCmd = "SELECT * FROM GRAFICOS_ID;";
    sqlite3_exec(db, queryCmd.c_str(),callback,NULL,NULL);
	exit = sqlite3_exec(db, queryCmd.c_str(),NULL,0,&messageError);
	if(exit!=SQLITE_OK)
    {
		cerr << "Nao e possivel consultar valores: " << messageError << endl;
        sqlite3_free(messageError);
	}else {
		cout << "Consulta Realizada " << endl;
	}

    commitCmd = "COMMIT;";
    exit = sqlite3_exec(db, commitCmd.c_str(),NULL,0,&messageError);
    if(exit!=SQLITE_OK)
    {
		cerr << "Nao e possivel finalizar transacao: " << messageError << endl;
        sqlite3_free(messageError);
	}else {
		cout << "Transacao Finalizada" << endl;
	}

	sqlite3_close(db);
	cout << "Banco de dados fechado" << endl;
	return 0;
}