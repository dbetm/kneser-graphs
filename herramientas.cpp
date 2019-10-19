#include "bibliotecas.h"

class Herramientas {
    // Métodos
    public:
        static int combinatoria(int, int);
        static int factorial(int);
        static vector<int> intersectarConjuntos(vector<int>, vector<int>);
        static int numDigitos(int);
        static string getString(int);
};

// Calcula la combinatoria n! / [r! (n-r)!]
// Programación dinámica
int Herramientas::combinatoria(int n, int r) {
    int C[r+1];
    memset(C, 0, sizeof(C));
    C[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = min(i, r); j > 0; j--) {
            C[j] = C[j]+ C[j-1];
        }
    }
    return C[r];
}

string Herramientas::getString(int num){
    int tamE=numDigitos(num);
    string espacio="";
    for(int i=0;i<tamE;i++){
        espacio+=" ";
    }
    return espacio;
}
int Herramientas::numDigitos(int num){
    int contador = 0;

    while(num > 0) {
        //num=num%10;
        num/=10;
        contador++;
    }
    return contador;
}

vector<int> Herramientas::intersectarConjuntos(vector<int> set1, vector<int> set2) {
    vector<int> resultado(set1.size() + set2.size());
    vector<int>::iterator it;
    // Ordenamos ambos conjuntos
    sort(set1.begin(), set1.end());
    sort(set2.begin(), set2.end());

    it = set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), resultado.begin());

    resultado.resize(it-resultado.begin());

    return resultado;
}


/*int main() {
    // Aquí hacer pruebas unitarias
    return 0;
}*/
