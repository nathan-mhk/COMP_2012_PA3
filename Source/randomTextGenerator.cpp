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
    }
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

string getFirstWord(const string& original) {
    string FirstWord = "";
    char delim = ' ';
    // If not empty string , shall never happens
    if (original.begin() != original.end()) {
        string::const_iterator itr = original.begin();
        while ((itr != original.end()) && (*itr == delim)) {
            ++itr;
        }
        do {
            FirstWord += *itr;
            ++itr;
        } while ((itr != original.end()) && (*itr != delim));
    }
    return FirstWord;
}

string RandomTextGenerator::generate(RNG* rng, int length) {
    WeightedRandomItemPicker<string> picker;
    string text = "";
    string word = "";
    const string firstWord = getFirstWord(original);

    for (int i = 0; i < length; ++i) {
        if (wfm[word].getSize() == 0)
            word = firstWord;
        cout << "Previous word is \"" << word << "\"." << endl;

        string* items = wfm[word].getKeyList();
        int* weights = wfm[word].getValueList();

        word = picker.pick(weights, items, wfm[word].getSize(), rng);
        text += word;
        if (i < length - 1)
            text += " ";
        
        delete [] items;
        delete [] weights;
    }
    wfm.clean();
    return text;
}
