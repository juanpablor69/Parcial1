#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    /* ****** ESCRIBIR ********
    cout << "Parcial1" << endl;
    ofstream prueba; // Para escribir en él.
    prueba.open("prueba.txt",ios::app); //Modo agregar
    char cadena1[20];
    cout <<"Ingrese una palabra: ";
    cin >> cadena1;
    for (int i=0;i<=30;i++){
        if (cadena1[i]=='\0') {
            break;
        }
        prueba<<cadena1[i];
    }
    prueba.close();

    2536101,DescubriendoLaFisica,4,5,3
    */
    ifstream archivo("pensum.txt");
        if (archivo.is_open()) {
            char texto[100],codigo[8],NameM[25],HP[3],HI[3],C[3];
            int pos=0;
            bool ok=true;
            while (archivo.good() and ok==true) { //sin problemas de escritura, lectura, logica, etc.
                texto[pos] = archivo.get();
                if (texto[pos] == '\n'){
                    for (int k=0;k<10;k++){
                        if (texto[pos] == '\0') {
                            break;
                        }
                        if (texto[k]!=','){
                            codigo[k]=texto[k];
                        }
                        else{
                            codigo[k] = '\0';
                            k++;
                            for (int i=0;i<25;i++){
                                if (texto[k]!=','){
                                    NameM[i]=texto[k];
                                    k++;
                                }
                                NameM[i+1] = '\0';
                            }
                            k=10;
                            ok=false;
                        }
                    }
                }
                if (texto[pos] != EOF) {
                    pos++;
                }
            }
            texto[pos] = '\0';
            cout << texto <<endl;
            cout <<"Codigo: " << codigo<<endl;
            cout <<"Nombre Materia: " <<NameM<< endl;;
            archivo.close();
            } else {
            cout << "No se pudo abrir el archivo" <<endl;
        }

    return 0;
}
