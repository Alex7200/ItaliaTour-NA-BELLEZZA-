#include "librerie.h"

int main(){
    system("title ItaliaTour");
    system("color f3");
    int pos, pos2, cittaTransitorie;
    double distanza;
    paese italia;
    
    if(!leggiFile(italia)){
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
                        
                        pos=inserisciNomeCitta(" citta' di partenza ", italia);
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
                    
                    puntiInteresse(italia.citta[pos]);
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