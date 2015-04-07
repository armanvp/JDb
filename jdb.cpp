#include "jdb.h"

/*--------------------------------------------------------------------------------**
	Constructor
**--------------------------------------------------------------------------------*/
JDb::JDb(const char *file, cbSqlCreateTab cbSqlCrtTab, cbSqlExec cbSqlExec, int verbose) {

	int rc = 0;

	/* Set class variables */
	this->verbose 	      = verbose;
	this->_cbSqlCreateTab = cbSqlCrtTab;
	this->_cbSqlExec      = cbSqlExec;
	
	/* Open SQLite File */
	rc = sqlite3_open(file, &this->sqlite);
    this->retcodeCheck(&rc, (char *)sqlite3_errmsg(this->sqlite), "Open DB");     
	
	/* Create Table (if not existing) */
    this->tableCreate();
	
}
 
/*--------------------------------------------------------------------------------**
	retcodeCheck - Checks return code and returns messages
**--------------------------------------------------------------------------------*/
void JDb::retcodeCheck(int *rc, char *cError, const char *cMsg) {
     
    if(*rc != SQLITE_OK) {
		fprintf(stderr,"SQLite: %s\n",cError);
        sqlite3_free(cError);
    }else{
		if(this->verbose) {
			fprintf(stdout,"SQLite: %s\n", cMsg);
		}
    }
     
}

/*--------------------------------------------------------------------------------**
	exec - Executes SQL Statement
**--------------------------------------------------------------------------------*/
void JDb::exec(char *sql, const char *id) {

	char *cError;
	int  rc = 0;

	/* Executes SQL Statement */
    rc = sqlite3_exec(this->sqlite, sql, this->_cbSqlExec, (void *) id, &cError);
    this->retcodeCheck(&rc,cError,"Select successful");

}
 
/*--------------------------------------------------------------------------------**
	tableCreate - Creates the table (if does not exists)
**--------------------------------------------------------------------------------*/
void JDb::tableCreate() {
     
    char *cError;
	char *sql;
	int  rc;
 
	/* Calls the SQL Create Table Callback Function */
    sql = this->_cbSqlCreateTab();
	
	/* Executes SQL Statement */
    this->exec(sql);
     
}