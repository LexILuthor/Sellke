#include <iostream>
#include <fstream>
#include <vector>
#include<cstdlib>
#include<random>
#include "myFunctions.h"
#include "Sellke.h"


int main() {
    //std::srand(3453);
    char outputpath[] = "C:\\Users\\popcorn\\Desktop\\0\\UniTo\\Tesi\\Pugliese\\Modelli Probabilistici\\Sellke\\OutputFile\\sellke.csv";
    char inputpath[] = "C:\\Users\\popcorn\\Desktop\\0\\UniTo\\Tesi\\Pugliese\\Modelli Probabilistici\\Sellke\\OutputFile\\InputSellke.txt";

    //Population
    int N;

    //S->E
    double beta;

    // E-> I
    double ny;

    // I->R
    double gamma;


    std::string line;
    std::ifstream infile(inputpath);
    if (infile.is_open()) {
        getline(infile, line, ':');
        getline(infile, line);
        N = std::stoi(line);

        getline(infile, line, ':');
        getline(infile, line);
        beta = std::stod(line);

        getline(infile, line, ':');
        getline(infile, line);
        ny = std::stod(line);

        getline(infile, line, ':');
        getline(infile, line);
        gamma = std::stod(line);

        infile.close();
    } else std::cout << "Unable to open file";



    // Sellke algorithm.
    //"startInfection" will be the vector of the time the i-th individual become infected
    //"endInfection" will be the vector of the time the i-th individual ends to be infected
    //"time_vector" will be the vector of the time the i-th individual has the firs infectous contact
    std::vector<double> startInfection;
    std::vector<double> endInfection;
    std::vector<double> time_vector = sellke(N, beta, ny, gamma, startInfection, endInfection);
    int last_infected = startInfection.size() - 1;


    std::vector<double> timeline;
    int total_steps = (last_infected + 1) * 3;
    std::vector<std::vector<int> > SEIR(4, std::vector<int>(total_steps, 0));
    SEIR[0][0] = N;
    std::sort(startInfection.begin(), startInfection.end());
    std::sort(endInfection.begin(), endInfection.end());
    int t=0, s=0, e = 0;
    int caso = 0;

    while (t + s + e < total_steps-1) {
        if (t < last_infected + 1) {
            //setto caso uguale a:
            // 0 se il prossimo minimo è in time_vector (i.e avviene S->E)
            // 1 se il prossimo minimo è in startInfection (i.e. avviene E->I)
            // 2 se il prossimo nunimo è in endInfection (i.e. avviene I->R)
            std::vector<double> v{time_vector[t], startInfection[s], endInfection[e]};
            caso = std::min_element(v.begin(), v.end()) - v.begin();
        } else if (s < last_infected + 1) {
            std::vector<double> v{startInfection[s], endInfection[e]};
            caso = std::min_element(v.begin(), v.end()) - v.begin();
            caso++;
        } else {
            caso = 2;
        }
        int index = t + s + e;
        switch (caso) {
            case 0:
                //S->E
                timeline.push_back(time_vector[t]);
                t++;
                SEIR[0][index + 1] = SEIR[0][index] - 1;
                SEIR[1][index + 1] = SEIR[1][index] + 1;
                SEIR[2][index + 1] = SEIR[2][index];
                SEIR[3][index + 1] = SEIR[3][index];
                break;
            case 1:
                //E->I
                timeline.push_back(startInfection[s]);
                s++;
                SEIR[0][index + 1] = SEIR[0][index];
                SEIR[1][index + 1] = SEIR[1][index] - 1;
                SEIR[2][index + 1] = SEIR[2][index] + 1;
                SEIR[3][index + 1] = SEIR[3][index];
                break;
            case 2:
                //I->R
                timeline.push_back(endInfection[e]);
                e++;
                SEIR[0][index + 1] = SEIR[0][index];
                SEIR[1][index + 1] = SEIR[1][index];
                SEIR[2][index + 1] = SEIR[2][index] - 1;
                SEIR[3][index + 1] = SEIR[3][index] + 1;
                break;
            default:
                std::cout << "error\n";
        }

    }


    // writing on the csv file
    std::ofstream outfile(outputpath);
    if (!outfile.is_open()) {
        std::cout << "Unable to open file";
    } else {
        for (int i = 0; i < timeline.size(); i++) {

            outfile << SEIR[0][i] << ",\t" << SEIR[1][i] << ",\t" << SEIR[2][i] << ",\t" << SEIR[3][i] << ",\t"
                    << timeline[i] << "\n";
        }
        outfile.close();
    }

    
    return 0;

}




