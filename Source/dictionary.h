#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <typeinfo>  //to use typeid
#include <cstddef> //to use NULL
using namespace std;

//Note: this Dictionary class template supports any V that has a default constructor
//      (unless it is simpley a int/double/etc.) and can be assigned with 0
//      hence, the following code needs to work, or it is not qualified for being V
//      V v; //default construction
//      v = 0; //assignment with 0
template<typename K, typename V>
class Dictionary
{
public:
    //constructor
    //don't worry about the dummy
    //but if you care about an explanation:
    //it basically acts as both the default constructor and conversion constructor
    //which simply initialize the Dictionary to an empty initial state
    //since we want to have Dictionary<string, Dictionary<string, int>> later
    //we need Dictionary to have a conversion constructor so that assigning 0 to it works
    //as a result, the Dictionary itself can be qualified as V
    Dictionary(int dummy=0) : array(NULL), size(0) {};

    //copy constructor
    //deep copy is required
    Dictionary(const Dictionary& another);

    //destructor
    //use the clean function which is to be implemented by you
    ~Dictionary() { clean(); };

    //if there exists an item with the given key in the dictionary,
    //return a reference to its value
    //otherwise add the new item with that key to the dictionary and set its value to 0 by assignment
    //i.e. something like the following
    //           array[newSize-1].value = 0; 
    //note that the array should always be just big enough to cotain all the items
    //and that the new item is always added to the end of the array, hence the index newSize-1
    //that also means that everytime you add a new item, you need to increase the size of the array by 1
    V& operator[](K key); 

    //deep assignment operator
    //remember to check for self-assignment first
    Dictionary& operator=(const Dictionary& another);

    //return the dictionary's (i.e. its array's) size
    int getSize() const { return size; };

    //return a list of keys in the exact order they are stored in the dictionary's array
    //you need to dynamically create an array of K and return it in this function
    //however, you do NOT need to delete it here in this function/class
    //the caller of this function has the responsibility of deleting the returned array after it's done using it
    K* getKeyList() const; 

    //same as above, but for values
    V* getValueList() const;

    //delete the array
    //set array to NULL
    //set size to 0
    void clean();

    //print the content of the dictionary
    //read the code to understand exactly what it does
    //note: it gives some special formatting treatment when K is string or when V is Dictionary
    friend ostream& operator<<(ostream& os, const Dictionary& d)
    {
        os << "{ ";
        bool valueIsDictionary = false;
        if(d.size)
        {
            bool keyIsString = typeid(d.array[0].key) == typeid(string);
            valueIsDictionary = string(typeid(d.array[0].value).name()).find("Dictionary")!=string::npos;
            for(int i=0;i<d.size;i++)
            {
                if(valueIsDictionary)
                    os << "\n\t";
                os << "(" << (keyIsString?"\"":"") << d.array[i].key << (keyIsString?"\"":"") << "," << d.array[i].value << ")";
                if(i!=d.size-1) os << ",";
            }
        }
        if(valueIsDictionary)
            os << "\n";
        os << " }";
        return os;
    };
private:
    struct KeyValue
    {
        K key;
        V value;
    }; //the key-value pair struct

    KeyValue* array; //pointer to array of items (the key-value pairs)
    int size; //size of the dictionary (i.e. the array size)
};

//the following statement effectively copies and pastes the content of
//the dictionaryImplementation.h to here
//because the template member function definitions need to be here after the class template declaration
//this is a trick to allow students to write code in a separate file
#include "dictionaryImplementation.h"

#endif
