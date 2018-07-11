#include <iostream>
#include "Decoder.h"
#include "TreeNode.h"
#include "MinHeap.h"
#include "HuffTree.h"
#include <string>
#include <bitset>
#include <fstream>
#include <cstring>
#include <cstddef>
#include <vector>
#include <stdio.h>
using namespace std;
int headerLen;
int numOfBytes;
//constructor                                                                                                                                                                                                                                                                                                                                                               
Decoder::Decoder(string huff_file_path) : frequency_table{0}{
  fileCharLength = 0;
  numOfBytes = 0;
  headerLen = 0;
  this->in_file = huff_file_path;
  heap = new MinHeap();
  tree = new HuffTree();
}


//function to build the frequency table                                                                                                                                                                                                                                                                                                                                     
void Decoder::buildFrequencyTableFromFile()
{
  ifstream inputFile;
  inputFile.open(in_file, ios::in | ios::binary);
  if(inputFile.fail())
    {
      cout<<"error"<<endl;
      return;
    }
  int uniqueChars = this->readtwoByte(inputFile);
  headerLen = uniqueChars;
  int character;
  int frequency;
  for(int i =0;i<uniqueChars;i++)
    {
      character = this->readByte(inputFile);
      frequency = this->readfourByte(inputFile);
      this->frequency_table[character] = frequency;
    }
  fileCharLength = numberChar();
  inputFile.close();
}
//return the length of the header                                                                                                                                                                                                                                                                                                                                           
int getHeaderLength()
{
  return headerLen;
}
//gives the number of chars in file                                                                                                                                                                                                                                                                                                                                         
int Decoder::numberChar(){
  int nChars = 0;
  for(int i = 0; i < 256; i++){
    nChars = nChars + frequency_table[i];
  }
  return nChars;
}
//creates min-heap and build the huffman tree                                                                                                                                                                                                                                                                                                                               
void Decoder::decode()
{
  this->buildFrequencyTableFromFile();
  for(int i = 0;i<256;i++)
    {
      if(frequency_table[i] != 0)
        {
          TreeNode * node = new TreeNode(i,frequency_table[i]);
          heap->insert(node);
        }
    }
  tree->buildTree(heap);
}
//writes uncompressed file and save it as file_path                                                                                                                                                                                                                                                                                                                         
void Decoder::writeUncompressedFile(string file_path)
{
  ofstream outFile;
  outFile.open(file_path);
  ifstream inFile;
  inFile.open(in_file);
  if(inFile.fail())
    {
      return;
    }
  int charByte;
  int length = 0;
  inFile.seekg(0,ios::end);
  length = inFile.tellg();
  inFile.seekg(0,ios::beg);
  string currentBit;
  while(numOfBytes != length)
    {
      if(numOfBytes >= (getHeaderLength()*5+2)){
        charByte = readByte(inFile);
        currentBit = bitset<8>(charByte).to_string();
        bodyBit += currentBit;
      }else{
        readByte(inFile);
      }
      numOfBytes++;
    }
  TreeNode * root = tree->getRoot();
  int end = 0;
  for(int i = 0;i<bodyBit.length();i++)
    {
      if(root->isLeafNode())
        {
          char temp = root->getVal();
          outFile.write((const char*)&temp,1);
          root = tree->getRoot();
          end++;
        }
      if(bodyBit[i] == '0')
        {
          root = root->getRight();
        }else if(bodyBit[i] == '1')
        {
          root = root->getLeft();
        }
      if(end == fileCharLength){
        break;
      }
    }
  inFile.close();//                                                                                                                                                                                                                                                                                                                                                         
}

Decoder::~Decoder()
{
  delete heap;
  delete tree;
}
int Decoder::readByte(ifstream& file)
{
  unsigned char oneByte;
  file.read(reinterpret_cast<char *>(&oneByte),1);
  return (unsigned int)oneByte;
}
int Decoder::readfourByte(ifstream& file)
{
  unsigned char oneByte;
  unsigned char twoByte;
  unsigned char threeByte;
  unsigned char fourByte;
  file.read(reinterpret_cast<char *>(&oneByte),1);
  file.read(reinterpret_cast<char *>(&twoByte),1);
  file.read(reinterpret_cast<char *>(&threeByte),1);
  file.read(reinterpret_cast<char *>(&fourByte),1);
  return (unsigned int)(oneByte | (twoByte << 8) | (threeByte << 16) | (fourByte << 24));
}
int Decoder::readtwoByte(ifstream& file)
{
  unsigned char oneByte;
  unsigned char twoByte;
  file.read(reinterpret_cast<char *>(&oneByte),1);
  file.read(reinterpret_cast<char *>(&twoByte),1);
  return (unsigned int)(twoByte << 8 | oneByte);
}

