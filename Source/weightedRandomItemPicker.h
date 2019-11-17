#ifndef WEIGHTED_RANDOM_ITEM_PICKER
#define WEIGHTED_RANDOM_ITEM_PICKER

#include "rng.h"

template <typename T>
class WeightedRandomItemPicker {
public:
    //pick randomly from an array of items according to their given probability (weights) of being picked, using the given RNG
    //note: weights[i] corresponds to the weight for items[i], for i in the range [0, n-1]
    T pick(int weights[], T items[], int n, RNG* rng)
    {
        int r = 0;
        int totalWeight = 0;
        for(int i=0;i<n;i++)
            totalWeight += weights[i];
        int randomNumber = rng->getRandomNumber();
        r =  randomNumber % totalWeight + 1; //totalWeight should not be more than 32768 due to standard library rand() limitation
        //if you use your own input original text which is very long, be aware of that
        
        //r is now a "random" number in [1, totalWeight] using whatever rng specified

        cout << "Picking from the following " << n << " item(s):" << endl;
        for(int i=0;i<n;i++)
        {
            cout << "(\"" << items[i] << "\"," << weights[i] << ") ";
        }
        cout << endl;
        int originalR = r;
        
        //the following will pick an item according to the r
        //recall that r is a random number in the range [1, totalWeight]
        //so the following *~magic~* can choose an item randomly with item weights considered
        for(int i=0;i<n;i++)
        {
            r-=weights[i];
            if(r<=0)
            {
                cout << "Random number is " << randomNumber << ", so (randomNumber\%totalWeight+1) is " << originalR << ", so \"" << items[i] << "\" is picked." << endl;
                cout << endl;

                return items[i];
            }
        }

        return items[0]; //shouldn't happen
    };
};

#endif