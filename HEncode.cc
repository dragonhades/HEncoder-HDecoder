#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <random>
#include <algorithm>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <termios.h>
#include <unistd.h>
using namespace std;
#include "tools.h"

struct Tree;
struct Node;
struct Ascii;

int char_to_int(const char &c){
  if(c=='0') return 0;
  else return 1;
}

void get_bit(int *arr, int &count, const char c){
  count++;
  arr[count-1] = char_to_int(c);
  if(count==8) count=0;
}

string encode(Tree &t,vector<int> &input){
  string s;
  for(auto num:input){
    s += t.list[0].out(num,"");
  }
  return s;
}

void bin_out(const string &s){
  istringstream iss(s);
  char c;
  int count=0;
  int arr[8];
  try {
    while(1){
      for(register int i=0;i<8;i++){
	if(!(iss>>c)) throw 0;
	//cerr<<c;
	get_bit(arr, count, c);
      }
      putchar(arr[0]<<7|arr[1]<<6|arr[2]<<5|arr[3]<<4|arr[4]<<3|arr[5]<<2|arr[6]<<1|arr[7]);
    }
  } catch(...){
    switch(count){
      case 0:
	break;
      case 1:
	putchar(arr[0]<<7);
	break;
      case 2:
	putchar(arr[0]<<7 | arr[1]<<6);
	break;
      case 3:
	putchar(arr[0]<<7 | arr[1]<<6 | arr[2]<<5);
	break;
      case 4:
	putchar(arr[0]<<7|arr[1]<<6|arr[2]<<5|arr[3]<<4);
	break;
      case 5:
	putchar(arr[0]<<7|arr[1]<<6|arr[2]<<5|arr[3]<<4|arr[4]<<3);
	break;
      case 6:
	putchar(arr[0]<<7|arr[1]<<6|arr[2]<<5|arr[3]<<4|arr[4]<<3|arr[5]<<2);
	break;
      case 7:
	putchar(arr[0]<<7|arr[1]<<6|arr[2]<<5|arr[3]<<4|arr[4]<<3|arr[5]<<2|arr[6]<<1);
	break;
    }
  }

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

int main(int argc, char* argv[]){
  if(argc<2){
    cerr<<"Usage: ./HDecode Filename";
    return 0;
  }
  termios oldt;
  tcgetattr(STDIN_FILENO, &oldt);
  termios newt = oldt;
  newt.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  
  while(1){
    cerr<<"Enter password:"<<endl;
    string enter;
    getline(cin, enter);
    cerr<<"Please enter again:"<<endl;
    string again;
    getline(cin, again);
    if(enter!=again){
      cerr<<"The password you entered does not match the pervious one."<<endl;
      cerr<<"Try again."<<endl;
    } else {
      setSeed(enter);
      break;
    }
  }

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

  ifstream fs(argv[1]);
  
  int count=0;
  char inp;
  Ascii ascii1;
  Ascii ascii2;
  vector<int> input;
  int acc = 128;
  while(1){
    ascii1=ascii2;
    input.clear();
    if(count==1) acc=128;
    for(register int i = 0; i<acc; i++){
      fs>>noskipws>>inp;
      if(fs.fail()) {
	//input.emplace_back(128);
	break;
      }
      input.emplace_back(inp);
      int num = (unsigned int) inp;
      ascii2.update(num);
    }
    Tree t(ascii1);
    if(count==0){
      random_shuffle(t.list.begin(),t.list.end());
    }
    t.merge_least();
    bin_out(encode(t,input));
    acc=acc*2;
    count++;
    if(fs.fail()) break;
  }
  //t.huffcode();
  //ascii2.hufffreq();
  //wpl(t,ascii2);
}
