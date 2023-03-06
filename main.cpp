// Developed by Joan Rios i Pla.
// It's not possible to make this without human imput, we will persent the human with possible options.

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <conio.h>
// #include "functions.hpp"

using namespace std;

typedef struct
{
    string text = "[]";
    string type = "[]";
    int length = 0;
} word;

vector<word> options;
vector<word> sentence;

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
void addToOptions(word addition);
void addToSentence(word input);
vector<word> getWordsOfTypeAndLen(int type, int len);
string strPi();
string strUsage();

int main(void)
{

    // Start rand()
    srand((unsigned) time(NULL));

    flushOptions();
    flushSentence();

    // Testing stuff

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
                    word idk = {str, typesOfWords[i], (int) str.length()};
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

    // Usage
    cout << strUsage();
    cout << endl << "Press any key to continue.";
    getch();
    putchar('\n');

    string input;
    while (true)
    {
        cout << endl
             << "End of current text: " << endOfSentence() << endl
             << "Pi: " << strPi() << endl
             << "Chose one of the following or write a word:" << endl;
        updateOptions();
        for (int i = 0; i < options.size(); i++)
        {
            cout << i << ": " << options[i].text << endl;
        }
        cout << endl;
        cin >> input;
        if (isdigit(input.at(0)))
        {
            if(input.length() == 1) addToSentence(options[input.at(0)- '0']);
            if(input.length() == 2) addToSentence(options[(input.at(0) - '0') * 10 + (input.at(1) - '0')]);
        }
        else if (isascii(input.at(0)))
        {
            if (input.at(0) == '/')
            {
                // Commands

                if (input == "/sentence")
                {
                    if (sentence.size() == 0) cout << "Empty sentence.";
                    for (int i = 0; i < sentence.size(); i++)
                    {
                        cout << sentence[i].text << " ";
                    }
                    putchar('\n');
                }
                else if (input == "/help" || input == "/usage")
                {
                    cout << strUsage();
                }
                else
                {
                    cout << "\033[31m" << "Unknown command " << "\033[m";
                }
                cout << endl << "Press any key to continue.";
                getch();
                putchar('\n');
            }
            else
            {
                addToSentence(*(new word {input, "[userInputed]", (int) input.length()}));
            }
        }
    }
}


void updateOptions()
{
    flushOptions();
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
            for(int i = 0; i < 2; i++) addToOptions(all[i]);
        }
        else if (all.size() == 1)
        {
            addToOptions(all[0]);
        }
    }
}

string endOfSentence()
{
    string out = "";
    if (sentence.size() >= 5)
        out += "... ";
    if (sentence.size() >= 4)
        out += sentence[sentence.size() - 4].text + " ";
    if (sentence.size() >= 3)
        out += sentence[sentence.size() - 3].text + " ";
    if (sentence.size() >= 2)
        out += sentence[sentence.size() - 2].text + " ";
    if (sentence.size() >= 1)
        out += sentence[sentence.size() - 1].text;
    return out;
}

void flushOptions()
{
    options.clear();
}

void flushSentence()
{
    sentence.clear();
}

void addToOptions(word addition)
{
    options.push_back(addition);
}

void addToSentence(word addition)
{
    sentence.push_back(addition);
    current++;
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

string strPi()
{
    string out = "";
    for (int i = 1; i <= 2; i++)
    {
        if(current - i >= 0) out += pi.at(current - i);
    }
    
    out += "\033[32m";
    out += pi.at(current);
    out += "\033[m";
    out += pi.at(current + 1);
    out += pi.at(current + 2);
    return out;
}

string strUsage()
{
    string out;
    out += "\n";
    out += "\033[32mUsage:\033[m\n";
    out += "Chose from the list of matching words by typing the corresponding number.\n";
    out += "If you want to see the whole sentence, type \033[34m/sentence\033[m.\n";
    return out;
}