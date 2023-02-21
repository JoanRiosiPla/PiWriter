// Joan Rios i Pla
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <string>
//#include "functions.hpp"

using namespace std;

int maxSearches = 1000000;

int prevWord;
const int numberOfWordFiles = 10;
string typesOfWords[] = {"noun", "pronoun", "verb", "adjective", "adverb", "preposition", "determiner", "conjunction", "interjection", "pi"};

string findWord(fstream allWords[numberOfWordFiles], string typeOfWord, int letters, int max);
int nameToIndex(string name);

int main(void)
{
    // Start rand()
    srand((unsigned) time(NULL));

    // Open Files
    fstream words[numberOfWordFiles];
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
            cout << "Opened " << typesOfWords[i];
        }
        cout << endl;
    }

    // Get pi
    string pi;
    getline(words[nameToIndex("pi")], pi);

    prevWord = rand() % 7;
    cout << "Random Word To Start From: " << prevWord << endl;

    for (int i = 0; i < 20; i++)
    {
        string out;
        cout << pi.at(i);
        switch (prevWord)
        {
        // noun
        case 0:
            {
                string tmp;
                out += findWord(words, "verb", int(pi.at(i) - '0'), maxSearches);
                prevWord = nameToIndex("verb");
                
                break;
            }

        
        // pronoun
        case 1:
            {
                out += findWord(words, "adjective", int(pi.at(i) - '0'), maxSearches);
                prevWord = nameToIndex("adjective");
                break;
            }
            
        // verb
        case 2:
            {
                string tmp;
                tmp = findWord(words, "determiner", int(pi.at(i) - '0'), maxSearches);
                prevWord = nameToIndex("determiner");
                if (tmp == "[not found]")
                {
                    tmp = findWord(words, "preposition", int(pi.at(i) - '0'), maxSearches);
                    prevWord = nameToIndex("preposition");
                }
                out += tmp;
                
                break;
            }
            

        // adjective
        case 3:
            {
                out += findWord(words, "noun", int(pi.at(i) - '0'), maxSearches);
                prevWord = nameToIndex("noun");
                break;
            }
            

        // adverb
        case 4:
            {
                out += findWord(words, "noun", int(pi.at(i) - '0'), maxSearches);
                prevWord = nameToIndex("noun");
                break;
            }

        
        // preposition
        case 5:
            {
                out += findWord(words, "adjective", int(pi.at(i) - '0'), maxSearches);
                prevWord = nameToIndex("adjective");
                break;
            }


        // determiner
        case 6:
            {
                out += findWord(words, "noun", int(pi.at(i) - '0'), maxSearches);
                prevWord = nameToIndex("noun");
                break;            
            }


        // conjuction
        case 7:
            {
                out += findWord(words, "determiner", int(pi.at(i) - '0'), maxSearches);
                prevWord = nameToIndex("determiner");
                break;   
            }


        // interjection
        case 8:
            {
                out += findWord(words, "verb", int(pi.at(i) - '0'), maxSearches);
                prevWord = nameToIndex("verb");
                break;
            }

        }
        out += " ";
        cout << out;
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


// Find first word in "words" file with "letters" number of letters

string findWord(fstream allWords[numberOfWordFiles], string typeOfWord, int letters, int max)
{
    string word;

    // cout << " " << typeOfWord << " ";

    if (typeOfWord == "verb" && letters <= 1)
    {
        prevWord = nameToIndex("preposition");
        return ", a";
    }

    fstream &words = allWords[nameToIndex(typeOfWord)];

    for (int i = 0; i < 2; i++)
    {
        int chance = 5;
        if (i == 1)
        {
            if (word != "[not found]")
            {
                break;
            }
            chance = 1;
        }
        
        words.seekg(0);
        int index = 0;
        bool ready = false;
        do
        {

            getline(words, word);
            if (rand() % chance == 0)
            {
                index++;
                ready = true;
            }
            else
            {
                ready = false;
            }
            
        } while (( !ready || word.length() != letters ) && index < max);

        if (index == max) word = "[not found]";
    }
    return word;
}

int nameToIndex(string name)
{
    for (int i = 0; i < numberOfWordFiles; i++)
    {
        if (typesOfWords[i] == name)
        {
            return i;
        }
    }
    return -1;
}