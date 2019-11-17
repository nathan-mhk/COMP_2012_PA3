#include "rng.h"

class ConsecutiveRNG : public RNG 
{
public:
    ConsecutiveRNG(); //remember to initialize the data member here, you can decide on the initial value of current
    ~ConsecutiveRNG(); //nothing needs to be done in this destructor
    int getRandomNumber(); //return a fake "random" number, see webpage for description
private:
    int current; //you may use this variable to keep track of the current number
                //but how you use it is up to you
};