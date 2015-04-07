#include <cstdio>
#include <sqlite3.h>

typedef char * (*cbSqlCreateTab)();
typedef int (*cbSqlExec)(void *id, int argc, char **argv, char **azColName);

class JDb {
     
    private:
		cbSqlCreateTab _cbSqlCreateTab;
		cbSqlExec      _cbSqlExec;
		int	 	       verbose;
        sqlite3        *sqlite;
     
        void retcodeCheck(int *rc, char *cError, const char *cMsg = NULL);
        void tableCreate();
		
    public:
	
        JDb(const char *file, cbSqlCreateTab cbSqlCrtTab, cbSqlExec cbSqlExec = NULL, int verbose = 0);
		void exec(char *sql, const char *id = NULL);
     
};