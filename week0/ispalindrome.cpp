#include <iostream>
using namespace std;

bool isPalindrome(string inputString){
    string copy=inputString;
    int length=copy.size();
    for(int x=1, y=0; x<=length; x++, y++){
        copy[y]=inputString[length-x];
    }
    if (copy==inputString){
        return true;
    }
    else{
        return false;
    }
}

int main(){
    string word;
    char keepGoing='y';
    while(keepGoing=='Y' or keepGoing=='y'){
        cout << "INPUT A STRING : ";
        cin >> word;
        if (isPalindrome(word)==true){
            cout << word << " IS A PALINDROME" << endl;
        }
        else{
            cout << word << " IS NOT A PALINDROME" << endl;
        }
        std::cout << "Continue? Y/N. ";
        std::cin >> keepGoing;
    }
    return 0;
}