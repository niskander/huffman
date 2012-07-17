//--------------------------------------------------------------------------------
// This is an implementation of Huffman coding; part of an assignment for CC371
// (Analysis and Design of Algorithms) at Alexandria University.
// The skeleton provided can be found in skeleton.cpp.
//--------------------------------------------------------------------------------
// Copyright (c) 2011 Alexandria University
//
// CC371 - Analysis and Design of Algorithms
// Spring 2011
// Programming Assignment(3-1)
// By Ahmed Abdelkader
//
// Licensed under the Creative Commons Attribution-ShareAlike License.
// To view this license, visit http://creativecommons.org/licenses/by-sa/3.0/

#include <iostream>  // NOLINT
#include <fstream>   // NOLINT
#include <stdio.h>
#include <string.h>
#include <deque>
#include <map>

#include "MinPriorityQueue.h"
#include "node.h"

using namespace std;

struct CharCode {
     char c;
     char n_bits;
     char code;
}; // CharCode

int Usage(int argc, char** argv) {
     printf("Usage: %s -<e | d> <input file> <output file>\n", argv[0]);
     return 1;
} // Usage

char StringToChar(const string& s) {
     char sum = 0;
     int shift = 7;
     for (int i = 0; i < (int)s.length(); ++i) {
	  if (s[i] == '1') {
	       sum += (1 << shift);
	  } // if
	  --shift;
     } // for
     return sum;
} // StringToChar

string CharToString(const char c, char n_bits) {
     string s("");
     s.resize(n_bits);
     for (int i = 0; i < n_bits; ++i) {
	  if (c & (1 << i)) s[n_bits-1-i] = '1';
	  else s[n_bits-1-i] = '0';
     } // for
     return s;
} // CharToString

int encode(const char* input, const char* output) {
     int size = 0, freq[256];
     memset(freq, 0, sizeof freq);

     std::ifstream fin(input, std::ios::in | std::ios::binary);
     if (!fin) return 1;

     char c;
     //while (fin.read(&c, 1)) ++size, ++freq[c + 128];
     while (fin.read(&c, 1)) {
	  ++size, ++freq[(int)c];
     } // while
     fin.clear(), fin.seekg(0);

     // TODO(student): 1. Build the Huffman tree
     int diff_chars = 0;
     MinPriorityQueue<Node> q;

     for (int i = 0; i < 256; ++i) {
	  if (freq[i] != 0) {
	       Node n(freq[i], (char)i);
	       q.Insert(n);
	       ++diff_chars;
	  } // if
     } // for

     while (q.GetLength() > 1) {
	  Node* n1 = new Node();
	  *n1 = q.ExtractMin();
	  Node* n2 = new Node();
	  *n2 = q.ExtractMin();
	  Node* n3 = new Node();
	  *n3 = Node(n1->FreqSum() + n2->FreqSum(), n1, n2);
	  q.Insert(*n3);
     } // while

     Node root = q.ExtractMin();
     map<char, string> code_table;
     root.GenerateCodeTable(code_table, "");

     // TODO(student): 2. Encode and output
     std::ofstream fout(output, std::ios::out | std::ios::binary);
     if (!fout.is_open()) {
	  printf("Output file could not be opened/created.\n");
	  fin.close();
	  fout.close();
	  return 1;
     } // if

     // TODO: diff_chars could be 256
     char diff_chars_char = (char)diff_chars;
     fout.write(&diff_chars_char, sizeof(diff_chars_char));

     // Write the code table to the output file
     map<char, string>::iterator it;
     for (it = code_table.begin(); it != code_table.end(); ++it) {
	  char code_char = StringToChar((*it).second);
	  char n_bits = (char)((*it).second).length();
	  //printf("%c: %d\n", (*it).first, (int)code_char);
	  //printf("%c: %s\n", (*it).first, ((*it).second).c_str());
	  // The character
	  fout.write(&((*it).first), sizeof((*it).first));
	  // Length of code
	  fout.write(&n_bits, sizeof(n_bits));
	  // Code
	  fout.write(&code_char, sizeof(code_char));
     } // for

     char bits = 7;
     char byte = 0;
     while (fin.read(&c, 1)) {
	  string code_str = code_table[c];
	  for (int i = 0; i < (int)code_str.length(); ++i) {
	       if (code_str[i] == '1') {
		    byte |= (1 << bits);
	       } // if
	       --bits;
	       if (bits == -1) {
		    fout.write(&byte, 1);
		    bits = 7;
		    byte = 0;
	       } // if
	  } // for
     } // while
     if (byte != 0) {
	  fout.write(&byte, 1);
     } // if

     fin.close();
     fout.close();

     return 0;
} // encode

int decode(const char* input, const char* output) {
     // TODO(student): Implement this function.
     std::ifstream fin(input, std::ios::in | std::ios::binary);
     std::ofstream fout(output, std::ios::out | std::ios::binary);
     if (!fin || !fout) return 1;

     char diff_chars = 0;
     char min_n_bits = 8;
     fin.read(&diff_chars, 1);
     CharCode* code_table = new CharCode[diff_chars];
     printf("diff_chars: %d\n", (int)diff_chars);

     for (int i = 0; i < diff_chars && !fin.bad() && !fin.fail(); ++i) {
	  fin.read(&code_table[i].c, 1);
	  fin.read(&code_table[i].n_bits, 1);
	  fin.read(&code_table[i].code, 1);
	  if (code_table[i].n_bits < min_n_bits) min_n_bits = code_table[i].n_bits;
     } // for

     string code_str = "";
     char code_bits = 0;
     char code = 0;
     char c = 0;
     while (fin.read(&c, 1)) {
	  for (char bit = 7; bit >= 0; --bit) {
	       if (c & (1 << bit)) {
		    code |= (1 << (7-code_bits));
	       } // if
	       ++code_bits;
	       if (code_bits >= min_n_bits) {
		    for (int i = 0; i < diff_chars; ++i) {
			 if (code_bits == code_table[i].n_bits && 
			     code == code_table[i].code) {
			      fout.write(&code_table[i].c, 1);
			      code_bits = 0;
			      code = 0;
			      break;
			 } // if
		    } // for
	       } // if
	  } // for
     } // while

     fin.close();
     fout.close();
     return 0;
} // decode

int main(int argc, char** argv) {
     // Input validation
     if (argc != 4) Usage(argc, argv);
     if (argv[1][0] != '-' || (argv[1][1] != 'e' && argv[1][1] != 'd'))
	  Usage(argc, argv);

     if (argv[1][1] == 'e') {
	  return encode(argv[2], argv[3]);
     } else {
	  return decode(argv[2], argv[3]);
     } // if

     return 0;
} // main

// compile-command: "g++ main.cpp node.cpp"
