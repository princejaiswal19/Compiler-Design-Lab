#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    ifstream inputFile("in.cpp");
    ofstream outputFile("out.cpp");

    if (!inputFile.is_open())
    {
        cout << "Error:" << endl;
        return 1;
    }

    if (!outputFile.is_open())
    {
        cout << "Error:" << endl;
        return 1;
    }

    string line;
    bool inComment = false;
    int commentLines = 0;

    while (getline(inputFile, line))
    {
        string trimmedLine = line;
        trimmedLine.erase(0, trimmedLine.find_first_not_of(" \t")); 

        if (inComment)
        {
            commentLines++;
            if (trimmedLine.find("*/") != string::npos)
            {
                inComment = false;
            }
            continue;
        }

        if (trimmedLine.find("/*") != string::npos)
        {
            inComment = true;
            commentLines++;
            if (trimmedLine.find("*/") != string::npos)
            {
                inComment = false;
            }
            continue;
        }

        if (trimmedLine.find("//") != string::npos)
        {
            commentLines++;
            continue;
        }

        outputFile << line << endl;
    }

    cout << "Total comment lines: " << commentLines << endl;

    inputFile.close();
    outputFile.close();

    return 0;
}
