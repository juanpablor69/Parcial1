#include <iostream>
#include <fstream>

using namespace std;

void leerPensum(char texto[]);
int ExtCodigo (char codigo[],char texto[],int k);
void extNombre(int k, char texto[], char NameM[]);

int main()
{
    cout << "SISTEMA UNIVERSIDAD" << endl;

    int opcion=1;
    while (opcion!=0) {
        cout << "\n***************** MENU *****************" <<endl;
        cout << "1. VER PENSUM." <<endl;
        cout << "2. MATRICULAR MATERIAS."<<endl;
        cout << "0. Salir"<<endl;

        cout << "\nIngrese seleccionado: ";
        cin >> opcion;

        switch (opcion) {
        case 0: // SALIDA
        {
            cout << "Hasta luego"<<endl;
            opcion=0;
        }
            break;
        case 1: // LEER PENSUM
        {
            char texto[250];
            cout << "*** MATERIAS QUE PUEDES MATRICULAR ***"<<endl;
            leerPensum(texto);
            cout << texto <<endl;
        }
            break;
        case 2: // MATRICULAR
        {
            char texto[250];
            leerPensum(texto);
            cout << "OFERTA DE MATERIAS.\n A CADA UNA PRESIONA (1) PARA MATRICULAR Y (2) PARA NO MATRICULAR"<<endl;
            char codigo[8],NameM[25];
            int k=0;
            k=ExtCodigo(codigo,texto,k);
            extNombre(k,texto,NameM);
            cout << "Deseas Matricular..."<<endl;
            cout << NameM<<endl;
        }
            break;
        }
    }
    return 0;
}

void leerPensum(char texto[]){
    ifstream archivo("pensum.txt");
    if (archivo.is_open()) {
        int pos=0;
        while (archivo.good()) { //sin problemas de escritura, lectura, logica, etc.
            texto[pos] = archivo.get();
            if (texto[pos] != EOF) {
                pos++;
            }
        }
        texto[pos] = '\0';
        archivo.close();
    }else {
        cout << "No se pudo abrir el archivo" <<endl;
    }
}

int ExtCodigo (char codigo[],char texto[],int k){
    for (int i=k;i<100;i++){
        if (texto[k]!=','){
            codigo[k]=texto[k];
            k++;
        }
        else{
            codigo[k] = '\0';
            break;
        }
    }
    return k;
}

void extNombre(int k,char texto[],char NameM[]){
    k++;
    for (int a=0;a<50;a++){
        if (texto[k]!=','){
            NameM[a]=texto[k];
            k++;
        }
        else{
            NameM[a] = '\0';
            break;
        }
    }
}

void HIndep(int k,char texto[],int HI){
    for (int a=0;a<50;a++){
        if (texto[k]!=','){
            HI=texto[k];
            k++;
        }
        else{
            break;
        }
    }
}


