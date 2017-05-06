#ifndef HEADER
#define HEADER

// int defined in tool.cc, see more details there
// Used to set the acc for huffman coding loop sequence
// Default to 128
extern unsigned int ACCUMULATOR;

class Ascii {
  std::vector<int> freq;
public:
  Ascii();
 // return rvalue of instances of freq
  int operator[](const int i) const ;
  void update(const int index);
  void print();
  // Debug tool to calculate the huffman freqency
  void hufffreq();
  // clear the freq
  void clear();
};

class Node {
  int c;
  int weight;
public:
  std::shared_ptr<Node> left=nullptr;
  std::shared_ptr<Node> right=nullptr;
  Node(const int c, const int weight):c{c},weight{weight}{}
  //recursively concatenate the binary bits to s as it goes down the tree.
  std::string out(const int c, const std::string &s);
  int get_weight() const ;
  int get_intChar() const ;
};

class Tree {
  std::vector<Node>list;
public:
  Tree(const Ascii &a);
  Node front() const ;
  std::vector<Node>::iterator begin() ;
  std::vector<Node>::iterator end() ;
  // merge the least weighted two nodes in list from left to right
  void merge_least();
  // Debug tool to output the temporary huffman code
  void huffcode();
  void print();
};

// use given string to set seed
void setSeed(std::string &s);

// return the depth of inp down the Node n
int depth(const Node &n, int inp);

// debug tooll to return the wpl value of the tree and ascii
void wpl(Tree &t, Ascii &a);

#endif
