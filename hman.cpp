#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <map>
#include <iterator>

struct Node {
  char data;
  unsigned freq;
  Node* left;
  Node* right;

  Node(char data, unsigned freq) {
    left = right = NULL;
    this->data = data;
    this->freq = freq;
  }
};

struct compare {
  bool operator()(Node* l, Node* r) { return (l->freq > r->freq); }
};

void print(Node* root, std::string s) {
  if(!root) return;
  if(root->data != '$') std::cout<<root->data<<": "<<s<<std::endl;

  print(root->left,s+"0");
  print(root->right,s+"1");
}

void makeTree(std::map<char, int> fMap) {
  std::priority_queue<Node*, std::vector<Node*>, compare> Heap;
  Node* left, *right, *top;
  for(auto it = fMap.begin(); it != fMap.end(); ++it) Heap.push(new Node(it->first, it->second));

  while(Heap.size() != 1) {
    left = Heap.top();
    Heap.pop();
    right = Heap.top();
    Heap.pop();

    top = new Node('$', left->freq + right->freq);
    top->left = left;
    top->right = right;
    Heap.push(top);
  }

  print(Heap.top(), "");
}

const int countChar(const std::string& text, const char& key) {
  int n = text.length(); int fCount = 0;
  for(int i = 0; i < n; ++i) if(text[i] == key) fCount++; 
  return fCount;
}

void calcFreq(std::map<char, int>& fMap, const std::string& text) {
  int n = text.length();
  for(int i = 0; i < n; ++i) {
    fMap.insert(std::pair<char, int> (text[i], countChar(text,text[i])));
  }
}

int main() {

    std::string text; std::map<char, int> fMap;
    std::map<char, int>::iterator it;
    std::cout<<"\n Enter the string: ";
    getline(std::cin, text);
    calcFreq(fMap, text);  
   
    std::cout<<"\tCHAR\tVALUE\n";
    for(it = fMap.begin(); it != fMap.end(); ++it) 
      std::cout<<'\t'<<it->first<<'\t'<<it->second<<'\n';
    
    makeTree(fMap);
  
  return 0;

}
