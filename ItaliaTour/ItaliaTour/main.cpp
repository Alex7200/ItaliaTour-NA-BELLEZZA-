#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <windows.h>

#define MAX_CAR 100+1
#define MAX_ELEM 1000
#define MAX_CITTA 5

#define CURVATURA_TERRESTRE 0.9996

#define CAR_SEPARATORE ';'

using namespace std;

typedef struct{
	double x;
	double y;
}coordinate;

typedef struct{
	char nomeCitta[MAX_CAR];
	char nomeRegione[MAX_CAR];
	long int abitanti;
	double superficie;
	coordinate coord;
}luoghi;

typedef struct{
    luoghi citta[MAX_ELEM];
    int numCitta;
}paese;

void corniceAlto();
void corniceBasso();
void corniceMedio();
void car();
void menu();

int leggiFile(paese &italia);
void estraiElemento(char rigaIn[],char elemento[]);

double distanzaCitta(const luoghi &citta1, const luoghi &citta2);
double distanzaPiuCitta( const paese &italia , int cittaTransitorie);

void showInfo( const luoghi &citta );
void addCitta( paese &italia );
void addCittaFile( paese &italia );

int inserisciNomeCitta(const char stringa[], const paese &italia);
int ricercaCitta(const char nomeCitta[], const paese &italia);
void confronto(const luoghi &citta1, const luoghi &citta2);

void puntiInteresse(int pos);

