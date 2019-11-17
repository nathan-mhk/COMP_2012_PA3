#ifndef RANDOM_TEXT_GENERATOR_H
#define RANDOM_TEXT_GENERATOR_H

#include <string>
#include "rng.h"
#include "dictionary.h"
#include "weightedRandomItemPicker.h"
using namespace std;

class RandomTextGenerator {
private:
    Dictionary< string, Dictionary<string, int> > wfm; //WFM (word frequency matrix)
    string original; //it stores the input text used to generate the WFM

public:
    //read the file content from the file specified by the fileName, and save it to the data member original
    //for Eclipse, the file should be put in the same location as the source files
    //for other IDEs, you need to look it up yourself
    //for simplicity, as the original text shouldn't contain any newline character,
    //just read the first line in the file 
    //(i.e. read until the first newline character or EOF, but don't include those characters in the original)
    void readOriginalFromFile(const char fileName[]);

    //verify the original content text
    //A valid text is defined as a text that consists of only valid characters 
    //return the null character '\0' if no invalid character is found
    //otherwise, return the first invalid character found
    //valid characters are
    //- alphabets, lower case or upper case
    //- digits (i.e., '0' - '9')
    //- space ' ' 
    //- comma ','
    //- the following 8 symbols '.', ';', ':', '\'', '\"', '-', '!', '?'
    //note that there should be no newline character ('\n') or other special characters (such as '\t' or '\r' or some chinese full-width character, etc.)
    char verifyOriginal();

    //prepare the WFM
    //check the webpage for explanation and examples
    void prepareWFM();

    //generate a random text of the given length
    //rng is used as the random number generator
    //check the webpage for explanation and examples
    string generate(RNG* rng, int length);

    //set the original directly
    //if you couldn't finish the file reading part, just use this for testing
    void setOriginal(string s) { original = s; }; 

    //return the original
    string getOriginal() const { return original; };

    //return the WFM
    const Dictionary< string, Dictionary<string, int> >& getWFM() const { return wfm; };
};

#endif