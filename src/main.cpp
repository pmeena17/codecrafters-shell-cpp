#include <iostream>
#include <string>
#include <vector>

int main()
{
    const int nEchoLength = 5;
    const int nTypeLength = 5;
    static bool bExit = false;

    while (!bExit)
    {
        // Flush after every std::cout / std:cerr
        std::cout << std::unitbuf;
        std::cerr << std::unitbuf;

        std::cout << "$ "; // prompt

        std::string input;
        std::getline(std::cin, input);
        bool bIsInputValid = false;

        if (input.find("exit") == 0) // exit command
        {
            bExit = true;
            bIsInputValid = true;
        }

        if (input.find("echo") == 0) // echo command
        {
            std::cout << input.substr(nEchoLength) << '\n'; // print everything after "echo "
            bIsInputValid = true;
        }

        if (input.find("type") == 0) // type command
        {
            std::string sSub = input.substr(nTypeLength); // get the command following "type"
            if (sSub.substr(0, 4) == "exit" || sSub.substr(0, 4) == "echo" || sSub.substr(0, 4) == "type") // check if the command matches any built-in commands. TODO: use sBuiltIn for look-up?
                std::cout << sSub << " is a shell builtin\n";
            else
                std::cout << sSub << ": not found\n";
            bIsInputValid = true;
        }

        if (!bIsInputValid)
            std::cout << input << ": command not found\n";	// invalid command
    }
    return 0;
}
