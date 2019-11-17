#ifndef RNG_H
#define RNG_H

//RNG is an ABC that serves as a base for all random number generators
class RNG 
{
public:
    virtual ~RNG(){}; //it is in general a good practice to have a virtual destructor for an ABC
    virtual int getRandomNumber() = 0; //return a random number
};

#endif
