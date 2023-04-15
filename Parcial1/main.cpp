#include <iostream>
#include <fstream>

using namespace std;

int main()
{
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
    ifstream archivo("prueba.txt");
        if (archivo.is_open()) {
            char contenido[100];
            int pos=0;
            while (archivo.good()) { //sin problemas de escritura, lectura, logica, etc.
                contenido[pos] = archivo.get();
                if (contenido[pos] != EOF) {
                    pos++;
                }
                if (pos >= 100 - 1) {
                    break;
                }
            }
            contenido[pos] = '\0';
            cout << contenido <<endl;
            archivo.close();
        } else {
            cout << "No se pudo abrir el archivo" <<endl;
        }
    return 0;
}
