#include <iostream>
#include <vector>

using namespace std;

int n;
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

int topdown_pd(){
    
}

int main(int argc, char** argv){
    // Leemos el input.
    int R_t;
    cin >> R_t >> n;
    W.assign(n, 0);
    R.assign(n, 0);
    for (int i = 0; i < n; i++) cin >> W[i];
    for (int i = 0; i < n; i++) cin >> R[i];

    // Fuerza bruta
    sol.assign(n, 0);
    cout << recu_fb(n-1, 0, R_t);

    // Backtracking


    // Programacion dinamica

}