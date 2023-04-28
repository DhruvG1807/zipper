#include<iostream>
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
        string nytCode;

        AdaptiveHuffmanTree(){
            AdaptiveHuffmanTreeNode *nyt = new AdaptiveHuffmanTreeNode();
            this->head = nyt;
            this->nytCode = "";
        }
};

string encode(string input){
    //2 parameters e and r
    // m = 94 = 2^e + r
    //e = 6, r = 30
}

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



int main(){
    string input;
    // cin >> input;
    cout << fixedCode(4, 10, 21) << endl;
    //expected answer: 000000
    return 0;
}