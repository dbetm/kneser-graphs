#include "AdjacencyMatrix.cpp"
#include "combinacion_alter.cpp"
#include "leerArchivoMatrizAdyacencia.cpp"

// Prototipos de funciones
AdjacencyMatrix construirMatrizOriginal(int &n);
void generarGrafoKneser(AdjacencyMatrix &A, int n, int k);
string obtenerNombreCarpeta(int tam, int k);
string obtenerNombreArchivo(int n, int k);
void construirMatrizToken(vector <vector<int> > vv, AdjacencyMatrix &mg, AdjacencyMatrix &A);
void escribirArchivos(Combinacion_alter &ca, AdjacencyMatrix &mg, AdjacencyMatrix &A, string carpeta);
void escribirEntrada(ofstream &fs, AdjacencyMatrix &A);
void escribirListaVectores(ofstream &fs, vector < vector < int > > vv);
void escribirMatrizKneser(ofstream &fs, AdjacencyMatrix &mg, vector < vector < int > > vv);
void escribirRutaImagen(string ruta);

int main() {
	system("cls");   // Limpiar la consola en Windows
	int n = 0, k;
	AdjacencyMatrix A = construirMatrizOriginal(n);

	cout << "\n\nEntrada: " << endl;
    A.showMatrix();

	cout << "Ingresa k, para poder calcular G = kG(n,k): ";
	cin >> k;
	generarGrafoKneser(A, n, k);
	return 0;
}

AdjacencyMatrix construirMatrizOriginal(int &n) {
    int opcion;
    cout << "Inserte la forma de construccion de la matriz: "<< endl;
    cout << "(1) Forma automatica" << endl;
    cout << "(2) Forma manual" << endl;
    cout << "(3) Leer desde archivo" << endl;
    do {
        cout << ">> ";
        cin >> opcion;
        if(opcion == 1 || opcion == 2) {
            cout << "Inserte el orden de la matriz de adyacencia" << endl;
            cin >> n;
            break;
        }
        if(opcion == 1 || opcion == 2 || opcion == 3) break;
        else cout << "Elija una opcion valida" << endl;
    } while(true);

    int **matrix;
    if(opcion == 3) {
    	LecturaMatriz lector;
        matrix = lector.leerArchivo();
        n = lector.getOrden();
        cout << "\nLa matriz leida desde el archivo es de orden " << n  << endl;
    }
	
	// Instanciamos la matriz original
    AdjacencyMatrix A(n);
    if(opcion == 1) A.generateRandomMatrix(); // Se genera de forma aleatoria
    else if(opcion == 2) A.generateManualMatrix(); // El usuario introduce cada valor
    else A.setMatriz(matrix); // Se define la matriz generada del archivo    

    return A;
}

void generarGrafoKneser(AdjacencyMatrix &A, int n, int k) {
	// Escribir la matriz original en el archivo
	LecturaMatriz::escribirEnArchivo("archivosWolfram/matrix.txt", A);
	string carpeta = obtenerNombreCarpeta(A.getTam(), k);
	// Crear la carpeta
	system(("mkdir " + carpeta).c_str());
	// Moverse a esa carpeta
	system(("cd " + carpeta).c_str());
	// Se escribe la ruta para guardar la imagen del original
    escribirRutaImagen("../" + carpeta + "/entrada.png");
    // Se ejecuta el script de wolfram
    system("wolframscript -file archivosWolfram/generateImage.wl");

    // Hacemos la combinación
    Combinacion_alter ca(n, k);
    vector < vector<int> > vectores;
    vectores = ca.getVectores();
    AdjacencyMatrix mg(vectores.size());
    mg.generateZeroMatrix();
    construirMatrizToken(vectores, mg, A);
    LecturaMatriz::escribirEnArchivo("archivosWolfram/matrix.txt", mg);
    // Se escribe la ruta para guardar la imagen
    escribirRutaImagen("../" + carpeta + "/Kneser_" + to_string(n) + "n_" + to_string(k) + "k.png");
    system("wolframscript -file archivosWolfram/generateImage.wl");

    escribirArchivos(ca, mg, A, carpeta);
    cout << "\nSe han escrito los archivos en: " << carpeta << endl;
}

