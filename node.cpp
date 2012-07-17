#include "node.h"

Node::Node() {
     left_ = right_ = NULL;
     freq_sum_ = 0;
     c_ = '\0';
}

Node::Node(int freq_sum, char c) {
     freq_sum_ = freq_sum;
     left_ = NULL;
     right_ = NULL;
     c_ = c;
}

Node::Node(int freq_sum, Node* left, Node* right) {
     freq_sum_ = freq_sum;
     left_ = left;
     right_ = right;
     c_ = '\0';
}

int Node::FreqSum() { return freq_sum_; }
Node* Node::Left() { return left_; }
Node* Node::Right() { return right_; }

void Node::GenerateCodeTable(std::map<char, std::string>& code_table, std::string code) {
     if (this->left_ == NULL && this->right_ == NULL) {
	  code_table[c_] = code;
	  return;
     }
     if (this->left_ != NULL) {
	  std::string left_code = code;
	  left_code.push_back('0');
	  left_->GenerateCodeTable(code_table, left_code);
     }
     if (this->right_ != NULL) {
	  std::string right_code = code;
	  right_code.push_back('1');
	  right_->GenerateCodeTable(code_table, right_code);
     }
}

bool operator<(const Node& a, const Node& b) {
     return a.freq_sum_ < b.freq_sum_;
}

bool operator>(const Node& a, const Node& b) {
     return a.freq_sum_ > b.freq_sum_;
}

bool operator>=(const Node& a, const Node& b) {
     return a.freq_sum_ >= b.freq_sum_;
}

bool operator<=(const Node& a, const Node& b) {
     return a.freq_sum_ <= b.freq_sum_;
}

bool operator==(const Node& a, const Node& b) {
     return a.freq_sum_ == b.freq_sum_;
}

bool operator!=(const Node& a, const Node& b) {
     return a.freq_sum_ != b.freq_sum_;
}
