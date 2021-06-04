#include <bits/stdc++.h>
using namespace std;


void ReverseSentence (string* s){
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

    cout << *s;
}

string convertToString(char* a, int size)
{
    string s = "";
    for (int i = 0; i < size; i++){
        s = s + a[i];
    }
    return s;
}

int main(int argc, char const *argv[])
{
    string sentence = "I love programming SooooOOOO much";
    ReverseSentence(std::addressof(sentence));
    return 0;
}
