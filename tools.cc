#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <algorithm>
#include <random>
using namespace std;

#include "tools.h"

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
    list.emplace_back(i,a.freq[i]);
  }
  //list.emplace_back(128, 1);
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
  int min = list[0].weight;
  auto least=list.begin();
  for(auto l=list.begin();l!=list.end();l++){
    if(l->weight<min) {
      min = l->weight;
      least=l;
    }
  }
  Node temp = *least;
  list.erase(least);
  min = list[0].weight;
  auto second=list.begin();
  for(auto l=list.begin();l!=list.end();l++){
    if(l->weight<min){
      min = l->weight;
      second = l;
    }
  }
  int left = temp.weight;
  int right = second->weight;
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

int depth(Node &n, int inp){
  if(inp == n.c){
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
    int freq = a.freq[i];
    if(freq==0) continue;
    int dep = depth(t.list[0],i);
    sum += freq*dep;
  }
  ofstream of("huff.wpl");
  of<<sum<<endl;
}	
