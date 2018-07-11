#ifndef DECODER_H
#define DECODER_H
#include "TreeNode.h"
#include "MinHeap.h"
#include "HuffTree.h"
#include <string>

using namespace std;



class Decoder
{
 private:
  unsigned frequency_table[256];//array to hold freq of chars at the ascii position                                                                                                                                                                                                                                                                                         
  string in_file;//file for opening input file                                                                                                                                                                                                                                                                                                                              
  MinHeap * heap;//minheap to hold the minheap for hufftree                                                                                                                                                                                                                                                                                                                 
  HuffTree * tree;//to build hufftree                                                                                                                                                                                                                                                                                                                                       
  string bodyBit;//string to hold the body of file                                                                                                                                                                                                                                                                                                                          
  int fileCharLength;//length of the the unique char                                                                                                                                                                                                                                                                                                                        
 public:
  //huff_file_path is the input (encoded) file that we                                                                                                                                                                                                                                                                                                                      
  //want to decode                                                                                                                                                                                                                                                                                                                                                          
  Decoder(string huff_file_path);
  //read one byte                                                                                                                                                                                                                                                                                                                                                           
  int numberChar();
  int readByte(ifstream& file);
  //read two byte                                                                                                                                                                                                                                                                                                                                                           
  int readtwoByte(ifstream& file);
  //read four byte                                                                                                                                                                                                                                                                                                                                                          
  int readfourByte(ifstream& file);

  //Fills up the frequency_table array where frequency_table[i]                                                                                                                                                                                                                                                                                                             
  //will contain the frequency of char with ASCII code i                                                                                                                                                                                                                                                                                                                    
  //This method will read the header of the encoded file to                                                                                                                                                                                                                                                                                                                 
  //extract the chars and their frequency                                                                                                                                                                                                                                                                                                                                   
  void buildFrequencyTableFromFile();

  //Creates a min-heap and builds the Huffman tree                                                                                                                                                                                                                                                                                                                          
  void decode();

  //Writes the uncompressed file and save it as file_path                                                                                                                                                                                                                                                                                                                   
  void writeUncompressedFile(string file_path);

  ~Decoder();

};

#endif
