#include "librerie.h"

double distanzaCitta(const luoghi &citta1, const luoghi &citta2){
    return sqrt( pow( ( citta1.coord.x - citta2.coord.x ),2 ) + pow( ( citta1.coord.y - citta2.coord.y ),2 ) )*100*CURVATURA_TERRESTRE;
}

double distanzaPiuCitta( const paese &italia , int cittaTransitorie){
	double distanzaTot = 0;
	char nomeCitta[MAX_CAR];
	int posRec,posPass;
    
    cout << "Inserisci il nome della citta' di partenza"<<endl<<'\t';
    cin.getline( nomeCitta, MAX_CAR );
    while((posRec = ricercaCitta( nomeCitta, italia ))==-1){
        cout<<"Citta' inserita non valida..."<<endl;
        Sleep(500);
        cout << "Reinserisci il nome della citta' di partenza"<<endl<<'\t';
        cin.getline( nomeCitta, MAX_CAR );
    }
    
    int i = 0;
    while( i < cittaTransitorie){
        posPass = posRec;
        
        cout <<endl<<"Inserisci il nome della citta' transitoria"<<endl<<'\t';
        cin.getline( nomeCitta, MAX_CAR );
        while((posRec = ricercaCitta( nomeCitta, italia ))==-1){
            cout<<"Citta' inserita non valida..."<<endl;
            Sleep(500);
            cout << "Reinserisci il nome della citta' transitoria "<<endl<<'\t';
            cin.getline( nomeCitta, MAX_CAR );
        }
        
        distanzaTot += distanzaCitta( italia.citta[posRec], italia.citta[posPass] );
        i++;
    }
    
    return distanzaTot;
}

void showInfo( const luoghi &citta ){    
    cout << "[1]  Nome Citta': " << citta.nomeCitta <<endl;
    cout << "[2]  Nome Regione: " << citta.nomeRegione <<endl;
    cout << "[3]  Numero abitanti: " << citta.abitanti <<endl;
    cout << "[3]  Superficie occupata: " << citta.superficie <<endl;
    cout << "[4A] Coordinata N: " << citta.coord.x <<endl;
    cout << "[4A] Coordinata E: " << citta.coord.y <<endl;
}

void addCitta( paese &italia ){
	cout << "Inserisci il nome della regione di appartenenza: ";
	 cin.getline( italia.citta[italia.numCitta].nomeRegione, MAX_CAR );
	
	cout << "Inserisci il numero di abitanti che vivono in " << italia.citta[italia.numCitta].nomeCitta << ": ";
	 cin >> italia.citta[italia.numCitta].abitanti;
	while( cin.get() != '\n' );
	
	cout << "Inserisci la superficie su cui si estende " << italia.citta[italia.numCitta].nomeCitta << ": ";
	 cin >> italia.citta[italia.numCitta].superficie;
	while( cin.get() != '\n' );
	
	cout << "Digita le coordinate N : ";
	 cin >> italia.citta[italia.numCitta].coord.x;
	while( cin.get() != '\n' );
	
	cout << "Digita le coordinate E : ";
	 cin >> italia.citta[italia.numCitta].coord.y;
	while( cin.get() != '\n' );
	
	italia.numCitta ++;
}

void addCittaFile( paese &italia ){
	fstream file;
	
	file.open( "citta.csv", ios::app );
		
	if( !file )
		MessageBoxA(NULL,"Impossibile aprire il file citta.csv assicurarsi di averlo inserito nella stessa directory dell'eseguibile!","ItaliaTour", MB_OK | MB_ICONERROR);
	else{
		file << italia.citta[italia.numCitta - 1].nomeCitta << ';';
		file << italia.citta[italia.numCitta - 1].nomeRegione << ';';
		file << italia.citta[italia.numCitta - 1].abitanti << ';';
		file << italia.citta[italia.numCitta - 1].superficie<< ';';
		file << italia.citta[italia.numCitta - 1].coord.x << ';';
		file << italia.citta[italia.numCitta - 1].coord.y << '\n';
			
		cout << "Inserimento nel file avvenuto con successo!" <<endl;              
	}
		
	file.close();
}

int inserisciNomeCitta(const char stringa[], const paese &italia){
    char nomeCitta[MAX_CAR];
    int pos;
    
    cout<<"Inserisci il nome della"<<stringa<<endl<<'\t';
    cin.getline(nomeCitta,MAX_CAR);
    while((pos=ricercaCitta(nomeCitta,italia))==-1){
        cout<<"Citta' inserita non valida..."<<endl;
        Sleep(500);
        cout<<"Reinserisci il nome della"<<stringa<<endl<<'\t';
        cin.getline(nomeCitta,MAX_CAR);
    }
    return pos;
}

int ricercaCitta(const char nomeCitta[], const paese &italia){
    for(int i=0; i<italia.numCitta; i++){
        if(!strcmp(nomeCitta,italia.citta[i].nomeCitta))
            return i;
    }
    return -1;
}

void confronto(const luoghi &citta1, const luoghi &citta2){
    cout<<endl;
    if(citta1.abitanti>citta2.abitanti)
        cout<<"<-- "<<citta1.nomeCitta<<" ha un numero maggiore di abitanti di "<<citta2.nomeCitta<<" -->"<<endl;
    else if(citta1.abitanti<citta2.abitanti)
        cout<<"<-- "<<citta2.nomeCitta<<" ha un numero maggiore di abitanti di "<<citta1.nomeCitta<<" -->"<<endl;
    else
        cout<<"<-- "<<citta1.nomeCitta<<" ha lo stesso numero di abitanti di "<<citta2.nomeCitta<<" -->"<<endl;
    
    if(citta1.superficie>citta2.superficie)
        cout<<"<-- "<<citta1.nomeCitta<<" si estende su un maggior territorio rispetto "<<citta2.nomeCitta<<" -->"<<endl;
    else if(citta1.superficie<citta2.superficie)
        cout<<"<-- "<<citta2.nomeCitta<<" si estende su un maggior territorio rispetto "<<citta1.nomeCitta<<" -->"<<endl;
    else
        cout<<"<-- "<<citta1.nomeCitta<<" si estende sul territorio come "<<citta2.nomeCitta<<" -->"<<endl;
    cout<<endl;
}

void puntiInteresse(const luoghi &citta){
        
    sqlite3_stmt *stmt = NULL;
    sqlite3 *db;
    int rc;
    
    char stringa[1000]="select * from puntiInteresse where Citta glob '";
    strcat(stringa, citta.nomeCitta);
    strcat(stringa,"';");
    
    rc = sqlite3_open("database.db",&db);
    
    if(rc == SQLITE_OK){
        rc = sqlite3_prepare_v2(db, stringa, -1, &stmt, NULL);
        
        if(rc == SQLITE_OK){
            
            rc = sqlite3_step(stmt);
            while(rc != SQLITE_DONE && rc != SQLITE_OK){
                int i;
                
                for(i=1; i<6 ;i++){
                    corniceMedio();
                    cout<<"  Hotel:  "<< sqlite3_column_text(stmt, i)<<"  -->  ";
                    i++;
                    cout<< sqlite3_column_text(stmt, i)<<endl;
                }
                
                for(i=7; i<12 ;i++){
                    corniceMedio();
                    cout<<"  Ristorante:  "<< sqlite3_column_text(stmt, i)<<"  -->  ";
                    i++;
                    cout<< sqlite3_column_text(stmt, i)<<endl;
                }
                corniceMedio();
                
                rc = sqlite3_step(stmt);
            }
        }
    }
    sqlite3_close(db);
}
