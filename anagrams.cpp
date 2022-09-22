#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
#include <string>
#include <cassert>
using namespace std;

const int MAXRESULTS   = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in

//helper function for LexiconBulter
int lexHelper(istream &dictfile, string dict[], int& x)
{
     //occurs it ends up reaching the end of the file
    if((dictfile >> dict[0]).eof()) //eof is end of file function
    {
        return ++x;
    }
    if(x >= MAXDICTWORDS) //x in this cause is the count, of it were to equal or suppass the max amount of words then it would just return itself and not surpass
    {
        return x;
    }
    return lexHelper(dictfile, dict+1, ++x); //recalls the function but the return count is increased each time
    
}

int lexiconBuilder(istream &dictfile, string dict[])
{
    int x = 0;
    return lexHelper(dictfile, dict, x); //calls the helper function
    //it returns the number of words that have been read into dict (will never go pass maxDictWords)
}

//thejumbler set of helper functions
bool noWords(const string word[]
             , const int& size, const string& dictWord)
{
    
    //checks if their is a word that is being imputted and helps with finding duplicate words
    int x = 0;
    if(dictWord == word[x]) //if the words match then this function is gonna return false
    {
        return false;
    }
    if(size == x) //if the size is 0 then no worrds are being inputted
    {
        return true;
    }
   
    return noWords(word+1, size-1, dictWord); //recurse through until it reaches break case
}

bool trueGram(const string& word, string realWord, const int& x)
{
    //checks to see if its an actual anagram
    if(x == word.size())  //if x is equal to the size of the given word
    {
        return true;
    }
    if(realWord.find(word[x]) != string::npos) //npos is a static member constant value with the greatest possible value for an element of type size_t.
    {
        return trueGram(word, realWord.erase(realWord.find(word.at(x)), 1), x + 1); //iterartes until break point
    }
    else{
        return false;
    }
}

int characterSum(const string& checker)
{
    
    //helper function for the jumbler
    int i = 0;
    if(checker.size() != 1)
    {
        return checker[i] + characterSum(checker.substr(1)); //adds checker and recurses cahractersum starting from 1
    }
    else{
        return checker[i];
    }
}
int check(const string& word, const string dict[], const int& size, string results[], int& x)
{ //made so that we can implement another paramter
    int y =0;
   if(size <= 0||x>=MAXRESULTS)
   {
       return x;
   }
    
    if(dict[y].size() == word.size()) //chekcs to see if the sizes from the dict match the size of the word
    {
        if(characterSum(word) == characterSum(dict[y])) //if it does match then it chekcs to see if the charactersum function call of both sets actually work
        {
            if(trueGram(word, dict[y], y)) //checks to see if the word is actually an anagram
            {
                if(noWords(results, x, dict[y])) //checks to see if there is a word contained in code
                {
                    results[x++] = dict[y]; //assigns the dictionary word to the result
                }
            }
        }
    }
    return check(word, dict+1, size -1, results, x);  //it recursively iterates through the dictionary
}

int theJumbler(string word, const string dict[], int size,
string results[])
{
    int y = 0;
    return check(word, dict, size, results, y); //calls the helper function
}

void divulgeSolutions(const string results[], int size)
{
    
    if(size == 0)
    {
        return; //if the size of the solution is 0 then return nothing and end the code
    }
    else{
        cout << results[0] << endl;
        divulgeSolutions(results + 1, size-1); //if its not then cout the results and recurse by increasing the results by 1 and decrementinfg the size
    }
}
#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
#include <string>
#include <cassert>
using namespace std;

 
 
int main()
{
 string results[MAXRESULTS];
 string dict[MAXDICTWORDS];
 ifstream dictfile;         // file containing the list of words
 int nwords;                // number of words read from dictionary
 string word;
 
 dictfile.open("words.txt");
 if (!dictfile) {
  cout << "File not found!" << endl;
  return (1);
 }
 
 nwords = lexiconBuilder(dictfile, dict);
 
#ifdef TEST1
 word = "rat";
#endif
#ifdef TEST2
 word = "babe";
#endif
#ifdef TEST3
 word = "plane";
#endif
#ifdef TEST4
 word = "maiden";
#endif
#ifdef TEST5
 word = "arrogant";
#endif
 
 int numMatches = theJumbler(word, dict, nwords, results);
 if (!numMatches)
  cout << "No matches found" << endl;
 else
  divulgeSolutions(results, numMatches);
#ifdef TEST1
 assert(numMatches == 3 && (results[0] == "rat" ||
results[0] == "art"
  || results[0] == "tar"));
#endif
#ifdef TEST2
 assert(numMatches == 2 && (results[0] == "abbe" ||
results[0] == "babe"));
#endif
#ifdef TEST3
 assert(numMatches == 3 && (results[0] == "plane" ||
results[0] == "panel"
  || results[0] == "penal"));
#endif
#ifdef TEST4
 assert(numMatches == 2 && (results[0] == "maiden" ||
results[0] == "median"));
#endif
#ifdef TEST5
 assert(numMatches == 2 && (results[0] == "arrogant" ||
results[0] == "tarragon"));
#endif
 
cout << "passed";
 return 0;
}
