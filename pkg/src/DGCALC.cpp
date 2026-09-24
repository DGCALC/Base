

#include <DGCALC.h>


void DGCALC::ssub(std::string & subee, const std::string & pattern, const std::string & suband) {
    size_t pos = 0;
    while ((pos = subee.find(pattern, pos)) != std::string::npos) {
        subee.replace(pos, pattern.length(), suband);
    }
}

