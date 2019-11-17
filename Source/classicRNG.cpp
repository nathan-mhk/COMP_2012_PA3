#include "classicRNG.h"
using namespace std;

ClassicRNG::~ClassicRNG()
{
}

int ClassicRNG::getRandomNumber()
{
    return rand()%32768; //maximum of rand() is at least 32767 but it might be larger (implementation-dependent)
    //let's make it 32767 anyway for consistency
}