int main(){
    system("title ItaliaTour");
    system("color f3");
    int pos, pos2, cittaTransitorie;
    double distanza;
    paese italia;
    
    if(leggiFile(italia)){
        char nomeCitta[MAX_CAR];
        int scelta;
        
        do{
            system("color f3");
            menu();
            cin >> scelta;
            while(cin.get()!='\n');
            switch( scelta ){
                case 0:
                    MessageBoxA(NULL,"Grazie per aver utilizzato il nostro programma!","ItaliaTour", MB_OK | MB_ICONINFORMATION);
                    break;
                case 1:
                    MessageBeep(MB_ICONINFORMATION);
                    if(MessageBox(NULL, "[1] <-- Desideri procedere con questa operazione?", "ItaliaTour",  MB_YESNO | MB_ICONQUESTION) == IDYES){
                        system("cls");
                        system("color 3f");
                        
                        pos=inserisciNomeCitta(" citta' di partenza", italia);
                        cout<<endl;
                        pos2=inserisciNomeCitta(" citta' di arrivo ", italia);
                    
                        distanza = distanzaCitta( italia.citta[pos],italia.citta[pos2] );
                        
                        corniceAlto();
                        car();
                        cout<< italia.citta[pos].nomeCitta << " e " << italia.citta[pos2].nomeCitta << " si distanziano di " << distanza <<"km\t\t\t ";
                        car();
                        cout<<endl;
                        corniceBasso();
                        
                        cout<<endl;
                        system("PAUSE");
                    }
                    break;
                case 2:
                    MessageBeep(MB_ICONINFORMATION);
                    if(MessageBox(NULL, "[2] <-- Desideri procedere con questa operazione?", "ItaliaTour",  MB_YESNO | MB_ICONQUESTION) == IDYES){
                        system("cls");
                        system("color 3f");
                        
                        pos=inserisciNomeCitta(" prima citta' da confrontare ", italia);
                        cout<<endl;
                        pos2=inserisciNomeCitta(" seconda citta' da cofrontare", italia);
                        confronto(italia.citta[pos],italia.citta[pos2]);
                        cout<<endl;
                        system("PAUSE");
                    }
                    break;
                case 3:
                    MessageBeep(MB_ICONINFORMATION);
                    if(MessageBox(NULL, "[3] <-- Desideri procedere con questa operazione?", "ItaliaTour",  MB_YESNO | MB_ICONQUESTION) == IDYES){
                        system("cls");
                        system("color 3f");
                        
                        do{
                            cout << "Quante citta' vuoi passare prima di arrivare a destinazione? [MAX = " << MAX_CITTA << "]"<<endl<<'\t';
                            cin >> cittaTransitorie;
                            while( cin.get() != '\n' ); 
                        }while( cittaTransitorie > MAX_CITTA || cittaTransitorie<1);
                        
                        cout<<endl;
                        
                        distanza = distanzaPiuCitta( italia, cittaTransitorie );
                    
                        corniceAlto();
                        car();
                        cout<<" La distanza TOTALE e' " << distanza<<"km                                 ";
                        car();
                        cout<<endl;
                        corniceBasso();
                        
                        cout<<endl;
                        system("PAUSE");
                    }
                break;
            case 4:
                MessageBeep(MB_ICONINFORMATION);
                if(MessageBox(NULL, "[4] <-- Desideri procedere con questa operazione?", "ItaliaTour",  MB_YESNO | MB_ICONQUESTION) == IDYES){
                    system("cls");
                    system("color 3f");
                    
                    cout << "Inserisci la citta' di cui vuoi conoscere le informazioni:"<<endl<<'\t';
                    cin.getline( nomeCitta , MAX_CAR);
        
                    pos = ricercaCitta( nomeCitta, italia );
        
                    if( pos != -1 )
                        showInfo( italia.citta[pos] );
                    else{
        
                        if(MessageBox(NULL, "Desideri aggiungere le informazioni inerenti a una citta?", "ItaliaTour",  MB_YESNO | MB_ICONQUESTION) == IDYES){
                            system("cls");
                            
                            strcpy( italia.citta[italia.numCitta].nomeCitta, nomeCitta );
                            cout << "Nome della citta' aggiunta con successo!" << endl;
				
                            addCitta( italia );
                            addCittaFile( italia );
                        }
                    }
                    cout<<endl;
                    system("PAUSE");
                }
                break;
            case 5:
                MessageBeep(MB_ICONINFORMATION);
                if(MessageBox(NULL, "[5] <-- Desideri procedere con questa operazione?", "ItaliaTour",  MB_YESNO | MB_ICONQUESTION) == IDYES){
                    system("cls");
                    system("color 3f");
                    
                    cout<<"Inserire il nome della citta' della quale vuole sapere i punti di interesse: "<<endl<<'\t';
                    cin.getline(nomeCitta,MAX_CAR);
                    while((pos=ricercaCitta(nomeCitta,italia))==-1){
                        cout<<"Citta' non valida..."<<endl<<"Inserire il nome della citta' della quale vuole sapere i punti di interesse: "<<endl<<'\t';
                        cin.getline(nomeCitta,MAX_CAR);
                    }
                    
                    system("cls");
                    
                    puntiInteresse(pos);
                    cout<<endl;
                    system("PAUSE");
                }
                break;
            default:
                MessageBoxA(NULL,"Ha inserito una scelta non valida!","ItaliaTour", MB_OK | MB_ICONERROR);
                break;
            }
        
            system("cls");
        }while( scelta != 0);
        
        return 0;
    }
    
	return 1;
}

void corniceAlto(){
    cout<<(char)201;
    for(int i=0; i<64 ;i++)
        cout<<(char)205;
    cout<<(char)187<<endl;
}

void corniceBasso(){
    cout<<(char)200;
    for(int i=0; i<64 ;i++)
        cout<<(char)205;
    cout<<(char)188<<endl;
}

void corniceMedio(){
    cout<<(char)204;
    for(int i=0; i<64 ;i++)
        cout<<(char)205;
    cout<<(char)185<<endl;
}

void car(){
    cout<<(char)186;
}

void menu(){
    cout<<"                        *MENU DI SCELTA*"<<endl;
    
    corniceAlto();
    
    cout<<(char)186<<"                 Inserisci l'operazione da eseguire             "<<(char)186<<endl;
    
    corniceBasso();
    
    corniceAlto();
    car();
	cout<<"[1]Calcola distanza tra due citta'                              ";
    car();
    cout<<endl;
    
    corniceMedio();
    car();
	cout<<"[2]Confronta le informazioni di due citta'                      ";
    car();
    cout<<endl;
    
    corniceMedio();
    car();
	cout<<"[3]Calcola il percorso tra piu' citta'                          ";
    car();
    cout<<endl;
    
    corniceMedio();
    car();
	cout<<"[4]Visualizza info di una citta'                                ";
    car();
    cout<<endl;
    
    corniceMedio();
    car();
	cout<<"[5]Visualizza punti di interesse di una citta'                  ";
    car();cout<<endl;
    
    corniceMedio();
    car();
    cout<<"[0]Per uscire dal programma                                     ";
    car();cout<<endl;
    
    corniceBasso();
    cout<<endl<<'\t';
}

