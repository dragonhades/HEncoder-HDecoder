#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <algorithm>
#include <random>
using namespace std;

#include "tools.h"

// Global int defined for HEncode.cc and HDecode.cc to adjust the acc for 
//  huffman loops. Default to 128
// Since the number of all outcome of random_shuffle is ACCUMULATOR! (factorial)
//  smaller the nummber, more unsafe it gets.
// But the huffman compression works better if the file charator count 
//  exceeds ACCUMULATOR by great amount.
// Hence, change this number accordingly to get the best compression results.
// WARNING: the program does not check the validity of this number.
//          Any unexpected results due to the change of this number is not responsible
//          by the program.
unsigned int ACCUMULATOR=128;

int Node::get_weight() const {
  return weight;
}

int Node::get_intChar() const {
  return c;
}

string Node::out(const int inp, const string &s){
  if(inp == c){
    return s;
  } else {
    if((!left)&&(!right)) throw 0;
    if(!left){
      return right->out(inp,s+"1");
    }
    try {
      return left->out(inp,s+"0");
    } catch(...){
      if(!right) throw 0;
      else return right->out(inp,s+"1");
    }
  }
}

Tree::Tree(const Ascii &a){
  for(register int i=0;i<128;i++){
    list.emplace_back(i,a[i]);
  }
}

Node Tree::front() const {
  if(list.empty()) throw "List is empty";
  return list[0];
}

vector<Node>::iterator Tree::begin() {
  return list.begin();
}

vector<Node>::iterator Tree::end() {
  return list.end();
}

void Tree::huffcode(){
  ofstream of("huff.code");
  for(register int i=0;i<128;i++){
    string s = list[0].out(i,"");
    of<<s<<endl;
  }
}

void Tree::merge_least(){
  if(int(list.size())==1) return;
  int min = list[0].get_weight();
  auto least=list.begin();
  for(auto l=list.begin();l!=list.end();l++){
    if(l->get_weight()<min) {
      min = l->get_weight();
      least=l;
    }
  }
  Node temp = *least;
  list.erase(least);
  min = list[0].get_weight();
  auto second=list.begin();
  for(auto l=list.begin();l!=list.end();l++){
    if(l->get_weight()<min){
      min = l->get_weight();
      second = l;
    }
  }
  int left = temp.get_weight();
  int right = second->get_weight();
  Node n(-1,left+right);
  n.left = make_shared<Node>(temp);
  n.right = make_shared<Node>(*second);
  list.erase(second);
  list.emplace_back(n);
  return merge_least();
}

Ascii::Ascii(){
  for(register int i=0;i<128;i++){
    freq.emplace_back(0);
  }
}

int Ascii::operator[](const int i) const {
  return freq[i];
}

void Ascii::update(const int index){
  freq[index]++;
}

void Ascii::print(){
  for(auto it:freq){
    cerr<<it<<endl;
  }
}

void Ascii::hufffreq(){
  ofstream of("huff.freq");
  for(auto it:freq){
    of<<it<<endl;
  }
}

void Ascii::clear(){
  freq.clear();
  for(register int i=0;i<128;i++){
    freq.emplace_back(0);
  }
}

void setSeed(string &s){
  seed_seq seed(s.begin(),s.end());
  default_random_engine generator(seed);
  int gen = generator();
  srand(gen);
}

int depth(const Node &n, int inp){
  if(inp == n.get_intChar()){
    return 0;
  } else {
    if((!n.left)&&(!n.right)) throw 0;
    if(!n.left){
      return 1+depth(*n.right,inp);
    }
    try {
      return 1+depth(*n.left,inp);
    } catch(...){
      if(!n.right) throw 0;
      else return 1+depth(*n.right,inp);
    }
  }
}

void wpl(Tree &t, Ascii &a){
  int sum=0;
  for(int i=0; i<128; i++){
    int freq = a[i];
    if(freq==0) continue;
    int dep = depth(t.front(),i);
    sum += freq*dep;
  }
  ofstream of("huff.wpl");
  of<<sum<<endl;
}	
