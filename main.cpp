// Joan Rios i Pla
#include <iostream>
#include <fstream>
//#include <functions.cpp>
using namespace std;

string typesOfWords[] = {"noun", "pronoun", "verb", "adjective", "adverb", "preposition", "conjunction", "interjection"};

int main(void)
{

    // Open Files
    fstream words[8];
    for (int i = 0; i < sizeof(words) / sizeof(fstream); i++)
    {
        words[i].open("words/" + typesOfWords[i] + ".csv", ios::in);
        if(!words[i]) 
        {
            cout<<"File not found: " << typesOfWords[i] << endl
                << "Attempting creation of file: " << typesOfWords[i] << endl;
            words[i].open("words/" + typesOfWords[i] + ".csv", ios::out | ios::in | ios::app);
            if (words[i])
            {
            cout << "Creation succesful";
            }
            else
            {
                cout << "Failed.";
                return 1;
            }
            
        }
        else
        {
            cout<<"Opened " << typesOfWords[i];
        }
        cout << endl;
    }

    //Close files
    for (int i = 0; i < sizeof(words) / sizeof(fstream); i++)
    {
        words[i].close();
        if (words[i].is_open())
        {
            cout << "Error while closing" << typesOfWords[i] << ", program didn't stop." << endl;
        }
    }
    
    return 0;
}