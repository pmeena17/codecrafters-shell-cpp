#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <filesystem>

static const std::string scEmptyString = "";
enum class ValidCommands
{
    invalid, exit, echo, type
};

const ValidCommands IsValidCommand(std::string sCommand)
{
    sCommand = sCommand.substr(0, sCommand.find(" "));
    if (sCommand == "exit") return ValidCommands::exit;
    if (sCommand == "echo") return ValidCommands::echo;
    if (sCommand == "type") return ValidCommands::type;
    
    return ValidCommands::invalid;
}

std::string GetValidPath(std::string sCommand)
{
    std::string sPathEnv = std::getenv("PATH");

    size_t pos = 0;
    std::string sTemp;
    while ((pos = sPathEnv.find(':')) != std::string::npos) // break PATH into smaller strings at the delimiter " : "
    {
        sTemp = sPathEnv.substr(0, pos);
        if (sTemp.find(sCommand) != std::string::npos)      // check if type command exists in PATH substrings
            return sTemp;
        sPathEnv.erase(0, pos + 1); // 1 because lenght of " : " is 1
    }

    return scEmptyString;
}

int main()
{
    static bool bExit = false;
    while (!bExit)
    {
        // Flush after every std::cout / std:cerr
        std::cout << std::unitbuf;
        std::cerr << std::unitbuf;
        std::cout << "$ "; // prompt

        std::string input;
        std::getline(std::cin, input);

        switch (IsValidCommand(input))
        {
            case ValidCommands::exit:
            {
                bExit = true;
                break;
            }
            case ValidCommands::echo:
            {
                input.erase(0, input.find(" ") + 1); // remove "echo ", then print the command
                std::cout << input << '\n';
                break;
            }
            case ValidCommands::type:
            {
                input.erase(0, input.find(" ") + 1); // remove "type "

                if (IsValidCommand(input) != ValidCommands::invalid)
                    std::cout << input << " is a shell builtin\n";
                else
                {
                    std::string sPath = GetValidPath(input);
                    if (sPath != scEmptyString)
                        std::cout << sPath << " is " << input << '\n';
                    else
                        std::cout << input << " not found\n";
                }
                break;
            }
            case ValidCommands::invalid: // fall-through
            default:
            {
                std::cout << input << ": command not found\n";	// invalid command
                break;
            }
        }
    }
    return 0;
}
