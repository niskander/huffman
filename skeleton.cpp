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

int Usage(int argc, char** argv) {
  printf("Usage: %s -<e | d> <input file> <output file>\n", argv[0]);
  return 1;
}

int encode(const char* input, const char* output) {
  int size = 0, freq[256];
  memset(freq, 0, sizeof freq);

  std::ifstream fin(input, std::ios::in | std::ios::binary);
  if (!fin) return 1;

  char c;
  while (fin.read(&c, 1)) ++size, ++freq[c + 128];
  fin.clear(), fin.seekg(0);

  // TODO(student): 1. Build the Huffman tree

  // TODO(student): 2. Encode and output
  std::ofstream fout(output, std::ios::out | std::ios::binary);
  while (fin.read(&c, 1)) {
    fout.write(&c, 1);
  }

  fin.close();
  fout.close();

  return 0;
}

int decode(const char* input, const char* output) {
  // TODO(student): Implement this function.
  return 0;
}

int main(int argc, char** argv) {
  // Input validation
  if (argc != 4)
    return Usage(argc, argv);
  if (argv[1][0] != '-' || (argv[1][1] != 'e' && argv[1][1] != 'd'))
    return Usage(argc, argv);

  if (argv[1][1] == 'e') {
    return encode(argv[2], argv[3]);
  } else {
    return decode(argv[2], argv[3]);
  }

  return 0;
}
