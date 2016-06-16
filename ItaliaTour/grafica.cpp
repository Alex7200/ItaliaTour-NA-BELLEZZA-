#include "librerie.h"

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
