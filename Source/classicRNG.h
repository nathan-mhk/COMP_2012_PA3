#include "rng.h"
#include <cstdlib>

class ClassicRNG : public RNG 
{
public:
    ~ClassicRNG(); //nothing needs to be done in this destructor
    int getRandomNumber(); //returns a random number
};