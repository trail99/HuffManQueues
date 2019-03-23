#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>

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

//typedef struct Node Node;

struct compare {
  bool operator()(Node* l, Node* r) { return (l->freq > r->freq); }
};

void print(Node* root, std::string s) {
  if(!root) return;
  if(root->data != '$') std::cout<<root->data<<": "<<s<<std::endl;

  print(root->left,s+"0");
  print(root->right,s+"1");
}

void makeTree(char data[], int freq[], int size) {
  std::priority_queue<Node*, std::vector<Node*>, compare> Heap;
  Node* left, *right, *top;
  for(int i = 0; i < size; ++i) Heap.push(new Node(data[i], freq[i]));

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

int main() {
  char L[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
  int F[] = { 5, 9, 12, 13, 16, 45 };

  int size = sizeof(L)/sizeof(L[0]);
  makeTree(L, F, size);

  return 0;

}
