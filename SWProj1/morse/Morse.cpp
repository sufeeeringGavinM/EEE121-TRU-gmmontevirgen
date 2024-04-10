#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class TrieNode{ //noticabely trimmed off unneccessary variables like is_leaf
    public:
        char data; //either a one or a zero / dit or dah
        TrieNode *children[2]; //binary !! max of two nodes only per node
        string loc; //save "location" of node within trie e.g: e is 0, a is 01
        // dang, i couldve applied this location thing to the prefixGoodness problem (but like eeeehhh)
        TrieNode(char ooz){
            data=ooz;
            children[0]=NULL;
            children[1]=NULL;
        }
};
class Trieee{
    public:
        TrieNode* root;
        vector<string> valids = {
            ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", 
            "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", 
            "..-", "...-", ".--", "-..-", "-.--", "--..", ".----", "..---", "...--", 
            "....-", ".....", "-....", "--...", "---..", "----.", "-----", ".-.-.-"
        };
        Trieee(){
            root=new TrieNode('\0');
        }
        void insert(string key, char repr){
            TrieNode* toCrawl=root;
            string keyConverted;
            for(int i=0; i<key.size(); i++){ // O(n) where n length of key
                int index=key[i]-'0';
                if((toCrawl->children[index])==NULL){
                    toCrawl->children[index]=new TrieNode(key[i]); // children[0] having a new TrieNode means a zero, children[1] means a one. traversing through the trie node for a string 101 would then be like root->children[1]->children[0]->children[1].
                }
                toCrawl=toCrawl->children[index];
                
                if(key[i]=='0'){
                    keyConverted+='.'; // tracking "location" as mentioned before ++ might as well do it while you're traversing the entire key to keep it all O(n)
                }
                else{
                    keyConverted+='-';
                }
            }
            valids.push_back(key);
            toCrawl->data=repr;
            toCrawl->loc=keyConverted; 
        }
        void decode(TrieNode* node, char toFind, string &decoded){ //function very reminiscent of recursiveness of getnumofchildren() prefixGoodness subprob
            if(node==NULL){
                return;
            }
            if(node->data==toFind){
                decoded += (node->loc);
                return;
            }
            if(node->children[0]!=NULL){
                decode(node->children[0], toFind, decoded);
            }
            if(node->children[1]!=NULL){
                decode(node->children[1], toFind, decoded);
            }
            return;
        }

        string endecode(string input){ //encode or decode?
            bool encode=true;
            string result;
            string currentChar="";
            int i;
            TrieNode* crawler=root;
            // https://cplusplus.com/reference/string/string/find/
            // "If no matches [of c] were found [in string], the function [string.find('c')] returns string::npos."
            if(input.find('/') != string::npos || input.find('.') != string::npos || input.find('-') != string::npos){
                encode=false; // not encoding if dits or dahs or slahs are present
            } 
            if(encode==false){ //O(n) where n is length of thing to be decoded
                for(i=0; i<input.size(); i++){ // O(n)
                    if((find(valids.begin(),valids.end(),currentChar))==valids.end() && currentChar!="" && currentChar!="..--" && currentChar!="---." && currentChar!="----" ){ //check if current charafcter is valid, also the three conditions at the end are just specfific cases i found in the morse tree where the condition just kind of does not work
                        result+="#"; //error character
                        currentChar=""; //current char in morse code **
                        crawler=root; //
                    }
                    if(input[i]=='.'){
                        crawler=crawler->children[0]; //0 is .
                        currentChar.push_back('.');
                    }
                    if(input[i]=='-'){
                        crawler=crawler->children[1]; //1 is -
                        currentChar.push_back('-');
                    }
                    if(input[i]==' '){
                        result.push_back(crawler->data); //take letter every space
                        crawler=root;
                        currentChar="";
                    }
                    if(input[i]=='/'){
                        result.push_back(crawler->data);
                        result.push_back(' ');
                        currentChar="";
                        crawler=root;
                    }
                    if(i==(input.size()-1)){
                        if((find(valids.begin(),valids.end(),currentChar))==valids.end() && currentChar!="" ){
                            result+="#";
                            currentChar="";
                            return result;
                        }
                        result.push_back(crawler->data);
                        return result;
                    }
                }
            }
            else{ //O(nlogn)
                for(int i=0; i<input.size();i++){ //O(n)
                    if(input[i]==' '){
                        result += " / ";
                    }
                    else{
                        decode(root, toupper(input[i]), result); // O(logn), i think.  also, everything'll be in uppercase
                        result += " ";
                    }
                }
            }
            return result;          
        }
};

int main(){
    Trieee MorseTree=Trieee(); 

    //morse tree initialization!
    //here 0 is (t)dit (.), 1 is dah (-)
    MorseTree.insert("01",'A'); //a
    MorseTree.insert("1000",'B');//b
    MorseTree.insert("1010",'C');//c
    MorseTree.insert("100",'D');//d
    MorseTree.insert("0",'E');//e
    MorseTree.insert("0010",'F');//f
    MorseTree.insert("110",'G');//g
    MorseTree.insert("0000",'H');//h
    MorseTree.insert("00",'I');//i
    MorseTree.insert("0111",'J');//j
    MorseTree.insert("101",'K');//k
    MorseTree.insert("0100",'L');//l
    MorseTree.insert("11",'M');//m
    MorseTree.insert("10",'N');//n
    MorseTree.insert("111",'O');//o
    MorseTree.insert("0110",'P');//p
    MorseTree.insert("1101",'Q');//q
    MorseTree.insert("010",'R');//r
    MorseTree.insert("000",'S');//s
    MorseTree.insert("1",'T');//t
    MorseTree.insert("001",'U');//u
    MorseTree.insert("0001",'V');//v
    MorseTree.insert("011",'W');//w
    MorseTree.insert("1001",'X');//x
    MorseTree.insert("1011",'Y');//y
    MorseTree.insert("1100",'Z');//z
    MorseTree.insert("01111",'1');//1
    MorseTree.insert("00111",'2');//2
    MorseTree.insert("00011",'3');//3
    MorseTree.insert("00001",'4');//4
    MorseTree.insert("00000",'5');//5
    MorseTree.insert("10000",'6');//6
    MorseTree.insert("11000",'7');//7
    MorseTree.insert("11100",'8');//8
    MorseTree.insert("11110",'9');//9
    MorseTree.insert("11111",'0');//0

    string decodeorencodemepleaseee121;
    getline(cin, decodeorencodemepleaseee121);
    cout << MorseTree.endecode(decodeorencodemepleaseee121)<<endl;
}

