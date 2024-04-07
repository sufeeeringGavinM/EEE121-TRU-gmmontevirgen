#include <iostream>
#include <string>
using namespace std;

class TrieNode{
    public:
        char data; //either a one or a zero / dit or dah
        TrieNode *children[2]; //binary !! max of two nodes only per node
        bool is_leaf; //life easy
        int copies;
        TrieNode(char ooz){
            data=ooz;
            is_leaf=false;
            copies=0;
            children[0]=NULL;
            children[1]=NULL;
        }
};

class Trieee{
    public:
        int numberOfnodes=1; //root node
        int numberOfdigits=0;
        int numberOfNodes=1;
        int numberOfDigits=0;
        TrieNode* biggestNode;
        TrieNode* root;
        string biggest;
        Trieee(){
            root=new TrieNode('\0');
        }
        void insert(string key){
            TrieNode* toCrawl=root;
           
            for(int i=0; i<key.size(); i++){
                int index=key[i]-'0';
                if((toCrawl->children[index])==NULL){
                    toCrawl->children[index]=new TrieNode(key[i]);
                    numberOfNodes++; //tracker of num of nodes
                }
                if(toCrawl->children[index]->is_leaf==true){
                    numberOfDigits++;
                    toCrawl->children[index]->copies++; // if we are adding a duplicate string, we simply add 1 to its "copies". only leaf nodes can have duplicates!
                    return;
                }
                toCrawl=toCrawl->children[index];
                numberOfDigits++; //tracker of num of digits. we're going through key.size() might as well add a O(1) thingy here to collect key.size()'s value
            }
            toCrawl->is_leaf=true; 
            if(key.size()>biggest.size()){
                biggest=key;
                biggestNode=toCrawl; //note that biggest node will never have a duplicate as if it does, this function would have returned already!
            }
        }
};

int main(){
    Trieee Trie=Trieee();   
    Trie.insert("01010010101010101010");
    Trie.insert("11010010101010101010");
}
