//#include "bibliotecas.h"

class LecturaMatriz {
    private:
        int n;
    public:
        LecturaMatriz();
        int ** leerArchivo();
        int getOrden();
        static void escribirEnArchivo(string, AdjacencyMatrix &);
        ~LecturaMatriz();
    private:
        vector < string > recuperarValores();
};

LecturaMatriz::LecturaMatriz() {
    this->n = 0;
}
LecturaMatriz::~LecturaMatriz() {}

int LecturaMatriz::getOrden() {
    return this->n;
}

int ** LecturaMatriz::leerArchivo() {
    int ** matrix;
    vector < string > valores = recuperarValores();
    this->n = valores.size() ;
    // inicializamos la matriz
    matrix = new int*[this->n];
    for (int i = 0; i < this->n; i++) matrix[i] = new int[this->n];

    int aux;
    int j;
    for (int i = 0; i < this->n; i++) {
        j = 0;
        stringstream fila(valores[i]);
        fila >> aux; // el que se ignora
        while(fila >> aux) {
            matrix[i][j] = aux;
            j++;
        }
    }
    return matrix;
}

vector < string > LecturaMatriz::recuperarValores() {
    string fila;
    vector < string > valores;
    ifstream archivo;
    archivo.open("matrix_ady.txt", ios::in);
    if(archivo.fail()) {
        cout << "Error al tratar de abrir el archivo de la matriz de adyacencia" << endl;
        exit(1);
    }
    while (!archivo.eof()) {
        getline(archivo, fila);
        valores.push_back(fila);
    }
    archivo.close();
    return valores;
}

void LecturaMatriz::escribirEnArchivo(string path, AdjacencyMatrix &A) {
    ofstream fs(path);
    cout << "\n";
    int ** matrix = A.getMatriz(); // Se recupera la matriz
    int tam = A.getTam(); // Y su tamaño
    for (int i = 0; i < tam; ++i) {
        for (int j = 0; j < tam; ++j) {
            fs << matrix[i][j] << " ";
        }
        fs << "\n";
    }
    fs.close();
}
/*
int main() {
    LecturaMatriz lector;
    int ** matrix = lector.leerArchivo();
    int n = lector.getOrden();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
*/
