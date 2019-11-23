// SUBMIT THIS FILE

#include "randomTextGenerator.h"
#include <fstream>
using namespace std;

void RandomTextGenerator::readOriginalFromFile(const char fileName[]) {
    // ifstream file(fileName);
    ifstream file;
    file.open(fileName);
    if (file.is_open()) {
        getline(file, original, '\n');
        file.close();
    } else
        cout << "Failed to open file" << endl;
}

char RandomTextGenerator::verifyOriginal() {
    for (unsigned int i = 0; i < original.size(); ++i) {
        int testChar = (int)original[i];
        if (
            // [32-34] || 39 || [44-46] || [48-59] || 63 || [65-90] || [97-122]
            //  ' '!"      '      ,-.        0-9       ?      A-Z         a-z
            ((testChar >= 32) && (testChar <= 34)) ||
            (testChar == 39)  || (testChar == 63)  ||
            ((testChar >= 44) && (testChar <= 46)) ||
            ((testChar >= 48) && (testChar <= 59)) ||
            ((testChar >= 65) && (testChar <= 90)) ||
            ((testChar >= 97) && (testChar <= 122))) {
            continue;
        } else
            return original[i];
    }
    return '\0';
}

void RandomTextGenerator::prepareWFM() {
    // Generate wfm using original
    string copy = original;
    string prevWord = "";
    string currWord = "";
    char delim = ' ';
    for (string::const_iterator itr = original.begin(); itr != original.end();) {
        // Ignore all the continuous space char
        if (*itr == delim) {
            ++itr;
            continue;
        }
        string::const_iterator nextItr = itr;
        // Prevent dereferencing .end()
        while ((nextItr != original.end()) && (*nextItr != delim)) {
            currWord += *nextItr;
            ++nextItr;
        }
        // nextItr will point at the first space char after the extracted word
        (wfm[prevWord][currWord])++;
        prevWord = currWord;
        currWord = "";

        itr = nextItr;
    }
}

string RandomTextGenerator::generate(RNG* rng, int length) {
    // TODO
    // Need this for test6
    return "test";
}
