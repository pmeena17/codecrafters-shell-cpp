#include <iostream>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::string input;

  while (std::cin >> input)
  {
	std::cout << "$ ";
	std::getline(std::cin, input, '\n');
	std::cerr << input << ": command not found\n";
  }
}
