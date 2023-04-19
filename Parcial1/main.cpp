#include <iostream>
#include <fstream>

using namespace std;

void leerPensum(char texto[]);
int ExtCodigo (char codigo[],char texto[],int k);
int extNombre(int k, char texto[], char NameM[]);
int HProf(int k,char texto[],char HP[]);
int HIndep(int k,char texto[],char HI[]);
int extCreditos(int k,char texto[],char C[]);
int todo(int k,char texto[],char codigo[],char NameM[],char HI[],char HP[],char C[]);
int leerMatri(char tex_mat[]);
void Matricular(char NameM[],char codigo[],char HI[],char HP[],char C[]);
int leerHorario(char tex_hor[]);
int extHora(int k,char texto[],char C[]);
void RegHorario(char codigo[],char dia[],char hora[]);
int conv(char C[]);
bool ComparaCadenas(char cadena1[],char cadena2[]);
void ConvertirMay(char cadena[]);

int main()
{
    cout << "SISTEMA UNIVERSIDAD - PARCIAL 1 INFO II" << endl;
    int opcion=1,nmat=0,ncred=0;
    bool reghorario=false;
    while (opcion!=0) {
        cout << "\n***************** MENU *****************" <<endl;
        cout << "1. VER PENSUM." <<endl;
        cout << "2. MATRICULAR MATERIAS."<<endl;
        cout << "3. VER MATERIAS MATRICULADAS"<<endl;
        cout << "4. REGISTRAR HORARIO."<<endl;
        cout << "5. Analizar y sugerir horas de estudio."<<endl;
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
            system("cls");
            char texto[250];
            cout << "*** MATERIAS PRIMER SEMESTRE ***"<<endl;
            leerPensum(texto);
            cout << texto <<endl;
        }
            break;
        case 2: // MATRICULAR
        {
            system("cls");
            int mat=0;
            bool matri;
            char texto[300],codigo[8],NameM[25],HI[2],HP[2],C[2];
            char texto_[300],codigo_[8],NameM_[25],HI_[2],HP_[2],C_[2];
            leerPensum(texto);
            cout << "OFERTA DE MATERIAS."<<endl;
            cout << "Aparecera una a una cada materia que puedes matricular."<<endl;

            if (leerMatri(texto_)>0){
                for (int k=0;k<226;k++){
                    k=todo(k,texto,codigo,NameM,HI,HP,C);
                    int max=leerMatri(texto_);
                    matri=false;
                    for (int m=0;m<max;m++){
                        m=todo(m,texto_,codigo_,NameM_,HI_,HP_,C_);
                        if (ComparaCadenas(codigo,codigo_)){
                            matri=true;
                        }
                    }
                    if (matri==false){
                        cout << "\n****************************"<<endl;
                        cout << " ***** Nombre ***** Creditos"<<endl;
                        cout << NameM<<" * " <<C<< endl;
                        cout << "******************************"<<endl;
                        cout << "PRESIONA (1) PARA MATRICULAR Y (2) PARA NO MATRICULAR: ";
                        cin >> mat;
                        if (mat==1){
                            Matricular(NameM,codigo,HI,HP,C);
                        }
                    }
                }
            }
            else{
                for (int k=0;k<226;k++){
                    k=todo(k,texto,codigo,NameM,HI,HP,C); //una materia matriculada
                    cout << "\n****************************"<<endl;
                    cout << " ***** Nombre ***** Creditos"<<endl;
                    cout << NameM<<" * " <<C<< endl;
                    cout << "******************************"<<endl;
                    cout << "PRESIONA (1) PARA MATRICULAR Y (2) PARA NO MATRICULAR: ";
                    cin >> mat;
                    if (mat==1){
                        Matricular(NameM,codigo,HI,HP,C);
                    }
                }
            }
        }
            break;
        case 3:
        {
            system("cls");
            char tex_mat[250];
            int max=leerMatri(tex_mat);
            if (max>0){
                cout << "*** MATERIAS MATRICULADAS ***"<<endl;
                cout << tex_mat <<endl;
            }else{
                cout<<"No hay materias matriculadas."<<endl;
            }

        }
            break;
        case 4: //REGISTRAR HORARIO
        {
            system("cls");
            char texmat[200],registrar[8];
            int max,cont_h=0,htotal,hfaltan;
            max=leerMatri(texmat);
            if (max>0){
                cout << "MATERIAS MATRICULADAS: "<<endl;
                cout <<texmat<<endl;
                cout <<"\nIngresa el codigo de la materia para registrar horario: ";
                cin >> registrar;
                for (int k=0;k<max;k++){ // -- analizando matricula
                    char codigo[8],NameM[25],HI[2],HP[2],C[2];
                    k=todo(k,texmat,codigo,NameM,HI,HP,C); //
                    if (ComparaCadenas(codigo,registrar)){
                        char tex_hor[100];
                        cout << "\nRegistrando horario para " << NameM <<endl;
                        int max_=leerHorario(tex_hor);
                        for (int i=0;i<max_;i++){ // -- ANALIZANDO HORARIO PARA IMPRIMIR RESUMEN
                            char codigo_[8],hora_[2],diaL_[2];
                            i=ExtCodigo(codigo_,tex_hor,i);
                            i=extHora(i,tex_hor,diaL_);//dia
                            i=extCreditos(i,tex_hor,hora_);
                            if (ComparaCadenas(codigo,codigo_)){
                                cont_h++;
                            }
                        }
                        htotal=conv(HP)+conv(HI);
                        hfaltan=htotal - cont_h;
                        cout <<"Tienes " <<cont_h<<" horas registradas de esta materia."<<endl;
                        cout<<"Te quedan " <<hfaltan <<" horas por registrar."<<endl;;
                        char dia[2],hora[2];
                        if (hfaltan>0){
                            cout<<"\nREGISTRAR HORA UNICA"<<endl;
                            cout<<"OJO: Dia sera una letra en mayuscula. Hora sera una hora entre 8 y 21 (hora militar)."<<endl;
                            cout << "Dia: ";
                            cin >> dia;
                            ConvertirMay(dia);
                            cout << "Hora: ";
                            cin >> hora;
                            bool ok=true;
                            for (int i=0;i<max_;i++){ // -- analiza horario y verifica hora.
                                char codigo_[8],hora_[2],diaL_[2];
                                i=ExtCodigo(codigo_,tex_hor,i);
                                i=extHora(i,tex_hor,diaL_);//DIA
                                i=extCreditos(i,tex_hor,hora_); //hora
                                if (ComparaCadenas(dia,diaL_) and ComparaCadenas(hora,hora_)){ //dia
                                    ok=false;
                                }
                            }
                            if (ok){
                                cout<<"REGISTRADO!!"<<endl;
                                RegHorario(codigo,dia,hora);
                            }else{
                                cout<<"ERROR: Ya existe un registro a esta hora."<<endl;
                            }
                        }else{
                            cout<<"No puedes registrar mas horas para esta materia."<<endl;
                        }
                    }
                }
            }
            else{
                cout << "Debes matricular primero."<<endl;
            }
        }
            break;
        case 5: //SUGERIR HORARIO
        {
            system("cls");
            char texmat[200];
            int max,nHI=0,nHP=0;
            max=leerMatri(texmat);
            if(max>0){
                for (int k=0;k<max;k++){
                    char codigo[8],NameM[25],HI[2],HP[2],C[2];
                    k=todo(k,texmat,codigo,NameM,HI,HP,C);
                    nHI=nHI+conv(HI);
                    nHP=nHP+conv(HP);
                    ncred=ncred+conv(C);
                    nmat++;
                }
                cout << "Tienes " << nmat << " materias matriculadas."<<endl;
                cout << "Equivalentes a " << ncred << " creditos."<<endl;
                cout << "Tienes que estudiar, en total, " << (nHP+nHI)*16 << " horas este semestre. ("<<nHP+nHI<<"/semana)"<<endl;
                cout << "De esas, "<< nHP*16 << " son horas de trabajo asistidas por el profesor. (" <<nHP<<"/semana)"<<endl;
                cout << "Es decir, debes estudiar "<<nHI*16<<" horas por tu cuenta por semana. ("<<nHI<<"/semana)"<<endl;
                cout << "Tomando en cuenta que estudiaras, por dia, 7 horas en semana y 4 los sabados... (39h/semana"<<endl;
                cout << "Te quedan " <<39-(nHP+nHI)<<" horas libres por semana."<<endl;
            }else{
                cout << "Para una mayor efectividad, debes matricular primero."<<endl;
            }


        }
            break;
        default:
        {
            cout << "No valido. Intenta de nuevo."<<endl;
        }
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

int extHora(int k,char texto[],char C[]){
    k++;
    for (int a=0;a<50;a++){
        if (texto[k]!=','){
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

int todo(int k,char texto[],char codigo[],char NameM[],char HI[],char HP[],char C[]){
    k=ExtCodigo(codigo,texto,k);
    k=extNombre(k,texto,NameM);
    k=HProf(k,texto,HP);
    k=HIndep(k,texto,HI);
    k=extCreditos(k,texto,C);
    return k;
}

void Matricular(char NameM[],char codigo[],char HI[],char HP[],char C[]){
    ofstream Matricula; // Para escribir en él.
    Matricula.open("Matricula.txt",ios::app); //Modo agregar
    Matricula<<codigo<<','<<NameM<<','<<HP<<','<<HI<<','<<C<<endl;
    Matricula.close();
}

int leerMatri(char tex_mat[]){
    ifstream archivo("Matricula.txt");
    int pos=0;
    if (archivo.is_open()) {
        while (archivo.good()) { //sin problemas de escritura, lectura, logica, etc.
            tex_mat[pos] = archivo.get();
            if (tex_mat[pos] != EOF) {
                pos++;
            }
        }
        tex_mat[pos] = '\0';
        archivo.close();
    }else {
        cout << "" <<endl;
    }
    return pos;
}

void RegHorario(char codigo[],char dia[],char hora[]){
    ofstream Horario; // Para escribir en él.
    Horario.open("Horario.txt",ios::app); //Modo agregar
    Horario<<codigo<<','<<dia<<','<<hora<<endl;
    Horario.close();
}

int leerHorario(char tex_hor[]){
    ifstream archivo("Horario.txt");
    int pos=0;
    if (archivo.is_open()) {
        while (archivo.good()) { //sin problemas de escritura, lectura, logica, etc.
            tex_hor[pos] = archivo.get();
            if (tex_hor[pos] != EOF) {
                pos++;
            }
        }
        tex_hor[pos] = '\0';
        archivo.close();
    }else {
        cout << "" <<endl;
    }
    return pos;
}

int conv(char C[]){
    int k=0;
    for (int a=0;a<1;a++){
        k=C[a]-48;
    }
    return k;
}

bool ComparaCadenas(char cadena1[],char cadena2[]){
    for(int i=0;i<=20;i++){
        if (cadena1[i]!=cadena2[i]){
            return false;
        }
        if(cadena1[i] == '\0' or cadena2[i] == '\0') {
            break;
        }
    }
    return true;
}

void ConvertirMay(char cadena[]) {
    for (int i = 0; i <= 30; i++) {
        if (cadena[i] == '\0') {
            break;
        }
        else if (cadena[i] > 96 and cadena[i] < 123) {
            cadena[i] -= 32;
        }
    }
}
