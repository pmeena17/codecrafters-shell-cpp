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
	if (input.find("echo ") != string::npos) // if you find "echo " in the input stream
		std::cout << input.substr(input.find("echo ")); // print everything after "echo "
	std::cerr << input << ": command not found\n";
  }
}
