//
// Created by popcorn on 29/11/2020.
//

#ifndef SELLKE_SELLKE_H
#define SELLKE_SELLKE_H

#endif //SELLKE_SELLKE_H


std::vector<double> sellke(int N, double beta, double ny, double gamma, std::vector<double> &startInfection,
                                std::vector<double> &endInfection);


double integral(double from,  int last_infected, std::vector<double> &startInfection,
                std::vector<double> &endInfection, double &integral_value, std::vector<double> &Q,double beta);

