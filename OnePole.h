//
//  OnePole.cpp
//  SpectralBlur (Upgraded)
//
//  Created by Si Mills on 22/04/2022.
// https://www.earlevel.com/main/2012/12/15/a-one-pole-filter/

#ifndef OnePole_h
#define OnePole_h

#include <stdio.h>
#include <math.h>
#include "../common/BiduleSDK.h"

using namespace std;

class OnePole {
    public:
        OnePole() {a0 = 1.0; b1 = 0.0; z1 = 0.0;};
        OnePole(double Fc) { z1 = 0.0; setFc(Fc);};
        ~OnePole();
    
        void setFc(double Fc);
        double process(float input);
        double processF(float input);
        double processM(float input);
        void sayHello();
        
    protected:
        double a0, b1, z1;
};

#endif
