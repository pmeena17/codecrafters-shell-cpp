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
	if (input == "exit 0")
		return 0;
	std::cerr << input << ": command not found\n";
  }
}
