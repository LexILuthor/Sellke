//
// Created by popcorn on 29/11/2020.
//


#include <vector>
#include <iostream>
#include "myFunctions.h"
#include "Sellke.h"

std::vector<double> sellke(int N, double beta, double ny, double gamma, std::vector<double> &startInfection,
                           std::vector<double> &endInfection) {




    // Generate Q, L, I respectively the vectors of the resistance to the infection, expose time, infected time
    std::vector<double> Q(N);
    std::vector<double> L(N);
    std::vector<double> I(N);

    //generates the vectors and order Q
    generate(Q, L, I, ny, gamma, N);




    //vector containing at the i-th position the time of first infectious contact of individual i
    std::vector<double> time_vector(N, -1);
    time_vector[0] = 0;

    //indice della persona infettata più di recente
    int last_infected = 0;

    // Ultimo tempo t fino al quale l'integrale è conosciuto
    //coinciderà sempre con l'ultimo elemento di "time_vector" tranne che per questo primo step
    double ts = L[0];

    //valore dell'integrale tra 0 e ts
    double integral_value;
    integral_value = 0;

    //per ogni cella i abbaimo il tempo in cui l'individuo i-esimo comincia ad essere infetto e smette di essere infetto
    //nota che in realtà endInfection=startInfection+I dove I è il vettore degli infected time, mentre
    //startInfection = time_vector+ L dove L è il vettore degli exposed times


    startInfection.push_back(L[0]);
    endInfection.push_back(L[0] + I[0]);

    int number_of_active_intervals = 0;
    int last_event_R = 0;
    while (last_infected < N - 1) {
        ts = integral(ts, last_infected, startInfection, endInfection, integral_value, Q, (beta / N),
                      number_of_active_intervals,last_event_R);
        if (ts == -1) {
            //non abbiamo più nuovi contagi
            break;
        } else {
            last_infected++;
            time_vector[last_infected] = ts;
            startInfection.push_back(ts + L[last_infected]);
            endInfection.push_back(ts + L[last_infected] + I[last_infected]);
            //teoricamente il comando seguente è già vero
            integral_value = Q[last_infected];
        }

    }

    //check function

    int z = 0;
    double sum;
    sum = I[z] * (beta / N);
    while (Q[z + 1] <= sum && z < Q.size() - 1) {
        z++;
        sum = sum + (I[z] * (beta / N));
    }
    std::cout << "Theoretical: " << z << "\n";
    std::cout << "Computed: " << last_infected << "\n";


    return time_vector;

}


double integral(double from, int last_infected, std::vector<double> &startInfection,
                std::vector<double> &endInfection, double &integral_value, std::vector<double> &Q, double beta,
                int &numberofactiveintervals,int &last_event_R) {
    std::vector<size_t> indexStartInfection = sort_indexes(startInfection);
    std::vector<size_t> indexEndInfection = sort_indexes(endInfection);

    //compute the number of intervals that contains "from", it also sets not_ordered_j to the last individual before from
    //int last_event_R;
    //activeintervels(from, startInfection, endInfection, indexEndInfection, last_event_R);
    int last_event_I = last_event_R;

    double last_from = from;
    bool check = true;
    while (last_event_I < indexStartInfection.size() || last_event_R < indexEndInfection.size()) {
        int i = 0;
        int j = indexEndInfection[last_event_R];
        if (last_event_I >= indexStartInfection.size()) {
            check = false;
        } else {
            i = indexStartInfection[last_event_I];
        }

        if (startInfection[i] < endInfection[j] && check) {
            if (startInfection[i] >= last_from) {
                // nota che "last_from" si potrebbe sostituire con "from"
                if (integral_value + numberofactiveintervals * beta * (startInfection[i] - last_from) >=
                    Q[last_infected + 1]) {
                    // from qui diventa il tempo t al quale il nuovo infetto Q[last_infected+1] subisce il contatto infetto
                    from = (double) (Q[last_infected + 1] - integral_value +
                                     (numberofactiveintervals * beta * last_from)) /
                           (numberofactiveintervals * beta);


                    //comando inutile, è solo di controllo
                    // NB se si toglie controllare che il comando
                    // integral_value = Q[last_infected];
                    // a riga 64 sia attivo
                    //integral_value = integral_value + numberofactiveintervals * beta * (from - last_from);


                    return from;
                } else {
                    from = startInfection[i];
                    integral_value = integral_value + (numberofactiveintervals * beta * (from - last_from));
                    numberofactiveintervals++;
                    last_from = startInfection[i];
                }
            }
            last_event_I++;
        } else {
            if (endInfection[j] > last_from) {

                if (integral_value + numberofactiveintervals * beta * (endInfection[j] - last_from) >=
                    Q[last_infected + 1]) {
                    // from qui diventa il tempo t al quale il nuovo infetto Q[last_infected+1] subisce il contatto infetto
                    from = (double) (Q[last_infected + 1] - integral_value +
                                     numberofactiveintervals * beta * last_from) /
                           (numberofactiveintervals * beta);


                    //comando inutile, è solo di controllo
                    // NB se si toglie controllare che il comando
                    // integral_value = Q[last_infected];
                    // a riga 64 sia attivo
                    //integral_value = integral_value + numberofactiveintervals * beta * (from - last_from);

                    return from;
                } else {
                    from = endInfection[j];
                    integral_value = integral_value + (numberofactiveintervals * beta * (from - last_from));
                    numberofactiveintervals--;
                    last_from = endInfection[j];
                }
            }
            last_event_R++;
        }
    }
    return -1;
}







