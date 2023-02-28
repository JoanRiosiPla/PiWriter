// Joan Rios i Pla
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
//#include "functions.hpp"

using namespace std;

typedef struct
{
    string text = "[]";
    string type = "[]";
    int length = 0;
}word;

word options[9];
word sentence[100];

// TODO
vector<word> words[8];
string pi;

void updateOptions();
string endOfSentence();
void flushOptions();
void flushSentence();
bool addToOptions(word addition);
int lengthOfSentence();
int lengthOfOptions();
bool addToSentence(word input);

int main(void)
{
    flushOptions();
    flushSentence();
    
    string input;
    while (true)
    {
        cout << endl
        <<"End of current text:" << endOfSentence() << endl
        << "Chose one of the following:" << endl;
        updateOptions();
        for (int i = 0; i < lengthOfOptions() ; i++)
        {
            cout << i << ": " << options[i].text;
        }
        cout << endl;
        cin >> input;
        addToSentence(options[input.at(0) - '0']);
    }
}

// It's not possible to make this without human imput, we will persent the human with possible options.

void updateOptions()
{
    flushOptions();
    string type = sentence[sizeof(sentence)/sizeof(*sentence) - 1].type;
    addToOptions({"hi", "interjection", 2});
}

string endOfSentence()
{
    string out = "";
    if (lengthOfSentence() >= 5) out += "... ";
    if (lengthOfSentence() >= 4) out += sentence[lengthOfSentence() - 4].text + " ";
    if (lengthOfSentence() >= 3) out += sentence[lengthOfSentence() - 3].text + " ";
    if (lengthOfSentence() >= 2) out += sentence[lengthOfSentence() - 2].text + " ";
    if (lengthOfSentence() >= 1) out += sentence[lengthOfSentence() - 1].text;
    return out;
}

void flushOptions()
{
    for (int i = 0; i < sizeof(options)/sizeof(*options); i++)
    {
        options[i] = {"[empty]", "[none]", 0};
    }
    return;
}

void flushSentence()
{
    for (int i = 0; i < sizeof(sentence)/sizeof(*sentence); i++)
    {
        sentence[i] = {"[empty]", "[none]", 0};
    }
    return;
}

bool addToOptions(word addition)
{
    for (int i = 0; i < sizeof(options)/sizeof(*options); i++)
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
    for (int i = 0; i < sizeof(sentence)/sizeof(*sentence); i++)
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
    for (int i = 0; i < sizeof(sentence)/sizeof(*sentence); i++)
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
    for (int i = 0; i < sizeof(options)/sizeof(*options); i++)
    {
        if (options[i].text.at(0) == '[')
        {
            break;
        }
        length++;
    }
    return length;
}