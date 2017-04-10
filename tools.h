#ifndef HEADER
#define HEADER

// int defined in tool.cc, see more details there
// Used to set the acc for huffman coding loop sequence
// Default to 128
extern unsigned int ACCUMULATOR;

struct Ascii {
  std::vector<int> freq;
  Ascii();
  void update(const int index);
  void print();
  void hufffreq();
  void clear();
};

struct Node {
  int c;
  int weight;
  std::shared_ptr<Node> left=nullptr;
  std::shared_ptr<Node> right=nullptr;
  Node(const int c, const int weight):c{c},weight{weight}{}
  std::string out(const int c, const std::string &s);
};

struct Tree {
  std::vector<Node>list;
  Tree(const Ascii &a);
  void merge_least();
  void huffcode();
  void print();
};

void setSeed(std::string &s);

int depth(Node &n, int inp);

void wpl(Tree &t, Ascii &a);

#endif
