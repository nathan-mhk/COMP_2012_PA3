// SUBMIT THIS FILE

#include "consecutiveRNG.h"

ConsecutiveRNG::ConsecutiveRNG() : RNG(), current(0) {}

ConsecutiveRNG::~ConsecutiveRNG() {}

int ConsecutiveRNG::getRandomNumber() {
    return ((current++) % 32768);
}