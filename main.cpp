#include<iostream>
#include<map>
using namespace std;

class AdaptiveHuffmanTreeNode{
    public:
        int weight;
        string character;
        AdaptiveHuffmanTreeNode* left;
        AdaptiveHuffmanTreeNode* right;
        AdaptiveHuffmanTreeNode* parent;

        AdaptiveHuffmanTreeNode(){
            this->weight = 0;
            this->character = "";
            this->left = NULL;
            this->right = NULL;
            this->parent = NULL;
        }
};

class AdaptiveHuffmanTree{
    public:
        AdaptiveHuffmanTreeNode* head;
        AdaptiveHuffmanTreeNode* nyt;
        string nytCode;

        AdaptiveHuffmanTree(){
            AdaptiveHuffmanTreeNode *nyt = new AdaptiveHuffmanTreeNode();
            this->head = nyt;
            this->head = nyt;
            this->nytCode = "";
        }
};



string bin(long n){
    long i;
    string s = "";
    s+="0";
    for (i = 1 << 30; i > 0; i = i / 2){
        if((n & i) != 0){
            s+="1";
        }
        else{
            s+="0";
        }
    }
    return s;
}

string fixedCode(int e, int r, int index){
    index = index + 1;
    string output = "";
    //if index lies in [1,2r]
    if(index >=1 && index<=2*r){
        //represent index-1 in (e+1) bits
        string s = bin(index-1);
        for(int i = s.size()-e-1; i<s.size(); i++){
            output+=s[i];
        }
    }
    //else if index lies in [2r+1, infinity]
    else{
        //represent (index-r-1) in e bits
        string s = bin(index-r-1);
        for(int i = s.size()-e; i<s.size(); i++){
            output+=s[i];
        }
    }
    return output;
}

string encode(string input){
    //2 parameters e and r
    // m = 94 = 2^e + r
    //e = 6, r = 30
    int e = 6;
    int r = 30;
    AdaptiveHuffmanTree* tree = new AdaptiveHuffmanTree();
    string output = "";

    map<string, int> existsInTree;
    string s(1, input[0]);
    existsInTree[s] = 1;

    // output += fixedCode(e, r, 0);



    for(int i = 0; i<input.size(); i++){
        //if character is not present in the tree
        if(tree->head->character == ""){
            //output nyt code
            output+=tree->nytCode;
            //output 8 bit ascii code of the character
            output+=fixedCode(e, r, i);
            //update tree
            //create new node with weight 1
            AdaptiveHuffmanTreeNode* newNode = new AdaptiveHuffmanTreeNode();
            newNode->character = input[i];
            newNode->weight = 1;
            //create new nyt node
            AdaptiveHuffmanTreeNode* newNyt = new AdaptiveHuffmanTreeNode();
            newNyt->character = "";
            newNyt->weight = 0;
            //update tree
            tree->head->left = newNyt;
            tree->head->right = newNode;
            tree->head->weight = 1;
            newNyt->parent = tree->head;
            newNode->parent = tree->head;
            tree->head = newNyt;
            //update nyt code
            tree->nytCode = fixedCode(e, r, i);
        }
        //if character is present in the tree
        else{
            //output code of the character
            output+=fixedCode(e, r, i);
            //update tree
            //find node with character = input[i]
            AdaptiveHuffmanTreeNode* node = tree->head;
            string s(1, input[i]);
            while(node->character != s){
                node = node->parent;
            }
            //increment weight of the node
            node->weight+=1;
            //update tree
            //find node with weight = node->weight
            AdaptiveHuffmanTreeNode* node2 = tree->head;
            while(node2->weight != node->weight){
                node2 = node2->parent;
            }
            //if node is not the same as node2
            if(node != node2){
                //swap node and node2
                swap(node, node2);
            }
            //update nyt code
            tree->nytCode = fixedCode(e, r, i);
        }
    }
    return output;

}

int main(){
    string input = "aardvark";
    // cin >> input;
    // cout << fixedCode(4, 10, 21) << endl;
    cout << encode(input) << endl;
    return 0;
}