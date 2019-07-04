#include "decoder.h"

int main(int argc, char *argv[])
{
  std::ifstream file("morse.txt");
  Decoder decoder(file);

  std::string mesage;
  while (std::getline(std::cin, mesage))
    std::cout << decoder.decode_msg(mesage) << std::endl;

  if (argc > 1 && std::string(argv[1]) == "-a")
    decoder.print_trie();

  return 0;
}
