#include "librerie.h"

int leggiFile(paese &italia){
    sqlite3_stmt *stmt = NULL;
    sqlite3 *db;
    int rc, i, j;
    
    rc = sqlite3_open("database.db",&db);
    if(rc != SQLITE_OK)
        return 1;
    
    rc = sqlite3_prepare_v2(db, "select * from citta;", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
        return 1;

    italia.numCitta=0;
    
    rc = sqlite3_step(stmt);
    
    while (rc != SQLITE_DONE && rc != SQLITE_OK)
    {
        for(i=0; i<MAX_COL_CITTA ;i++){
            switch( i ){
                case 0:{
                    const unsigned char* nomeCitta = sqlite3_column_text(stmt, i);
                    
                    for(j=0; nomeCitta[j] ; j++)
                        italia.citta[italia.numCitta].nomeCitta[j]=nomeCitta[j];
                    italia.citta[italia.numCitta].nomeCitta[j]=nomeCitta[j];
                    
                    break;
                }
                case 1:{
                    const unsigned char* nomeRegione = sqlite3_column_text(stmt, i);
                    
                    for(j=0; nomeRegione[j] ; j++)
                        italia.citta[italia.numCitta].nomeRegione[j]=nomeRegione[j];
                    italia.citta[italia.numCitta].nomeRegione[j]=nomeRegione[j];
                    
                    break;
                }
                case 2:{
                    italia.citta[italia.numCitta].abitanti=sqlite3_column_int(stmt, i);
                        
                    break;
                }
                case 3:{
                    italia.citta[italia.numCitta].superficie=sqlite3_column_double(stmt, i);
                        
                    break;
                }
                case 4:{
                    italia.citta[italia.numCitta].coord.x=sqlite3_column_double(stmt, i);
                        
                    break;
                }
                case 5:{
                    italia.citta[italia.numCitta].coord.y=sqlite3_column_double(stmt, i);
                        
                    break;
                }
                default:{
                    break;
                }
                
            }
        }
        
        rc = sqlite3_step(stmt);
        italia.numCitta++;
    }

    sqlite3_close(db);

    return 0;
}
