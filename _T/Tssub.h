//
// Created by Lucius Schoenbaum on 3/15/22.
//

#pragma once


#include <Tbasis.h>

#include <DGCALC.h>


class Tssub {


public: // API:

    static void Tdryrun() {
        std::string s1 = "The quick brown fox jumps over the lazy dog.";
        cout << s1 << endl;
        DGCALC::ssub(s1, "brown", "BLUISH-GREY");
        cout << s1 << endl;

        std::string s2 = "The quick brown fox jumps over the brown dog.";
        cout << s2 << endl;
        DGCALC::ssub(s2, "brown", "BLUISH-GREY");
        cout << s2 << endl;
    }

};

