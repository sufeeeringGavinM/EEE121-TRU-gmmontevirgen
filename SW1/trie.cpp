#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class TrieNode{
    public:
        char data; //either a one or a zero / dit or dah (foreshadowing)
        TrieNode *children[2]; //binary !! max of two nodes only per node
        bool is_leaf; //life easy
        TrieNode(char ooz); //oneorzero (mr robot reference)
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
        vector<string> twoprefixes; // prefixes for those with TWO children
        vector<string> oneprefix; //prefixes for those with ONE child
        int numberOfDigits=0;
        int numberOfNodes=1; //always a root node in there
        Trieee(){
            root=new TrieNode('\0');
        }
        void insert(string key){
            TrieNode* toCrawl=root;
            for(int i=0; i<key.size(); i++){
                int index=key[i]-'0';
                if((toCrawl->children[index])==NULL){
                    toCrawl->children[index]=new TrieNode(key[i]);
                    numberOfNodes++;
                }
                toCrawl=toCrawl->children[index];
            }
            toCrawl->is_leaf=true;
            numberOfDigits+=key.length();
        }
        void findPrefixes(TrieNode* node, string pref) //obtains all common prefixes, puts them in a vector of strings
        {   
            if(node == NULL)
                return;
            if(node->children[0] != NULL && node->children[1] !=NULL){ //finds prefix 
                twoprefixes.push_back(pref); //prefix concactenated with its size
            }
            if((node->children[0] != NULL && node->children[1] ==NULL) or (node->children[0] == NULL && node->children[1] !=NULL)){
                oneprefix.push_back(pref);
            }
            if(node->children[0] != NULL){
                findPrefixes(node->children[0], pref + '0'); //goes through entire trie, similar to 
            }

            if(node->children[1] != NULL){
                findPrefixes(node->children[1], pref + '1');
            }
            //for the recursion to go thru the entire tree , I followed how this article below did it. though instead of with the aim of printing everything, it was just to find those with at least two children (prefixes) 
            // https://www.ritambhara.in/print-all-words-in-a-trie-data-structure/
        }

        void printDetails(){
            findPrefixes(root, "");
            cout<<"Number of digits in all binary strings: " << numberOfDigits <<endl;
            cout<<"Number of nodes in Trie: "<< numberOfNodes << endl;
            int longestPrefix=twoprefixes[0].size();
            for(int i=1; i<twoprefixes.size(); i++){
                if(twoprefixes[i].size()>longestPrefix){
                    longestPrefix=twoprefixes[i].size();
                }
            }
            cout<<"Max Prefix Length : " << longestPrefix << endl;
            // cout<<"Total Substrings : " << totalSubStrings << endl;
            // cout<<"Prefix Goodness : " << prefixGoodness << endl;
            
            for(int i=0; i<twoprefixes.size(); i++){
                cout << twoprefixes[i] << endl;
            }
            cout <<endl;
            // for(int i=0; i<oneprefix.size(); i++){
            //     cout << oneprefix[i] << endl;
            // }
        }
};

void testCasesHandler(){
    int numOfTests;
    Trieee Trie=Trieee();
    cout << "" ;
    cin >> numOfTests;
    string toAdd;
    for(int i=0; i<numOfTests; i++){
        cin >> toAdd;
        Trie.insert(toAdd);
    }
    Trie.printDetails();

}

int main(){
    int realNumofTests;
    cout<<"";
    cin >> realNumofTests;
    for(int j=1; j<=realNumofTests ; j++){
        cout << "Test Case #" << j <<":" << endl;
        testCasesHandler();
    }
}
