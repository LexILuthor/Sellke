//
// Created by popcorn on 26/11/2020.
//



#include <iostream>
#include <vector>
#include<random>
#include <time.h>
#include "myFunctions.h"


void generate(std::vector<double> &Q, std::vector<double> &L, std::vector<double> &I, double ny, double gamma, int N) {
    // for random seed:
    std::default_random_engine generator(time(0));

    std::exponential_distribution<double> exp1_distribution(1.0);
    std::exponential_distribution<double> expNy_distribution(ny);
    std::exponential_distribution<double> expGamma_distribution(gamma);


    // Generate Q, L, I respectively the vectors of the resistance to the infection, expose time, infected time


    for (int i = 0; i < N; i++) {
        Q[i] = exp1_distribution(generator);
        L[i] = expNy_distribution(generator);
        I[i] = expGamma_distribution(generator);

        //function used to guarantee independence (may be not necessary)
        /*
        exp1_distribution.reset();
        expNy_distribution.reset();
        expGamma_distribution.reset();
         */
    }

    //the first one is already infected
    Q[0] = 0;
    //order Q
    std::sort(Q.begin(), Q.end());
}


void activeintervels(double from, std::vector<double> &startInfection, std::vector<double> &endInfection,
                     std::vector<size_t> indexEndInfection, int &last) {
    int numberofactiveintervals = 0;
    for (int j = 0; j < indexEndInfection.size(); j++) {
        int i = indexEndInfection[j];
        if (endInfection[i] < from) {
            last = j;
        } else if (startInfection[i] < from && endInfection[i] > from) {
            numberofactiveintervals++;
        }
    }
}
