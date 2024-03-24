#include <iostream>
#include <string>
using namespace std;

class TrieNode{
    public:
        char data; //either a one or a zero / dit or dah
        TrieNode *children[2]; //binary !! max of two nodes only per node
        bool is_leaf; //life easy
        TrieNode(char ooz); //oneorzero
};

TrieNode::TrieNode(char ooz){
    data=ooz;
    is_leaf=false;
    children[0]=NULL;
    children[1]=NULL;
}

class Trieee{
    public:
        int numberOfnodes=1; //root node
        int numberOfdigits=0;
        TrieNode* root;
        Trieee(){
            root=new TrieNode('\0');
        }
        void insert(string key){
            TrieNode* toCrawl=root;
            for(int i=0; i<key.size(); i++){
                int index=key[i]-'0';
                if((toCrawl->children[index])==NULL){
                    toCrawl->children[index]=new TrieNode(key[i]);
                    numberOfnodes+=1;
                }
                toCrawl=toCrawl->children[index];
            }
            toCrawl->is_leaf=true;
        }
        void addAll(TrieNode* node, string toPrint){
            if(node == NULL)
                return;

            if(node->is_leaf){
                numberOfdigits+=toPrint.length();
            }
           
            if(node->children[0] != NULL){//if itaint null there ssomething below it 
                addAll(node->children[0], toPrint + '0');
            }

            if(node->children[1] != NULL){
                addAll(node->children[1], toPrint + '1');
            }
        }
        void printInfoNeeded(){
            addAll(root, "");
            cout<<"Number of digits in all binary strings: "<< numberOfdigits <<endl;
            cout<<"Number of nodes in Trie: "<< numberOfnodes <<endl;
            // cout<<"Max Prefix Length"<< <<endl;
            // cout<<"Total Substrings"<< <<endl;
            // cout<<"Prefix Goodness"<< <<endl;
            // https://stackoverflow.com/a/72077798/23393994
        }
};

int main(){
    Trieee Trie=Trieee();   
    Trie.insert("01010010101010101010");
    Trie.insert("11010010101010101010");
    Trie.printInfoNeeded();
}
