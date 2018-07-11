#include <iostream>
#include "TreeNode.h"
#include "MinHeap.h"
#include "Encoder.h"
#include "HuffTree.h"
#include <fstream>
#include <bitset>
#include <string>

using namespace std;
//constructor                                                                                                                                                                                                                                                                                                                                                               
Encoder::Encoder(string file_path){
  this->in_file = file_path;
  tree = new HuffTree();
  heap = new MinHeap();

}
//read from file build table                                                                                                                                                                                                                                                                                                                                                
void Encoder::buildFrequencyTable(){
  ifstream inFile;
  inFile.open(in_file);
  if(inFile.fail()){
    cout<<"error"<<endl;
    return;
  }
  else{
    char c;
    while(inFile.get(c)){
      unsigned char ascii = c;
      frequency_table[ascii]++;
    }
  }
  inFile.close();//dont forget to close infile                                                                                                                                                                                                                                                                                                                              
}
//build tree get codes                                                                                                                                                                                                                                                                                                                                                      
void Encoder::encode(){
  this->buildFrequencyTable();
  for(int i = 0; i < 256; i++){
    if(frequency_table[i] != 0){
      TreeNode * tn = new TreeNode(i,frequency_table[i]);
      heap->insert(tn);
    }
  }
  tree->buildTree(heap);
  tree->generateCodes();
}

//write out to file the compressed file                                                                                                                                                                                                                                                                                                                                     
void Encoder::writeEncodedFile(string output_file_path){
  ofstream outFile;
  outFile.open(output_file_path, ios::out | ios::binary);
  if (outFile.fail())
    {
    cout<<"error"<<endl;
    return;
    }
  int unique = tree->charHolder.size();
  outFile.write((const char *)&unique,2);
  for(int x = 0; x < 256; x++){
    if(frequency_table[x] != 0){
      int charFrequency = frequency_table[x];
      outFile.write((const char *)&x,1);
      outFile.write((const char *)&charFrequency,4);
    }
  }
  ifstream inFile;
  inFile.open(in_file);
  if(inFile.fail())
    return;
  char c;
  string bitCodeLine = "";
  while(inFile.get(c) ){
    int asciiVal = (int)(c);
    string charCode = tree->getCharCode(asciiVal);
    bitCodeLine += charCode;
  }
  int index;
  string convert;
  for(index = 0; index < bitCodeLine.length(); ){
    int count8 = 0;
    convert = "";
    while(count8 < 8 && index < bitCodeLine.length() ){
      convert+= bitCodeLine[index];
      count8++;
      index++;
    }
    int cL;
    for(cL = convert.length(); cL < 8; cL++){
      convert += "0";
    }
    bitset<8> bit(convert);
    unsigned long bits = bit.to_ulong();
    outFile.write((const char *)&bits,1);
  }
  //close files!                                                                                                                                                                                                                                                                                                                                                            
  outFile.close();
  inFile.close();
}
//destructor                                                                                                                                                                                                                                                                                                                                                                
Encoder::~Encoder(){
  delete tree;
  delete heap;
}