int leggiFile( paese &italia ){
    ifstream infile;
	char riga[MAX_CAR];
	char elemento[MAX_CAR];
    int countCampi;
	
    infile.open("citta.csv");
	if(!infile){
		MessageBoxA(NULL,"Impossibile aprire il file citta.csv assicurarsi di averlo inserito nella stessa directory dell'eseguibile!","ItaliaTour", MB_OK | MB_ICONERROR);
        return 0;
    }
	else{
        italia.numCitta = 0;
        
		infile.getline(riga,MAX_CAR);
		while(!infile.eof()){
            countCampi = 0;
            while(riga[0]){
                estraiElemento(riga,elemento);
                switch( countCampi ){
                    case 0:
                        strcpy( italia.citta[italia.numCitta].nomeCitta, elemento );
                        break;
                    case 1:
                        strcpy( italia.citta[italia.numCitta].nomeRegione, elemento );
                        break;
                    case 2:
                        italia.citta[italia.numCitta].abitanti = atoi( elemento );
                        break;
                    case 3:
                        italia.citta[italia.numCitta].superficie = atof( elemento );
                        break;
                    case 4:
                        italia.citta[italia.numCitta].coord.x = atof( elemento );
                        break;
                    case 5:
                        italia.citta[italia.numCitta].coord.y = atof( elemento );
                        break;
                    default:
                        break;
                }
                countCampi++;
            }
                
            italia.numCitta++;
				
            infile.getline(riga,MAX_CAR);
			}
			
        infile.close();
        return 1;
    }
}

void estraiElemento(char rigaIn[],char elemento[]){
	int i,j=0;
	int trovato=0;	//per segnalare il ritrovamento del carattere '\n' o ' '
	int k;
		
		//ricerca e copia
    for(i=0;rigaIn[i] && !trovato;i++){
        if( rigaIn[i] != CAR_SEPARATORE){
            elemento[j] = rigaIn[i];
            j++;
        }
        else
            trovato = 1;
    }
    elemento[j] = '\0';
		
    //eliminazione dell'elemento nella stringa
    for(k=0;rigaIn[i];k++,i++)
        rigaIn[k] = rigaIn[i];
    rigaIn[k] = '\0';
}

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

void puntiInteresse(int pos){
        
        fstream filePunti;
        char riga[1000];
        int i=0,  hotelOrRistorante=0, contaPuntiVirgola=0;
        
        filePunti.open("punti_interessanti.csv",ios::in);
        
        if(!filePunti){
                MessageBoxA(NULL,"Impossibile aprire il file punti_interessanti.csv assicurarsi di averlo inserito nella stessa directory dell'eseguibile!","ItaliaTour", MB_OK | MB_ICONERROR);
        }
        else{
            for(i=0; i<=pos ;i++){
                filePunti.getline(riga,1000);
            }
            i=0;
            
            corniceAlto();
            cout<<"     Hotel: ";
            while(riga[i]){
                if(riga[i]!='\0'){
                    if(riga[i]!=';')
                        cout<<riga[i];
                    else if(contaPuntiVirgola%2){
                        contaPuntiVirgola++;
                        cout<<endl;
                        corniceMedio();
                        
                        if(contaPuntiVirgola%6==0)
                            hotelOrRistorante=1;
                            
                        if(hotelOrRistorante)
                            cout<<"     Ristorante: ";
                        else
                            cout<<"     Hotel: ";
                    }
                    else{
                        contaPuntiVirgola++;
                        cout<<" --> ";
                    }
                    i++;
                }
            }
            cout<<endl;
            corniceBasso();
        }
}
