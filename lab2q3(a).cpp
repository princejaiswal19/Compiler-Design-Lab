#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void count_stats(const string &filename, int &c_count, int &w_count, int &s_count, int &l_count)
{
    ifstream file(filename);

    c_count = 0;
    w_count = 0;
    s_count = 0;
    l_count = 0;

    string line;
    bool in_word = false;

    while (getline(file, line))
    {
        l_count++;

        for (char c : line)
        {
            c_count++;

            if (isspace(c))
            {
                s_count++;
                in_word = false;
            }
            else
            {
                if (!in_word)
                {
                    w_count++;
                    in_word = true;
                }
            }
        }

        in_word = false;
    }

    file.close();
}

int main()
{
    string filename = "2exp.txt";
    int chars, words, spaces, lines;

    count_stats(filename, chars, words, spaces, lines);

  cout<<" 1: Count of the characters is:"<<chars<<endl;
  cout<<" 2: Count of the words is:"<<words<<endl;
  cout<<"3: Count of the spaces is:"<<spaces<<endl;
  cout<<"4: Count of the lines is:"<<lines<<endl;

return 0;
}
