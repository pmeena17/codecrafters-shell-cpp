#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

int main()
{
    const int nEchoLength = 5;
    const int nTypeLength = 5;
    static bool bExit = false;
    std::string sPath = std::getenv("PATH");

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
            std::string sSub = "";
            if (input.length() >= nTypeLength)
                sSub = input.substr(nTypeLength); // get the command following "type"
            else
                continue;
            
            size_t pos = 0;
            std::string sTemp;
            while ((pos = sPath.find(':')) != std::string::npos) // break PATH into smaller strings at the delimiter " : "
            {
                sTemp = sPath.substr(0, pos);
                if (sTemp.find(sSub) != std::string::npos)             // check if type command exists in PATH substrings
                {
                    std::cout << sSub << " is " << sTemp << '\n';      // print the first result if found
                    break;
                }
                sPath.erase(0, pos + 1); // 1 because lenght of " : " is 1
            }

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
