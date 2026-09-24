//
// Created by Lucius Schoenbaum on 3/15/22.
//

#pragma once


#include <Tbasis.h>

#include <DGCALC.h>


class Tpopcount {

    template <typename itype>
    static void findit(itype n) {
        cout << "popcount of " << n << " = " << DGCALC::popcount(n) << endl;
        cout << "\t\t\tpopsign of " << n << " = " << DGCALC::popsign(n) << endl;
    }

public: // API:

    static void Tdryrun() {
        for (int i = 0; i < 35; ++i) {
            findit(i);
        }
        cout << "near max for type:\n";
        for (uint64_t i = 0xffffffffffffffff; i >= 0xfffffffffffffff0; --i) {
            findit(i);
        }

    }
};

