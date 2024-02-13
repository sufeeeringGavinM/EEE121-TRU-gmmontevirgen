#include <iostream>
using namespace std;

bool isPalindrome(string inputString){
    string copy=inputString;
    int length=copy.size();
    for(int x=1, y=0; x<=length; x++, y++){
        copy[y]=inputString[length-x];
    }`
    if (copy==inputString){
        return true;
    }
    else{
        return false;
    }
}

int main(){
    string word;
    string keepGoing="y";
    while((keepGoing=="Y" or keepGoing=="y") and (keepGoing!="n" or keepGoing!="N")){
        cout << "INPUT A STRING : ";
        cin >> word;
        if (isPalindrome(word)==true){
            cout << word << " IS A PALINDROME" << endl;
        }
        else{
            cout << word << " IS NOT A PALINDROME" << endl;
        }
        cin.clear();
        cin.ignore(10000,'\n');
        cout << "Continue? Y/N. ";
        cin >> keepGoing;
        while(keepGoing!="y" and keepGoing!="Y" and keepGoing!="n" and keepGoing!="N"){
            cout << "That's not N or Y, let's try that again: ";
            cin >> keepGoing;
        }
    }
    return 0;
}