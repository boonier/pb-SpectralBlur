//
//  OnePole.cpp
//  SpectralBlur (Upgraded)
//
//  Created by Si Mills on 19/02/2023.
//

#include "../common/BiduleSDK.h"
#include "OnePole.h"
#include <iostream>

OnePole::~OnePole() {
    cout << "Destroy filter" << endl;
}

void OnePole::setFc(double Fc) {
//    cout << "Fc is: " << Fc << endl;
    b1 = exp(-2.0 * M_PI * Fc);
    a0 = 1.0 - b1;
}


double OnePole::process(float in) {
    return z1 = in * a0 + z1 * b1;
}

// maybe frequency needs its own filter???
double OnePole::processF(float in) {
    return z1 = in * a0 + z1 * b1;
}

double OnePole::processM(float in) {
    return z1 = in * a0 + z1 * b1;
}

void OnePole::sayHello () {
    cout << "I am a filter." << endl;
}

