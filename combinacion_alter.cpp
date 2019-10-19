#include "bibliotecas.h"

class Combinacion_alter {
    // Atributos
    private:
        int n;
        int k;
        vector < vector<int> > vectores;
    // Métodos
    public:
        Combinacion_alter(int, int);
        int getNumeroVertices();
        int getToken();
        vector < vector<int> > getVectores();
        void imprimirVectores();
        ~Combinacion_alter();
    private:
        void generarCombinacion();
};

Combinacion_alter::Combinacion_alter(int n, int k) {
    this->n = n;
    this->k = k;
    generarCombinacion();
}
// Genera los vectores
void Combinacion_alter::generarCombinacion() {
    int i;
    vector <char> c(100000);
    // Se generan los elementos del primer vector
    for (i = 0; i < k; i++) c[i] = k - i;
    // Se generan el resto de vectores y se van agregando a la colección
    while(1) {
        // vector auxiliar
        vector <int> aux(k);
        // recorre desde, k-1 hasta 0
        for (i = k; i--;) {
            aux[k - 1 - i] = c[i];
        }
        // se agrega a la colección
        vectores.push_back(aux);
        /* La siguiente comprobación no es estrictamente necesaria, pero
        si n no está cerca de k, hace que todo sea un poco más rápido.*/
        i = 0;
        if(c[i]++ < n) continue;

        for(; c[i] >= n - i;)
            if(++i >= k) return;
        for(c[i]++; i; i--)
            c[i - 1] = c[i] + 1;
    }
}

int Combinacion_alter::getNumeroVertices() {
    return this->n;
}

int Combinacion_alter::getToken() {
    return this->k;
}

vector < vector<int> > Combinacion_alter::getVectores() {
    return this->vectores;
}

void Combinacion_alter::imprimirVectores() {
    if(!vectores.empty()) {
        for (size_t i = 0; i < vectores.size(); i++) {
            cout<<"V"<<i+1<<"="<<"(";
            for (size_t j = 0; j < vectores[i].size(); j++) {
                if(j!=vectores[i].size()-1){
                    cout << vectores[i][j] << ",";
                }else{
                    cout << vectores[i][j];
                }

            }
            cout <<") "<<endl;
        }
    }
    else cout << "El conjunto está vacío." << endl;
}

Combinacion_alter::~Combinacion_alter() {
    if(vectores.empty()) vectores.clear();
}

// Pruebas unitarias
/*int main() {
    int n = 11, k = 2;
    // Instanciamos una nueva combinación
    Combinacion_alter ca(n, k);
    // Llamamos el método para imprimir los vectores generados
    ca.imprimirVectores();
    return 0;
}*/
