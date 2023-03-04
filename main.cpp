// Developed by Joan Rios i Pla.
// It's not possible to make this without human imput, we will persent the human with possible options.

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
// #include "functions.hpp"

using namespace std;

typedef struct
{
    string text = "[]";
    string type = "[]";
    int length = 0;
} word;

word options[9];
word sentence[100];

const int numberOfWordFiles = 10;
string typesOfWords[numberOfWordFiles] = {"noun", "pronoun", "verb", "adjective", "adverb", "preposition",
                                          "determiner", "conjunction", "interjection", "pi"};
vector<word> words[numberOfWordFiles];
string pi;
int current = 0;

void updateOptions();
string endOfSentence();
void flushOptions();
void flushSentence();
bool addToOptions(word addition);
int lengthOfSentence();
int lengthOfOptions();
bool addToSentence(word input);
vector<word> getWordsOfTypeAndLen(int type, int len);

int main(void)
{

    // Start rand()
    srand((unsigned) time(NULL));

    flushOptions();
    flushSentence();

    // Load files into vectors.

    {
        int time_before_load = time(NULL);

        for (int i = 0; i < numberOfWordFiles; i++)
        {
            fstream tmp;
            tmp.open("words/" + typesOfWords[i] + ".csv", ios::in);
            if (!tmp)
            {
                cout << "File not found: " << typesOfWords[i] << endl
                     << "Attempting creation of file: " << typesOfWords[i] << endl;
                tmp.open("words/" + typesOfWords[i] + ".csv", ios::out | ios::in | ios::app);
                if (tmp)
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

            // Load into vector;
            cout << "Loading file into vector ... ";
            if (typesOfWords[i] != "pi")
            {
                while (!tmp.eof())
                {
                    string str;
                    getline(tmp, str);
                    word idk = {str, typesOfWords[i], str.length()};
                    words[i].push_back(idk);
                }
            }
            else
            {
                getline(tmp, pi);
            }
            
            cout << "Should be loaded" << endl;

            // Close file
            tmp.close();
        }

        // TOFIX
        int time_after_load = time(NULL);
        int time_diff = time_after_load - time_before_load;
        cout << "Loaded in " << time_diff << " seconds." << endl;
    }

    string input;
    while (true)
    {
        cout << endl
             << "End of current text:" << endOfSentence() << endl
             << "Chose one of the following:" << endl;
        updateOptions();
        for (int i = 0; i < lengthOfOptions(); i++)
        {
            cout << i << ": " << options[i].text << endl;
        }
        cout << endl;
        cin >> input;
        addToSentence(options[input.at(0) - '0']);
    }
}


void updateOptions()
{
    flushOptions();
    string type = sentence[lengthOfSentence() - 1].type;
    int chars = pi.at(current) - '0';

    for (int i = 0; i < numberOfWordFiles - 1; i++)
    {
        vector<word> all = getWordsOfTypeAndLen(i, chars);
        if (all.size() >= 3)
        {
            for(int i = 0; i < 3; i++) addToOptions(all[rand() % all.size()]);
        }
        else if (all.size() == 2)
        {
            for(int i = 0; i < 2; i++) addToOptions(all[rand() % all.size()]);
        }
        else if (all.size() == 1)
        {
            for(int i = 0; i < 1; i++) addToOptions(all[rand() % all.size()]);
        }
    }
    current++;
}

string endOfSentence()
{
    string out = "";
    if (lengthOfSentence() >= 5)
        out += "... ";
    if (lengthOfSentence() >= 4)
        out += sentence[lengthOfSentence() - 4].text + " ";
    if (lengthOfSentence() >= 3)
        out += sentence[lengthOfSentence() - 3].text + " ";
    if (lengthOfSentence() >= 2)
        out += sentence[lengthOfSentence() - 2].text + " ";
    if (lengthOfSentence() >= 1)
        out += sentence[lengthOfSentence() - 1].text;
    return out;
}

void flushOptions()
{
    for (int i = 0; i < sizeof(options) / sizeof(*options); i++)
    {
        options[i] = {"[empty]", "[none]", 0};
    }
    return;
}

void flushSentence()
{
    for (int i = 0; i < sizeof(sentence) / sizeof(*sentence); i++)
    {
        sentence[i] = {"[empty]", "[none]", 0};
    }
    return;
}

bool addToOptions(word addition)
{
    for (int i = 0; i < sizeof(options) / sizeof(*options); i++)
    {
        if (options[i].text.at(0) == '[')
        {
            options[i] = addition;
            return true;
        }
    }

    return false;
}

bool addToSentence(word addition)
{
    for (int i = 0; i < sizeof(sentence) / sizeof(*sentence); i++)
    {
        if (sentence[i].text.at(0) == '[')
        {
            sentence[i] = addition;
            return true;
        }
    }

    return false;
}

int lengthOfSentence()
{
    int length = 0;
    for (int i = 0; i < sizeof(sentence) / sizeof(*sentence); i++)
    {
        if (sentence[i].text.at(0) == '[')
        {
            break;
        }
        length++;
    }
    return length;
}

int lengthOfOptions()
{
    int length = 0;
    for (int i = 0; i < sizeof(options) / sizeof(*options); i++)
    {
        if (options[i].text.at(0) == '[')
        {
            break;
        }
        length++;
    }
    return length;
}

vector<word> getWordsOfTypeAndLen(int type, int len)
{
    vector<word> out;
    for (auto i = words[type].begin(); i != words[type].end(); ++i)
    {
        if ((*i).length == len)
        {
            out.push_back(*i);
        }
    }
    return out;
}