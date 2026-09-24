//
// Created by Lucius Schoenbaum on 3/15/22.
//

#pragma once


#include <Tbasis.h>

#include <DGCALC.h>


class Tilog2 {

    static void findit(int n) {
        cout << "log2 of " << n << " = " << DGCALC::ilog2<int>(n) << endl;
    }

public: // API:

    static void Tdryrun() {
        int n1 = 31;
        int n2 = 32;
        int n3 = 33;
        findit(n1);
        findit(n2);
        findit(n3);
    }
};

