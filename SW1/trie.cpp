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
                }
                toCrawl=toCrawl->children[index];
            }
            toCrawl->is_leaf=true;
        }
        void printAll(TrieNode* node, string toPrint){
            if(node == NULL)
                return;

            if(node->is_leaf){
                cout << toPrint << endl;
            }

           
            if(node->children[0] != NULL){//if itaint null there ssomething below it 
                printAll(node->children[0], toPrint + '0');
            }

            if(node->children[1] != NULL){
                printAll(node->children[1], toPrint + '1');
            }
        }
        void printLeaves(){
            printAll(root, "");
        }
};

int main(){
    Trieee Trie=Trieee();   
    Trie.insert("1011");
    Trie.insert("1010");
    Trie.insert("100");
    Trie.insert("1000101");
    Trie.printLeaves();
}
