#include <iostream>
#include <fstream>

using namespace std;

void leerPensum(char texto[]);
void Matricular(char NameM[],char codigo[],char HI[],char HP[],char C[]);
int ExtCodigo (char codigo[],char texto[],int k);
int extNombre(int k, char texto[], char NameM[]);
int HProf(int k,char texto[],char HP[]);
int HIndep(int k,char texto[],char HI[]);
int extCreditos(int k,char texto[],char C[]);
int todo(int k,char texto[],char codigo[],char NameM[],char HI[],char HP[],char C[]);

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
        case 0: // SALIR
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
            system("cls");
            char texto[300];
            leerPensum(texto);
            cout << "OFERTA DE MATERIAS."<<endl;
            cout << "Aparecera una a una cada materia que puedes matricular."<<endl;
            char codigo[8],NameM[25],HI[2],HP[2],C[2];
            for (int k=0;k<226;k++){
                int mat=0;
                k=todo(k,texto,codigo,NameM,HI,HP,C);
                cout << "\n****************************"<<endl;
                cout << " ***** Nombre ***** Creditos"<<endl;
                cout << NameM<<" * " <<C<< endl;
                cout << "************" << k<< "****************"<<endl;
                cout << "PRESIONA (1) PARA MATRICULAR Y (2) PARA NO MATRICULAR: ";
                cin >> mat;
                if (mat==1){
                    Matricular(NameM,codigo,HI,HP,C);
                }
            }
        }
            break;
        }
    }
    return 0;
}

int todo(int k,char texto[],char codigo[],char NameM[],char HI[],char HP[],char C[]){
    k=ExtCodigo(codigo,texto,k);
    k=extNombre(k,texto,NameM);
    k=HProf(k,texto,HP);
    k=HIndep(k,texto,HI);
    k=extCreditos(k,texto,C);
    return k;
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
    for (int a=0;a<50;a++){
        if (texto[k]!=','){
            codigo[a]=texto[k];
            k++;
        }
        else{
            codigo[a] = '\0';
            break;
        }
    }
    return k;
}

int extNombre(int k,char texto[],char NameM[]){
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
    return k;
}

int HProf(int k,char texto[],char HP[]){
    k++;
    for (int a=0;a<50;a++){
        if (texto[k]!=','){
            HP[a]=texto[k];
            k++;
        }
        else{
            HP[a] = '\0';
            break;
        }
    }
    return k;
}

int HIndep(int k,char texto[],char HI[]){
    k++;
    for (int a=0;a<50;a++){
        if (texto[k]!=','){
            HI[a]=texto[k];
            k++;
        }
        else{
            HI[a] = '\0';
            break;
        }
    }
    return k;
}

int extCreditos(int k,char texto[],char C[]){
    k++;
    for (int a=0;a<50;a++){
        if (texto[k]!=',' and texto[k]!='\n' and texto[k] != '\0'){
            C[a]=texto[k];
            k++;
        }

        else{
            C[a] = '\0';
            break;
        }
    }
    return k;
}

void Matricular(char NameM[],char codigo[],char HI[],char HP[],char C[]){
    ofstream Matricula; // Para escribir en él.
    Matricula.open("Matricula.txt",ios::app); //Modo agregar
    Matricula<<codigo<<','<<NameM<<','<<HP<<','<<HI<<','<<C<<endl;;

    Matricula.close();
}


