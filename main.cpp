/* author: (your name here)
*  date: (today's date)
*  description:  provide a brief description of your program
*  proposed points (out of 10): a description of the number
*  of points you believe your assignment is worth
*/

#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <ctype.h>
#include <sstream>

using namespace std;
void convertAllLettersToLower(string &s)
{
    int len = (int)s.size();
    for (int i = 0; i < len; i++)
    {
        if (isalpha(s[i]))
        {
            s[i] = tolower(s[i]);
        }
    }
}

int main()
{

    //declare a few needed variables for inputing the data
    string line;
    int score;
    string message = " ";

    //open input file
    ifstream myfile("movieReviews.txt");
    ifstream stopWordsFile("stopwords.txt");
    if (myfile.fail() || stopWordsFile.fail())
    {
        cout << "could not open file" << endl;
        exit(0);
    }

    //create hash table
    HashTable table(20000);
    map<string, int> stopWords;
    if (stopWordsFile.is_open())
    {
        string s;
        while (!stopWordsFile.eof())
        {
            stopWordsFile >> s;
            convertAllLettersToLower(s);
            stopWords[s] = 1;
        }

        stopWordsFile.close();
    }

    while (!myfile.eof())
    {
        myfile >> score; //get score
        myfile.get();    // get blank space
        getline(myfile, line);
        int len = line.size();
        while (len > 0)
        { //identify all individual strings
            string sub;
            len = line.find(" ");
            if (len != std::string::npos)
            {
                sub = line.substr(0, len);
                line = line.substr(len + 1);
            }
            else
            {
                sub = line.substr(0, line.size());
            }
            convertAllLettersToLower(sub);
            if (!stopWords.count(sub))
            {
                // this word is not a stop word
                // cout << sub << endl;
                table.put(sub, score); //insert string with the score
            }
        }
    }

    //after data is entered in hash function
    //prompt user for a new movie review
    while (message.length() > 0)
    {
        cout << "enter a review -- Press return to exit: " << endl;
        getline(cin, message);

        //used for calculating the average
        double sum = 0;
        int count = 0;
        int mostNegativeScore = 5;
        int mostPostiveScore = -1;
        string mostNegativeWord = "";
        string mostPostiveWord = "";

        int len = message.size();
        //get each individual word from the input
        while (len != std::string::npos)
        {
            string sub;
            len = message.find(" ");
            if (len != string::npos)
            {
                sub = message.substr(0, len);
                message = message.substr(len + 1, message.size());
            }
            else
            {
                sub = message;
            }
            if (stopWords.count(sub))
            {
            }
            //calculate the score of each word
            int sco = table.getAverage(sub);
            sum += sco;
            if (sco > mostPostiveScore)
            {
                mostPostiveScore = sco;
                mostPostiveWord = sub;
            }
            if (sco < mostNegativeScore)
            {
                mostNegativeScore = sco;
                mostNegativeWord = sub;
            }
            count++;
        }

        if (message.size() > 0)
        {
            cout << "The review has an average value of " << sum / count << endl;
            cout << "The most negative word is: { " << mostNegativeWord << " } "
                 << "and the most positive word is: { " << mostPostiveWord << " }" << endl;
        }
    }

    return 0;
}
