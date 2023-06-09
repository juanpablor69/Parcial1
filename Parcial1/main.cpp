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
            char texto[1200];
            cout << "*** MATERIAS PRIMER SEMESTRE ***"<<endl;
            leerPensum(texto);
            cout << texto <<endl;
        }
            break;
        case 2: // MATRICULAR
        {
            system("cls");
            bool ok=true,existe=false;
            char texto[1200],codigo[8],NameM[25],HI[2],HP[2],C[2];
            char texto_[600];//,codigo_[8],NameM_[25],HI_[2],HP_[2],C_[2];
            char mat[8];
            leerPensum(texto);
            cout << "OFERTA DE MATERIAS."<<endl;
            cout<<texto<<endl;
            if (leerMatri(texto_)>0){ //analiza pensum
                cout << "\nEscribe el codigo de la materia que quieres matricular: ";
                cin >> mat;
                for (int k=0;k<1850;k++){
                    k=todo(k,texto,codigo,NameM,HI,HP,C);
                    if(ComparaCadenas(mat,codigo)){
                        //buscando si se repite
                        existe=true;
                        for (int i=0;i<leerMatri(texto_);i++){
                            char codigo_[8],NameM_[25],HI_[2],HP_[2],C_[2];
                            i=todo(i,texto_,codigo_,NameM_,HI_,HP_,C_);
                            if (ComparaCadenas(codigo,codigo_)){
                                ok=false;
                            }
                        }
                        if(ok){
                            cout <<"Has matriculado exitosamente: "<<NameM<<"."<<endl;
                            Matricular(NameM,codigo,HI,HP,C);
                            break;
                        }else{
                            cout<<"ERROR!: " << NameM<<" ya esta matriculada."<<endl;
                        }
                    }
                }
                if(!existe){
                    cout<<"\nEl codigo que ingresaste no se encontro."<<endl;
                }
            }
            else{
                cout << "Escribe el codigo de la materia que quieres matricular: ";
                cin >> mat;
                for (int k=0;k<1800;k++){
                    k=todo(k,texto,codigo,NameM,HI,HP,C); //una materia matriculada
                    if(ComparaCadenas(mat,codigo)){
                        existe=true;
                        cout <<"Has matriculado exitosamente: "<<NameM<<"."<<endl;
                        Matricular(NameM,codigo,HI,HP,C);
                        break;
                    }
                }
                if(!existe){
                    cout<<"\nEl codigo que ingresaste no se encontro."<<endl;
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
            int max,cont_h=0,htotal,hfaltan,hora_;
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
                        cout <<"Tienes " <<cont_h<<" hora(s) registradas de esta materia."<<endl;
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
                            hora_=conv(hora);
                            if (hora_<8 or hora_>21){
                                cout<<"No duerme??"<<endl;
                            }else{
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
            char texmat[200],tex_hor[150];
            int max,nHI=0,nHP=0,nmat=0,ncred=0;
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
                cout << "------------------- SEGUN TUS MATERIAS: ----------------------"<<endl;
                cout << "Tienes " << nmat << " materias matriculadas."<<endl;
                cout << "Equivalentes a " << ncred << " creditos."<<endl;
                cout << "Tienes que estudiar, en total, " << (nHP+nHI)*16 << " horas este semestre. ("<<nHP+nHI<<"/semana)"<<endl;
                cout << "De esas, "<< nHP*16 << " son horas de trabajo asistidas por el profesor. (" <<nHP<<"/semana)"<<endl;
                cout << "Es decir, debes estudiar "<<nHI*16<<" horas por tu cuenta este semestre. ("<<nHI<<"/semana)"<<endl;
                cout << "Tomando en cuenta que estudiaras, por dia, 7 horas en semana y 4 los sabados... (39h/semana"<<endl;
                cout << "Podrias matricular otras " <<39-(nHP+nHI)<<" horas por semana. (horas para matricular mas materias)"<<endl;

                cout << "\n------------------------------------------------------------"<<endl;
                cout << "----------------------- SEGUN TU HORARIO: --------------------"<<endl;
                int hora,dia_;
                char n[15]="-----------",mat[20],dia;
                char ***Horario = new char**[15]; // crear arreglo de punteros a punteros a caracteres

                for (int i = 0; i < 15; i++) {
                    Horario[i] = new char*[7]; // crear arreglo de punteros a caracteres para cada hora
                    for (int j = 0; j < 6; j++) {
                        Horario[i][j] = new char[25]; // crear arreglo de caracteres para cada
                        Horario[i][j]=n; // copiar la cadena en la celda de la matriz
                    }
                }

                for (int i=0;i<leerHorario(tex_hor);i++){ // -- analiza horario y verifica hora.
                    char codigo_[8],hora_[1],diaL_[1];
                    int dia_,hora1;
                    i=ExtCodigo(codigo_,tex_hor,i);
                    i=extHora(i,tex_hor,diaL_);//DIA
                    i=extCreditos(i,tex_hor,hora_); //hora
                    if(diaL_[0]=='L'){
                        dia_=0;
                    }else if(diaL_[0]=='M'){
                        dia_=1;
                    }else if(diaL_[0]=='W'){
                        dia_=2;
                    }else if(diaL_[0]=='J'){
                        dia_=3;
                    }else if(diaL_[0]=='V'){
                        dia_=4;
                    }else if(diaL_[0]=='S'){
                        dia_=5;
                    }
                    hora1=conv(hora_);
                    hora1-=8;
                    for (int j=0;j<15;j++){
                        for (int k=0;k<6;k++){
                            if (k==dia_ and j==hora1){
                                cout<<"entro"<<endl;
                                Horario[j][k]=codigo_;
                            }
                        }
                    }
                }

                cout<<  "     Lunes       Martes      Miercoles        Jueves      Viernes      Sabado"<<endl;
                for (int i=0;i<14;i++){
                    cout << i+8 << "h";
                    for (int k=0;k<6;k++){
                        cout << " " << Horario[i][k] << " ";
                    }
                    cout << endl;
                }
                delete[] Horario;
                Horario = nullptr;





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
