#ifndef HEADER
#define HEADER

struct Ascii {
  vector<int> freq;
  Ascii();
  void update(const int index);
  void print();
  void hufffreq();
  void clear();
};

struct Node {
  int c;
  int weight;
  shared_ptr<Node> left=nullptr;
  shared_ptr<Node> right=nullptr;
  Node(const int c, const int weight):c{c},weight{weight}{}
  string out(const int c, const string &s);
};

struct Tree {
  vector<Node>list;
  Tree(const Ascii &a);
  void merge_least();
  void huffcode();
  void print();
};

void setSeed(string &s);
#endif
