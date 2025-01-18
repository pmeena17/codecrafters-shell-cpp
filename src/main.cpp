#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <filesystem>
#include "header.h"

static const std::string scEmptyString = "";
enum class ValidCommands
{
    invalid, exit, echo, type, cmd
};

const ValidCommands IsValidCommand(std::string sCommand)
{
    sCommand = sCommand.substr(0, sCommand.find(" "));  // FIXME: might fail if the command starts with a " "
    if (sCommand == "exit") return ValidCommands::exit;
    if (sCommand == "echo") return ValidCommands::echo;
    if (sCommand == "type") return ValidCommands::type;
    if (GetValidPath(sCommand) != scEmptyString) return ValidCommands::cmd;
    
    return ValidCommands::invalid;
}

std::string GetValidPath(std::string sCommand)
{
    std::string sPathEnv = std::getenv("PATH");
    std::stringstream ss(sPathEnv);                       // create stringstream object for the PATH env var that we can search through
    std::string sTempPath;

    while (std::getline(ss, sTempPath, ':'))
    {
        std::filesystem::path sDir = sTempPath;          // use filesystem path to automatically take care of OS specific path separator
        std::filesystem::path sValidPath = sDir / sCommand;   // create absoulte path to look for

        if (std::filesystem::exists(sValidPath))               // check if type command exists in PATH substrings
            return sValidPath.string();
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

                if (IsValidCommand(input) != ValidCommands::invalid && IsValidCommand(input) != ValidCommands::cmd)
                    std::cout << input << " is a shell builtin\n";
                else
                {
                    std::string sPath = GetValidPath(input);
                    if (sPath != scEmptyString)
                        std::cout << input << " is " << sPath << '\n';
                    else
                        std::cout << input << " not found\n";
                }
                break;
            }
            case ValidCommands::cmd:
            {
                system(input.c_str());
                // call to exec function with "input" as argument
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
