#include <iostream>
#include <string>
#include <vector>


using namespace std;

class TrieNode{
    public:
        // char data; //either a one or a zero / dit or dah (foreshadowing) DONT NEED THIS FOR NOW HTOUGH
        TrieNode* children[2]; //binary !! max of two nodes only per node UPDATE: I REGRET THIS HOW WOULD I HANDLE DUPLICATES!? UPDATE2: ok just do add anothe property of the node indicating how many copies of it exist (if ther are)
        bool is_leaf; 
        int copies; //number of copies
        TrieNode(){ //oneorzero (mr robot reference)
            // data=ooz; //realized later on i didnt really need this
            is_leaf=false;
            copies=0; //by default, no copies
            children[0]=NULL;
            children[1]=NULL;
        }
};

class Trieee{
    public:
        TrieNode* root;
        vector<TrieNode*> prefixNodes;
        vector<string> twoprefixes; // 
        int numberOfDigits=0;
        int numberOfNodes=1; //always ONE root node in there
        string biggest; //track biggest string for special case where no common prefixes exist
        TrieNode* biggestNode;
        Trieee(){
            root=new TrieNode();
        }
        void insert(string key){
            TrieNode* toCrawl=root;
            for(int i=0; i<key.size(); i++){
                int index=key[i]-'0';
                if((toCrawl->children[index])==NULL){
                    toCrawl->children[index]=new TrieNode(); // children[0] having a new TrieNode means a zero, children[1] means a one. traversing through the trie node for a string 101 would then be like root->children[1]->children[0]->children[1].
                    numberOfNodes++; //tracker of num of nodes
                }
                if(i==(key.size()-1) && toCrawl->children[index]->is_leaf==true){ //if key's leaf node already exists, we are adding a copy
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
                biggestNode=toCrawl; //note that biggest node will never have a copy as if it does, this function would have returned already!
            }
        }
        void findPrefixes(TrieNode* node, string pref) //obtains all common prefixes, puts them in a vector of strings
        {   
            if(node == NULL)
                return;
            if(node->children[0] != NULL && node->children[1] !=NULL){ // a prefix is something with at least two children
                twoprefixes.push_back(pref); // collect prefix itself
                prefixNodes.push_back(node); // collect node containing prefix
            }
            if(node->children[0] != NULL){
                findPrefixes(node->children[0], pref+'0'); // adds a 0 to pref, as children[0] being not null indicates a zero
            }

            if(node->children[1] != NULL){
                findPrefixes(node->children[1], pref+'1'); // adds a 1 instead, as children[1]  beign not null means a one
            }
            //for the recursion to go thru the entire tree , I followed how this article below did it. though instead of with the aim of printing everything, it was just to find those with at least two children (prefixes) 
            // https://www.ritambhara.in/print-all-words-in-a-trie-data-structure/
        }
        void getNumberofChildren(TrieNode* node, int &substrings){ //vibes r giving O(nlogn)
            if(node==NULL){
                return;
            }
            if(node->is_leaf){
                substrings++;
                substrings+=node->copies; // if a leaf node has copies, add them
            }
            if(node->children[0]!=NULL){
                getNumberofChildren(node->children[0], substrings); //traverse the hell out of that trie
                
            }
            if(node->children[1]!=NULL){
                getNumberofChildren(node->children[1], substrings);
            }
        }
        void printDetails(){
            string longestPrefix;
            int longestPG=0;
            int substrings=0;
            int mostsubstrings=0;
            int currentPrefixSize;
            int currentPG;
            int longestPrefixSize=0;
            findPrefixes(root, "");
            
            for(int i=0; i<twoprefixes.size(); i++){
                substrings=0;
                getNumberofChildren(prefixNodes[i], substrings);
                currentPrefixSize=twoprefixes[i].size();
                currentPG=currentPrefixSize*substrings;
                if(currentPrefixSize>longestPrefixSize && currentPG >= longestPG){ //the longer prefix the better , while also maximizing prefixgoodness
                    longestPG=currentPG;
                    mostsubstrings=substrings;
                    longestPrefix=twoprefixes[i];
                    longestPrefixSize=currentPrefixSize;
                }
            }
            if(mostsubstrings==0 || biggest.size()>longestPG){ 
                //special case when there are no common prefixes
                // also if the largest string is just straight up greater than the max prefix goodness
                mostsubstrings=1;
                longestPrefixSize=biggest.size();
                longestPG=longestPrefixSize;
            }
            cout<<"Number of digits in all binary strings: " << numberOfDigits <<endl;
            cout<<"Number of nodes in Trie: "<< numberOfNodes << endl;
            cout<<"Max Prefix Length : " << longestPrefixSize << endl;
            cout<<"Total Substrings : " << mostsubstrings << endl;
            cout<<"Prefix Goodness : " << longestPG << endl;
            

            // DEBUGGING PURPOSES 
            // display each possible prefix
            
            // for(int i=0; i<twoprefixes.size(); i++){
            //     cout << twoprefixes[i] << endl;
            // }
            // cout <<endl;

    
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
