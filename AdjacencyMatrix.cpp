#include "bibliotecas.h"
#include "herramientas.cpp"
// Por Onder
class AdjacencyMatrix{
    private:
        // Order of the matrix
        int tam;
        // Reserve memory
        int ** matrix;
    public:
        AdjacencyMatrix(int n);  // constructor
        ~AdjacencyMatrix(); //destructor
        void showMatrix(); //this function show all the values of the matrix
        void generateRandomMatrix(); //this function fill the matrix with random values
        void generateManualMatrix(); //with this function is posible insert values of manual way
        void generateZeroMatrix();
        void generarMatrizCombinacion(long long int combi,int tam);
        void generarMatrizCombinacion(string comb,int tam);
        bool queryPos(int x,int y); // with this function it is consulted a value of the matrix
        void showMatrix(vector < vector<int> >  index);
        void setPos(int x,int y,int value);
        void simetricReflex(int x,int y,int value);
        int getTam();// return the tam of the matrix
        int getNumeroNodos();
        int ** getMatriz();
        string enteroAbinario(long long int num,int tam);
        int numRepresntacion(long long int n);
        void setMatriz(int **);
};
AdjacencyMatrix::AdjacencyMatrix(int n){
    tam=n;
    //Create a array of arrays to dinamic way
    matrix = new int*[n];
    for (int i = 0; i < n; i++)
        matrix[i] = new int[n];
    }
void AdjacencyMatrix::showMatrix(){
    cout<<endl;
    for(int x=0;x<tam;x++){
        for(int y=0;y<tam;y++){
            cout<<matrix[x][y]<<" ";
        }
        cout<<endl;
    }
}
void AdjacencyMatrix::showMatrix(vector < vector<int> >  index){
    //hacer el aumento de espacios para cada uno
    cout<<endl;

    for(unsigned int i=0;i<index.size();i++){
        if(i==0){
            cout<<"   V"<<i+1<<" ";
        }else{
            cout<<"V"<<i+1<<" ";
        }

    }
    cout<<endl;
    for(int x=0;x<tam;x++){
        for(int y=0;y<tam;y++){
            if(y==0){
                cout<<"V"<<x+1<<Herramientas::getString(Herramientas::numDigitos(tam)-(Herramientas::numDigitos(x+1)))+" ";
            }
            cout<<matrix[x][y]<<Herramientas::getString((Herramientas::numDigitos(y+1)))+Herramientas::getString(y+1);
        }
        cout<<endl;
    }
}
void AdjacencyMatrix::generateRandomMatrix(){
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<unsigned int> dis;
    int num;
    for(int x=0;x<tam;x++){
        for(int y=x;y<tam;y++){
            if(x==y){
                matrix[x][y]=0;
            }
    	  	else if(x!=y){
                  num=dis(gen) % 2;
                  simetricReflex(x,y,num);
    		      //matrix[x][y]=num;
                  //matrix[y][x]=num;
    	    }
        }
    }
}
void AdjacencyMatrix::generateManualMatrix(){
    for(int x=0;x<tam;x++){
        for(int y=0;y<tam;y++){
            cout<<"("<<x+1<<","<<y+1<<")"<<endl;
            scanf("%d", &matrix[x][y]);
        }
    }
}
void AdjacencyMatrix::generateZeroMatrix(){
    for(int x=0;x<tam;x++){
        for(int y=0;y<tam;y++){
            matrix[x][y]=0;
        }
    }
}
void AdjacencyMatrix::generarMatrizCombinacion(long long int comb,int tam){
    int aux;
    //Convertir el número a binario
    string combinacion = enteroAbinario(comb,tam);
    int pos=0;
    for(int x=0;x<tam;x++){
        for(int y=x;y<tam;y++){
            if(x==y){
                matrix[x][y]=0;
            }
    	  	else if(x!=y){
                  aux = combinacion[pos]=='1'?1:0;
                  simetricReflex(x,y,aux);
                  pos++;
    	    }
        }
    }

}
void AdjacencyMatrix::generarMatrizCombinacion(string comb,int tam){
    int aux;
    //Combertir el numero a binario
    string combinacion = comb;
    int pos=0;
    for(int x=0;x<tam;x++){
        for(int y=x;y<tam;y++){
            if(x==y){
                matrix[x][y]=0;
            }
    	  	else if(x!=y){
                  aux = combinacion[pos]=='1'?1:0;
                  simetricReflex(x,y,aux);
                  pos++;
    	    }
        }
    }

}
int AdjacencyMatrix::numRepresntacion(long long int n){
    if(n==0)return 1;
    int c=0;
    int bin=1;
    while(bin<=n){
        bin=bin<<1;
        c++;
    }
    return c;
}
//nesita el tamaño para rellenar
string AdjacencyMatrix::enteroAbinario(long long int num,int tam){
    string cadena="";
    int sup = numRepresntacion(num);
    int i = 0;
    while(sup > i){
        if(num & (((long int)1) << i))
            cadena+="1";
        else{
            cadena+="0";
        }
        i++;
    }
    string cadena2="";
    if(cadena.length()==(tam*tam -tam)/2)
        return cadena;
    for(int i=cadena.length();i<(tam*tam -tam)/2;i++){
        cadena2+="0";
    }
    string aux_cadena = "";
    for (int i = cadena.size(); i >=0 ; i--)
         aux_cadena += cadena[i];
    return cadena2+=aux_cadena;
}
bool AdjacencyMatrix::queryPos(int x,int y){
    if(matrix[x][y]==1){
        return true;
    }else{
        return false;
    }
}
int AdjacencyMatrix::getTam(){
    return tam;
}
int ** AdjacencyMatrix::getMatriz() {
    return matrix;
}
void AdjacencyMatrix::setMatriz(int **matrixx) {
    this->matrix = matrixx; // se setea la matriz
}
void AdjacencyMatrix::simetricReflex(int x,int y,int value){
    setPos(x,y,value);
    setPos(y,x,value);

}
void AdjacencyMatrix::setPos(int x,int y,int value){
    matrix[x][y]=value;
}
int AdjacencyMatrix::getNumeroNodos(){
    int nodos=0;
    for(int x=0;x<tam;x++){
        for(int y=x;y<tam;y++){
            if(matrix[x][y]==1){
                nodos++;
            }
        }
    }
    return nodos;
}

AdjacencyMatrix::~AdjacencyMatrix(){
    /*for(int x=0;x<tam;x++){
        for(int y=0;y<tam;y++){
            matrix[x][y]='\0';
        }
    }*/

    for (int i = 0; i < tam; ++i)
        delete matrix[i];
    delete matrix;
}
