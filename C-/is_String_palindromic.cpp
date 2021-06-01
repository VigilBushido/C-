#include <iostream>
#include <string>
#include <vector>
using namespace std;


bool IsPalindrone( const string& s ){
    int i = 0, j = sizeof(s) - 1;

    while (i < j)
    {   
        /*i and j both skip non-alphanumeric characters.*/
        while (!isalnum(s[i]) && i < j)
        {
            ++i;
        }
        while (!isalnum(s[j]) && i < j)
        {
            --j;
        }
        if (tolower(s[i++]) != tolower(s[j--])){
            return false;
        }
        
    }
    return true;
}


int main() {
    
	string str1 = "A man, a plan, a canal, Panama.";
	cout << "Initial String  : " << str1 << endl;
	cout << " Results (1= pos, 0= neg): " << IsPalindrone(str1);
	return 0;
}