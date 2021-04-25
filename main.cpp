#include <iostream>
#include <vector>

using namespace std;

int n, R_t;
vector<int> W, R;


vector<int> sol; // Guarda la solucion parcial
bool es_sol(){
    int i = n-1;
    while (i > 0 && sol[i] != 1) i--;
    int R_temp = R[i];
    i--;
    while (i > 0) {
        if (sol[i] == 1) {
            if (R_temp >= W[i]) R_temp = R[i];
            else return false;
        }
        i--;
    }
    return true;
}

int recu_fb(int pos, int sum, int R_rem){
    // Caso base.
    if (pos == 0) 
        if (R_rem >= 0 && es_sol()) return sum;
        else return 0;

    // Recursion.
    int sum1 = 0;
    int sum2 = 0;
    sum1 = recu_fb(pos-1, sum, R_rem);
    sol[pos] = 1;
    sum2 = recu_fb(pos-1, sum+1, R_rem-W[pos]);
    return max(sum1, sum2);
}


int S = 0; // Mejor solucion hasta el momento.
int recu_bt(int pos, int sum, int R_rem){
    // Caso base.
    if (pos == 0){
        S = max(S, sum);
        return sum;
    }

    // Poda por optimalidad.
    if (S >= sum+pos) return S;

    // Recursion.
    int sum1 = recu_bt(pos-1, sum, R_rem);
    int sum2 = 0;

    // Poda por factibilidad.
    if (R_rem >= W[pos-1] && R[pos] >= W[pos-1])
        sum2 = recu_bt(pos-1, sum, R_rem-W[pos-1]);

    return max(sum1, sum2);
}

vector<vector <int> > memMat; //Matriz de memorizacion de nx(R_t+1).
int topdown_pd(int pos, int R_rem){
    if(pos == n || R_rem <= 0) { // Si terminamos de recorrer todo o nos quedamos sin capacidad, nada mas para agregar.
        return 0;
    }
    if(memMat[pos][R_rem] == -1) { // Si no ta memorizado, lo calculamos.
         //El maximo entre agregar o no agregar la posicion actual. Considerando la resistencia actual adecuadamente.
        memMat[pos][R_rem] = max(1 + topdown_pd(pos+1, min(R_rem-W[pos], R[pos])),
                                 topdown_pd(pos+1, min(R_rem, R[pos])));
    }
    //cout << pos << " " << R_rem << " " << memMat[pos][R_rem] << endl;
    return memMat[pos][R_rem];
}

int main(int argc, char** argv){
    // Leemos el input.
    cin >> n >> R_t;
    W.assign(n, 0);
    R.assign(n, 0);
    for (int i = 0; i < n; i++) cin >> W[i] >> R[i];

    // Fuerza bruta
    memMat = vector<vector <int> >(n, vector<int>(R_t+1, -1)); //Chocloide para inicializar la matriz en -1.
    cout << topdown_pd(0, R_t) << endl;

    // Backtracking


    // Programacion dinamica

}