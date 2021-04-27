#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <random>
#include <fstream>

using namespace std;

map<string, string> distribuciones_implementadas = {
    {"uniforme", "Uniforme"}, {"uniformeR", "Uniforme R"}, {"muchos", "Muchos productos"}, {"pocos", "Pocos productos"}, {"fullRandom", "Full Random"}
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
    path = path + "/" + distribucion;
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
    

    ofstream indice(path + "/indice.csv");
    indice << "dataset,instancia,n,W,archivo";

    for(int i=0; i<steps; i++) {
        for(int j=0; j<n; j++) {
            ofstream out;

            if(distribucion == "uniforme") {
                std::uniform_int_distribution<int> distrib(minVal, maxVal);

                int nActual = points[i];
                r_tubo = distrib(gen);

                string filename = "n" + to_string(nActual) + "_" + to_string(j) + ".in";
                out.open(path + "/" + filename);

                out << nActual << " " << r_tubo << "\n";
                for(int k=0; k<nActual; k++) out << distrib(gen) << " " << distrib(gen) << "\n";

                indice << "\n" << distribucion + "," + to_string(j) + "," + to_string(nActual) + "," + to_string(r_tubo) + "," + path + "/" + filename;
            }
            else if(distribucion == "muchos") {
                std::uniform_int_distribution<int> distrib(minVal, 2*r_tubo/points[i]);

                int nActual = points[i];

                string filename = "n" + to_string(nActual) + "_" + to_string(j) + ".in";
                out.open(path + "/" + filename);   


                out << nActual << " " << r_tubo << "\n";
                for(int k=0; k<nActual; k++) out << distrib(gen) << " " << r_tubo << "\n";

                indice << "\n" << distribucion + "," + to_string(j) + "," + to_string(nActual) + "," + to_string(r_tubo) + "," + path + "/" + filename;
            }
            else if(distribucion == "pocos") {
                std::uniform_int_distribution<int> distrib(0.2*r_tubo, 1.1*r_tubo);
                
                int nActual = points[i];

                string filename = "n" + to_string(nActual) + "_" + to_string(j) + ".in";
                out.open(path + "/" + filename);

                out << nActual << " " << r_tubo << "\n";
                for(int k=0; k<nActual; k++) out << distrib(gen) << " " << r_tubo << "\n";

                indice << "\n" << distribucion + "," + to_string(j) + "," + to_string(nActual) + "," + to_string(r_tubo) + "," + path + "/" + filename;
            }
            else if(distribucion == "uniformeR") {
                std::uniform_int_distribution<int> distrib(minVal, maxVal);

                int nActual = distrib(gen);
                r_tubo = points[i];

                string filename = "r" + to_string(r_tubo) + "_" + to_string(j) + ".in";
                out.open(path + "/" + filename);

                out << nActual << " " << r_tubo << "\n";
                for(int k=0; k<nActual; k++) out << distrib(gen) << " " << distrib(gen) << "\n";

                indice << "\n" << distribucion + "," + to_string(j) + "," + to_string(nActual) + "," + to_string(r_tubo) + "," + path + "/" + filename;
            }
            else if(distribucion == "fullRandom") {
                std::uniform_int_distribution<int> distrib(minVal, maxVal);

                int nActual = distrib(gen);
                r_tubo = distrib(gen);

                string filename = to_string(i*n+j) + ".in";
                out.open(path + "/" + filename);

                out << nActual << " " << r_tubo << "\n";
                for(int k=0; k<nActual; k++) out << distrib(gen) << " " << distrib(gen) << "\n";

                indice << "\n" << distribucion + "," + to_string(i*n+j) + "," + to_string(nActual) + "," + to_string(r_tubo) + "," + path + "/" + filename;
            }

            out.close();
        }
    }

    indice.close();
}