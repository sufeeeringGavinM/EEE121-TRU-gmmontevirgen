#include <iostream>

bool isPrime(int number){
    if(number==0 or number==1){
            return false;
        }
    int num2=2;
    while(num2<=number/2){
        if(number%num2==0){
            return false;
        }
        num2++;
    }
    return true;
}


int main(){
    int numb;
    std::string keepGoing="y";
    while(keepGoing=="y" or keepGoing=="Y"){
        std::cout << "INPUT AN INTEGER : ";
        std::cin >> numb;
        if (isPrime(numb)==true){
            std::cout << numb << " IS A PRIME NUMBER" << std::endl;
        }
        else{
            std::cout << numb << " IS NOT A PRIME NUMBER" << std::endl;
        }
        std::cin.clear();
        std::cin.ignore(10000,'\n');
        std::cout << "Continue? Y/N. ";
        std::cin >> keepGoing;
        while(keepGoing!="y" and keepGoing!="Y" and keepGoing!="n" and keepGoing!="N"){ //input check
            std::cout << "That's not N or Y, let's try that again: ";
            std::cin >> keepGoing;
            }
    }
    return 0;
}