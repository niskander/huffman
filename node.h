#ifndef __NODE_H__
#define __NODE_H__

#include <string>
#include <map>

class Node {
     friend bool operator<(const Node& a, const Node& b);
     friend bool operator>(const Node& a, const Node& b);
     friend bool operator>=(const Node& a, const Node& b);
     friend bool operator<=(const Node& a, const Node& b);
     friend bool operator==(const Node& a, const Node& b);
     friend bool operator!=(const Node& a, const Node& b);

public:
     Node();
     Node(int freq_sum, char c);
     Node(int freq_sum, Node* left, Node* right);
     int FreqSum();
     Node* Left();
     Node* Right();
     void GenerateCodeTable(std::map<char, std::string>& code_table, std::string code);

private:
     char c_;
     int freq_sum_;
     Node* left_;
     Node* right_;
};

#endif
