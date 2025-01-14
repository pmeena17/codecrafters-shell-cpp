#include <iostream>
#include <vector>

int main()
{
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    const int nEchoLength = 5;
    const int nTypeLength = 5;

    std::vector<std::string> sBuiltIn = { "exit", "echo", "type" };

    std::string input;
    while (std::getline(std::cin, input))
    {
        std::cout << "$ "; // prompt

        if (input.find("exit") == 0) // exit command
            return 0;

        if (input.find("echo") == 0) // echo command
        {
            std::cout << input.substr(nEchoLength) << '\n'; // print everything after "echo "
            continue;
        }

        if (input.find("type") == 0) // type command
        {
            std::string sSub = input.substr(nTypeLength); // get the command following "type"
            if (find(sBuiltIn.begin(), sBuiltIn.end(), sSub) != sBuiltIn.end()) // check if the command exists in built-in commands
                std::cout << sSub << " is a shell builtin\n";
            continue;
        }

        std::cout << input << ": command not found\n";	// invalid command
    }
}
