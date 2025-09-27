#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::string input;
  while (true)
  {
    std::cout  << "$ ";
    std::getline(std::cin, input);
    if (std::cin.eof())
    {
      std::cout << std::endl;
      break;
    }
    if (input == "\\q")
    {
      break;
    }
    std::cout <<  input << std::endl;
  }
}
