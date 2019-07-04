#ifndef DECODER_H
#define DECODER_H

#include <iostream>
#include <string>
#include <fstream>
#include <functional>
#include <sstream>

struct Node
{
  std::string key;
  std::string val;
  Node *next[2];
};

class Decoder
{
private:
  Node *root;

  Node *insert(Node *node, std::string key, std::string val, int pos);
  Node *search(Node *node, std::string key, int pos);
  void post_order(Node *node, std::function<void(Node *)> fn);
  void pre_order(Node *node, std::function<void(Node *)> fn);

public:
  Decoder(std::ifstream &file);
  ~Decoder();
  std::string decode_msg(std::string msg);
  void print_trie();
};

#endif
