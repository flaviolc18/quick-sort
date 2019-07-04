#include "decoder.h"

Decoder::Decoder(std::ifstream &file)
{
  this->root = nullptr;
  if (file.is_open())
  {
    std::string key, value;
    while (!file.eof())
    {
      file >> value >> key;
      this->root = this->insert(this->root, key, value, 0);
    }
  }
  file.close();
}

Decoder::~Decoder()
{
  this->post_order(this->root, [](Node *node) { free(node); });
}

Node *Decoder::insert(Node *node, std::string key, std::string val, int pos)
{

  if (node == nullptr)
    node = new Node();
  if (pos == (int)key.length())
  {
    node->key = key;
    node->val = val;
    return node;
  }
  int child = key[pos] == '.' ? 0 : 1;
  node->next[child] = this->insert(node->next[child], key, val, pos + 1);
  return node;
}

Node *Decoder::search(Node *node, std::string key, int pos)
{
  if (node == nullptr)
    return nullptr;
  if (pos == (int)key.length())
    return node;
  int c = key[pos] == '.' ? 0 : 1;
  return this->search(node->next[c], key, pos + 1);
}

void Decoder::pre_order(Node *node, std::function<void(Node *)> fn)
{
  if (node == nullptr)
    return;
  fn(node);
  this->pre_order(node->next[0], fn);
  this->pre_order(node->next[1], fn);
}

void Decoder::post_order(Node *node, std::function<void(Node *)> fn)
{
  if (node == nullptr)
    return;
  post_order(node->next[0], fn);
  post_order(node->next[1], fn);
  fn(node);
}

std::string Decoder::decode_msg(std::string msg)
{
  std::stringstream decoded_msg, encoded_msg(msg);
  std::string token;
  while (std::getline(encoded_msg, token, ' '))
  {
    if (token == "/")
      decoded_msg << " ";
    else
      decoded_msg << this->search(this->root, token, 0)->val;
  }
  return decoded_msg.str();
}

void Decoder::print_trie()
{
  this->pre_order(this->root, [](Node *node) {
    if (node->val != "")
      std::cout << node->val << " " << node->key << std::endl;
  });
}
