#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int CountWord(string text, string word)
{
    int count = 0;
    string temp = "";
    for (int i = 0; i <= text.length(); i++)
    {
        if (text[i] != ' ' && i < text.length())
        {
            temp += text[i];
        }
        else
        {
            if (temp == word)
            {
                count++;
            }
            temp = "";
        }
    }
    return count;
}
int main()
{
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");
    if (!inputFile.is_open())
    {
        cout << "Error opening input file!" << endl;
        return 1;
    }
    string text = "";
    string line;
    while (getline(inputFile, line))
    {
        text += line + " ";
    }
    inputFile.close();
    cout << "Text from file:\n" << text << endl;
    string word;
    cout << "Enter word to search: ";
    cin >> word;
    int count = CountWord(text, word);
    if (count > 0)
    {
        outputFile << count;
        cout << "Word found " << count << " times" << endl;
    }
    else
    {
        outputFile << 27;
        cout << "Word not found. Written 27 to file." << endl;
    }
    outputFile.close();
    return 0;
}