string obtenerNombreCarpeta(int tam, int k) {
    // Ejemplo: 2n__2019_9_2__07%56%15
    time_t t = time(0);   // get time now
    tm* now = localtime(&t);

    string date = to_string(now->tm_year + 1900) + "_";
    date += to_string(now->tm_mon + 1) + "_" + to_string(now->tm_mday);
    // Se construye la hora
    string hour;
    if(now->tm_hour < 10) hour = "0" + to_string(now->tm_hour);
    else hour = to_string(now->tm_hour);
    // Los minutos
    string min;
    if(now->tm_min < 10) min = "0" + to_string(now->tm_min);
    else min = to_string(now->tm_min);
    // Los segundos
    string sec;
    if(now->tm_sec < 10) sec = "0" + to_string(now->tm_sec);
    else sec = to_string(now->tm_sec);
    // Formamos la cadena HH:MM
    string tiempo = "__" + hour + "%" + min + "%" + sec;
    date += tiempo;
    string nombre = to_string(tam) + "n__" + to_string(k) + "k__" + date;
    return nombre;
}

string obtenerNombreArchivo(int n, int k) {
    // Ejemplo: n6_k2.txt
    string nombre = "n"  +  std::to_string(n)  +  " k"  +  std::to_string(k)  +  ".txt";
    return nombre;
}

void construirMatrizToken(vector <vector<int> > vv, AdjacencyMatrix &mg, AdjacencyMatrix &A) {
    vector <int> aux;
    int n = vv.size();
    /* Se genera la matriz triangular superior G(k), y automáticamente se
    va haciendo el reflejo, ya que es simétrica. */
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            /* Se guarda el vector resultado en aux de la diferencia
            simétrica */
            aux = Herramientas::intersectarConjuntos(vv[i], vv[j]);
            /* El tamaño del vector resultado es z, si z es igual a 0 entonces
            existe la adyacencia */
            if(aux.size() == 0) {
            	mg.simetricReflex(i, j, 1);
            }
        }
    }
}

void escribirArchivos(Combinacion_alter &ca, AdjacencyMatrix &mg, AdjacencyMatrix &A, string carpeta) {
    string nombre = obtenerNombreArchivo(ca.getNumeroVertices(), ca.getToken());
    string path = carpeta + "/" + nombre;
    ofstream fs(path);
    vector < vector<int> > vectores = ca.getVectores();
    escribirEntrada(fs, A);
    escribirListaVectores(fs, vectores);
    if(mg.getTam() < 50) escribirMatrizKneser(fs, mg, vectores);
    else fs << "\nMatriz muy grande" << endl;
    fs.close();
}

void escribirEntrada(ofstream &fs, AdjacencyMatrix &A) {
    int ** matrix = A.getMatriz(); // Se recupera la matriz
    int tam = A.getTam(); // Y su tamaño
    fs << "Entrada: " << endl;
    for(int x = 0; x < tam; x++){
        for(int y = 0; y < tam; y++){
            fs << matrix[x][y] << " ";
        }
        fs << "\n";
    }
    fs << "---------------------------------------" << endl;
}

void escribirListaVectores(ofstream &fs, vector < vector < int > > vv) {
    fs << "Lista de vectores:" << endl;
    int n = vv.size();
    if(!vv.empty()) {
        for (int i = 0; i < n; i++) {
            fs << "V" << i + 1 << "=" << "(";
            for (size_t j = 0; j < vv[i].size(); j++) {
                if(j != vv[i].size() - 1)
                    fs << vv[i][j] << ",";
                else
                    fs << vv[i][j];
            }
            fs << ") "<<endl;
        }
    }
    else fs << "El conjunto esta vacio." << endl;
}

void escribirMatrizKneser(ofstream &fs, AdjacencyMatrix &mg, vector < vector < int > > vv) {
    fs << "\nMatriz generada con k:" << endl;
    int n = vv.size();
    for(int i = 0; i < n; i++) {
        if(i == 0) fs << "   V" << i+1 << " ";
        else fs << "V" << i+1 << " ";
    }
    fs << endl;
    int tam = mg.getTam(); // recuperamos el tamaño de la matriz
    int **matrix = mg.getMatriz(); // y se recupera la matriz
    for(int x = 0;x < tam;x++) {
        for(int y = 0; y < tam; y++) {
            if(y == 0) {
                fs << "V" << x+1 << Herramientas::getString(Herramientas::numDigitos(tam)-(Herramientas::numDigitos(x+1))) + " ";
            }
            fs << matrix[x][y] << Herramientas::getString((Herramientas::numDigitos(y+1)))+Herramientas::getString(y+1);
        }
        fs << endl;
    }
}

void escribirRutaImagen(string ruta) {
    ofstream fs("archivosWolfram/rutaImagen.txt");
    fs << ruta;
    // Cerramos el archivo
    fs.close();
}