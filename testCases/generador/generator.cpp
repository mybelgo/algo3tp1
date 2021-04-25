#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <random>
#include <fstream>

using namespace std;

map<string, string> distribuciones_implementadas = {
    {"u", "Uniforme"}
};

int main(int argc, char** argv){
    if (argc < 2 || distribuciones_implementadas.find(argv[1]) == distribuciones_implementadas.end())
	{
		cerr << "Distribucion no encontrada: " << argv[1] << endl;
		cerr << "Las distribuciones existentes son: " << endl;
		for (auto& alg_desc: distribuciones_implementadas) cerr << "\t- " << alg_desc.first << ": " << alg_desc.second << endl;
		return 0;
	}
    string distribucion = argv[1];

    int steps, n;
    int r_tubo, minVal, maxVal;
    string path;
    cin >> path;
    cin >> r_tubo >> minVal >> maxVal;
    cin >> n >> steps;
    vector<int> points(steps, 0);
    for(int i=0; i<steps; i++) cin >> points[i];

    std::random_device rd;
    std::mt19937::result_type seed = rd() ^ (
            (std::mt19937::result_type)
            std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now().time_since_epoch()
                ).count() +
            (std::mt19937::result_type)
            std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::high_resolution_clock::now().time_since_epoch()
                ).count() );

    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> distrib(minVal, maxVal);

    ofstream indice(path + "/indice.csv");
    indice << "dataset,instancia,n,W,archivo";

    for(int i=0; i<steps; i++) {
        for(int j=0; j<n; j++) {
            string filename = "n" + to_string(points[i]) + "_" + to_string(j) + ".in";
            ofstream out(path + "/" + filename);

            out << points[i] << " " << r_tubo;
            for(int k=0; k<points[i]; k++) out << "\n" << distrib(gen) << " " << distrib(gen);

            indice << "\n" << distribucion + "," + to_string(j) + "," + to_string(points[i]) + "," + to_string(r_tubo) + "," + path + "/" + filename;
            out.close();
        }
    }

    indice.close();
}