#include <iostream>
#include <string>
#include <ctime>
#include "dictionary.h"
#include "randomTextGenerator.h"
#include "consecutiveRNG.h"
#include "classicRNG.h"
using namespace std;

int main()
{
    srand(time(NULL));  

    cout << boolalpha;
    cout << "Hello Markov Chain!" << endl;

    cout << "========================================" << endl;
    cout << "TEST CASE 0" << endl;
    RNG* cRNG = new ConsecutiveRNG;
    for(int i=0;i<200000;i++)
    {
        int r = cRNG->getRandomNumber();
        int expected = i%32768;
        if(r != expected)
        {
            cout << "Wrong@" << i << "... expected " << expected << "; got " << r << endl;
            delete cRNG;
            return 0;
        }
    }
    cout << "We are good." << endl;
    delete cRNG;

    cout << "========================================" << endl;
    cout << "TEST CASE 1" << endl;
    Dictionary<string, int> d;
    d["b"] = 2;
    cout << d["a"] << endl;
    cout << d["b"] << endl;
    cout << d["c"] << endl;

    cout << "========================================" << endl;
    cout << "TEST CASE 2" << endl;

    string s[] = {"a", "b", "c", "d"};

    Dictionary< string, Dictionary<string, int> > m;
    for(unsigned int i=0; i<sizeof(s)/sizeof(string); i++)
        for(unsigned int j=0; j<sizeof(s)/sizeof(string); j++)
            cout << "m[" << s[i] << "][" << s[j] << "]=" << (m[s[i]][s[j]]=i*4+j) << endl;

    cout << "========================================" << endl;
    cout << "TEST CASE 3" << endl;
    for(unsigned int i=0; i<sizeof(s)/sizeof(string); i++)
        for(unsigned int j=0; j<sizeof(s)/sizeof(string); j++)
            cout << "m[" << s[i] << "][" << s[j] << "]=" << m[s[i]][s[j]] << endl;

    cout << "Printing m:" << endl;
    cout << m << endl;

    cout << "========================================" << endl;
    cout << "TEST CASE 4" << endl;
    RandomTextGenerator rtg;
    rtg.readOriginalFromFile("original.txt");
    cout << "Original from original.txt:" << endl;
    cout << rtg.getOriginal() << endl;

    cout << "========================================" << endl;
    cout << "TEST CASE 5" << endl;
    cout << "Preparing WFM..." << endl;
    rtg.prepareWFM();
    cout << "WFM size = " << rtg.getWFM().getSize() << endl;
    cout << "Printing WFM:" << endl;
    cout << rtg.getWFM() << endl;

    cout << "========================================" << endl;
    cout << "TEST CASE 6" << endl;
    char vo = rtg.verifyOriginal();
    if(vo!='\0')
    {
        cout << "INVALID CHARACTER DETECTED:<" << vo << ">" << endl;
        return 0;
    }
    cout << "Generating Random Text with CONSECUTIVE RNG..." << endl;
    ConsecutiveRNG* consecutiveRNG = new ConsecutiveRNG;
    string result = rtg.generate(consecutiveRNG, 64);
    cout << "Result:" << endl;
    cout << result << endl;
    delete consecutiveRNG;

    cout << "========================================" << endl;
    cout << "FREESTYLE TEST YO LEGGO" << endl;
    cout << "Which RNG to use? (1:CONSECUTIVE or 2:CLASSIC)" << endl;
    int rngChoice;
    cin >> rngChoice;
    cout << endl;
    RNG* rng;
    if(rngChoice==1)
        rng = new ConsecutiveRNG;
    else
        rng = new ClassicRNG;
    cout << "Length of the random text?" << endl;
    int length;
    cin >> length;
    cout << endl;

    string input = "";
    cin.ignore(); //ignore any remaining character (e.g. newline character) that remains in the buffer
    while(true)
    {
        cout << "Say bye, or input the original text below, in one line! Remember the restrictions! If you use some non-English input, note that special or full-width characters are not supported even tho they look similar. When you copy and paste some text, it may also contain some invisible invalid characters." << endl;
        cout << "----------------------------------------" << endl;
        getline(cin, input);
        if(input == "bye")
            break;
        cout << "----------------------------------------" << endl;
        rtg.setOriginal(input);
        char verifyResult=rtg.verifyOriginal();
        if(verifyResult!='\0')
        {
            cout << "INVALID CHARACTER DETECTED:<" << verifyResult << ">" << endl;
            continue;
        }
        cout << "========================================" << endl;
        cout << "Original:" << endl;
        cout << rtg.getOriginal() << endl;

        cout << "========================================" << endl;
        rtg.prepareWFM();
        cout << "WFM size = " << rtg.getWFM().getSize() << endl;
        cout << "Printing WFM:" << endl;
        cout << rtg.getWFM() << endl;
        cout << "========================================" << endl;
        cout << "Generating Random Text with " << (rngChoice==1?"CONSECUTIVE":"CLASSIC") << " RNG..." << endl;
        string result = rtg.generate(rng, length);
        cout << "Result:" << endl;
        cout << result << endl;
        cout << "========================================" << endl;
    } 
    delete rng;
    cout << "lata!" << endl;

    return 0;
}
