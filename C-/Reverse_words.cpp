#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

void ReverseWords(string s) {
    vector<string> tmp;
    string str = "";
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == ' ') //check for blank space
        {
            tmp.push_back(str); // push word(str) to vector
            str = "";// make str null
        }
        else //add character to str to form current word
        str += s[i];
    }
    // last word remaining, add it to vector 
    tmp.push_back(str);

    // Printing from last to first in vector
    int i;
    for (i = tmp.size() - 1; i > 0; i--)
        cout << tmp[i] << " ";
    //last word to print
    cout << tmp[0] << endl;
}
/*}
    //First, reverses the whole string.
    reverse(begin(*s), end(*s));

    size_t start = 0, finish;
    while ((finish = s->find(" ", start)) != string::npos) {
        //Reverses each word in the string.
        reverse(begin(*s) + start, begin(*s) + finish);
        start = finish + 1;
    }
    // Reverses the last word.
    reverse(begin(*s) + start, end(*s));
}*/

int main(){
    string s = "  i love programming";
    ReverseWords(s);
    return 0;
}