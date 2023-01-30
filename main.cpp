// Joan Rios i Pla
#include <iostream>
#include <fstream>
//#include <functions.cpp>
using namespace std;

int main(void)
{
    fstream adjectives;
    adjectives.open("words/adjectives.csv",ios::out);
    if(!adjectives) 
    {
        cout<<"File creation failed";
    }
    else
    {
        cout<<"New file created";
        adjectives.close(); // Step 4: Closing file
    }
    return 0;
}