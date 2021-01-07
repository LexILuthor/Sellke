//
// Created by popcorn on 29/11/2020.
//

#ifndef SELLKE_MYFUNCTIONS_H
#define SELLKE_MYFUNCTIONS_H

#endif //SELLKE_MYFUNCTIONS_H

/*

std::vector<double> rand_Unif(int nSamples = 1, double a = 0, double b = 1);

std::vector<double> rand_Exponential(int nSamples = 1, double lambda = 1);

*/

void generate(std::vector<double> &Q, std::vector<double> &L, std::vector<double> &I, double ny, double gamma, int N);


void activeintervels(double from, std::vector<double> &startInfection, std::vector<double> &endInfection,
                    std::vector<size_t> indexEndInfection,int &last);




//template for the function that returns the ordered index
#include <algorithm>
#include <numeric>      // std::iota

template<typename T>
std::vector<size_t> sort_indexes(const std::vector<T> &v) {

    // initialize original index locations
    std::vector<size_t> idx(v.size());
    iota(idx.begin(), idx.end(), 0);

    // sort indexes based on comparing values in v
    // using std::stable_sort instead of std::sort
    // to avoid unnecessary index re-orderings
    // when v contains elements of equal values
    stable_sort(idx.begin(), idx.end(),
                [&v](size_t i1, size_t i2) { return v[i1] < v[i2]; });

    return idx;
}



