#include <iostream>
#include "jdb.h"

using namespace std;


int callbackSqlExec(void *id, int argc, char **argv, char **azColName) {

    cout<<"ID: "<<(char *)id<<'\n';
    int i;
    for(i = 0; i < argc; i++) {
        cout<<azColName[i]<<argv[i]<< '\n';
    }
    return 0;
}


char *callbackSqlCreate() {

    return (char *) "CREATE TABLE TMPHMD("    \
          "TIMESTAMP KEY NOT NULL," \
          "HMD TEXT NOT NULL,"      \
          "TMP TEXT NOT NULL );";

}

int main(int argc, char **argv) {
    
    JDb tmpJDb("tmpJDb.db",&callbackSqlCreate,&callbackSqlExec,1);
    tmpJDb.exec((char *)"INSERT INTO TMPHMD (TIMESTAMP,HMD,TMP) VALUES ('20150307','12.3','22.2');");
    tmpJDb.exec((char *)"SELECT * FROM TMPHMD","Select");
    return 0;
}