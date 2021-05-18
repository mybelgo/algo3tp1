#include <iostream>
#include <vector>
#include <map>
#include <chrono>

using namespace std;

map<string, string> algoritmos_implementados = {
    {"FB", "Fuerza Bruta"}, {"BT", "Backtracking con podas"}, {"BT-F", "Backtracking con poda por factibilidad"}, {"BT-O", "Backtracking con poda por optimalidad"}, {"DP", "Programacion dinámica"}};

int n, R_t;
vector<int> W, R;

int recu_fb(int pos, int sum, int R_rem)
{
    // Caso base.
    if (pos == n)
        return R_rem < 0 ? 0 : sum;

    // Recursion
    return max(recu_fb(pos + 1, sum, R_rem), recu_fb(pos + 1, sum + 1, min(R_rem - W[pos], R[pos])));
}

bool poda_factibilidad = true; // define si la poda por factibilidad esta habilitada.
bool poda_optimalidad = true;  // define si la poda por optimalidad esta habilitada.
int S = 0;                     // Mejor solucion hasta el momento.
int recu_bt(int pos, int sum, int R_rem)
{
    //cout << pos << " " << sum << " " << R_rem << endl;
    //cout << "CB\n";
    // Caso base.
    if (pos == n)
    {
        if (R_rem < 0)
            return 0;
        S = max(S, sum);
        return sum;
    }

    //cout << "P O\n";
    // Poda por optimalidad.
    if (poda_optimalidad && (S >= sum + (n - pos))) {
        //cout << "Poda O.\n";
        return 0;
    }
    
    //cout << "P F\n";
    // Poda por factibilidad.
    if (poda_factibilidad && (R_rem < 0)) {
        //cout << "Poda F.\n";
        return 0;
    }

    //cout << "RECU\n";
    // Recursion
    return max(recu_bt(pos + 1, sum, R_rem), recu_bt(pos + 1, sum + 1, min(R_rem - W[pos], R[pos])));
}

vector<vector<int>> memMat; //Matriz de memorizacion de nx(R_t+1).
int topdown_pd(int pos, int R_rem)
{
    // Si terminamos de recorrer todo o nos quedamos sin capacidad, nada mas para agregar.
    if (pos == n || R_rem < 0)
        return 0;

    // Si no ta memorizado, lo calculamos.
    if (memMat[pos][R_rem] == -1)
    { // Si no ta memorizado, lo calculamos.
        //El maximo entre agregar o no agregar la posicion actual. Considerando la resistencia actual adecuadamente.
        memMat[pos][R_rem] = max(1 + topdown_pd(pos + 1, min(R_rem - W[pos], R[pos])),
                                 topdown_pd(pos + 1, R_rem));
    }
    //cout << pos << " " << R_rem << " " << memMat[pos][R_rem] << endl;
    return memMat[pos][R_rem];
}

int main(int argc, char **argv)
{
    // Verificar que el algoritmo pedido exista.
    if (argc < 2 || algoritmos_implementados.find(argv[1]) == algoritmos_implementados.end())
    {
        cerr << "Algoritmo no encontrado: " << argv[1] << endl;
        cerr << "Los algoritmos existentes son: " << endl;
        for (auto &alg_desc : algoritmos_implementados)
            cerr << "\t- " << alg_desc.first << ": " << alg_desc.second << endl;
        return 0;
    }
    string algoritmo = argv[1];

    // Leemos el input.
    cin >> n >> R_t;
    W.assign(n, 0);
    R.assign(n, 0);
    for (int i = 0; i < n; i++)
        cin >> W[i] >> R[i];

    int resultado = -1;
    auto start = chrono::steady_clock::now();
    if (algoritmo == "FB")
    {
        resultado = recu_fb(0, 0, R_t);
    }
    else if (algoritmo == "BT")
    {
        poda_factibilidad = true;
        poda_optimalidad = true;
        resultado = recu_bt(0, 0, R_t);
    }
    else if (algoritmo == "BT-F")
    {
        poda_factibilidad = true;
        poda_optimalidad = false;
        resultado = recu_bt(0, 0, R_t);
    }
    else if (algoritmo == "BT-O")
    {
        poda_factibilidad = false;
        poda_optimalidad = true;
        resultado = recu_bt(0, 0, R_t);
    }
    else if (algoritmo == "DP")
    {
        memMat = vector<vector<int>>(n, vector<int>(R_t + 1, -1)); // Chocloide para inicializar la matriz en 0.
        resultado = topdown_pd(0, R_t);
    }
    auto end = chrono::steady_clock::now();
    double total_time = chrono::duration<double, milli>(end - start).count();

    // Imprimimos el tiempo de ejecución por stderr.
    clog << total_time << endl;

    // Imprimimos el resultado por stdout.
    cout << resultado << endl;
    return 0;
}