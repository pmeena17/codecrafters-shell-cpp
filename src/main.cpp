#include <iostream>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  while (std::cin)
  {
	std::cout << "$ ";
	std::string input;
	std::getline(std::cin, input, '\n');
	std::cerr << input << ": command not found\n";
  }
}
