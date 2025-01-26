#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <filesystem>
#include "header.h"

// TODO: Refactoring
// create a command type class with types: built-in, executable, invalid
// call member function on command object to check for the type and
// get valid path if it's an executable
/*
enum class Type { Invalid, Builtin, Executable };
class CommandType
{
public:
    CommandType(std::string in)
    {
        m_command = IsValidCommand(in);
    }
private:
    Type m_command;
    Type IsValidCommand(std::string in);
    std::string GetValidPath();
};
*/

static const std::string scEmptyString = "";
enum class ValidCommands
{
    invalid, exit, echo, type, pwd, cd, cmd, count
};

const ValidCommands IsValidCommand(std::string sCommand)
{
    static_assert(ValidCommands::count == static_cast<ValidCommands>(7)); // check the code below if new valid commands are added

    sCommand = sCommand.substr(0, sCommand.find(" "));  // FIXME: might fail if the command starts with a " "
    if (sCommand == "exit") return ValidCommands::exit;
    if (sCommand == "echo") return ValidCommands::echo;
    if (sCommand == "type") return ValidCommands::type;
    if (sCommand == "pwd") return ValidCommands::pwd;
    if (sCommand == "cd") return ValidCommands::cd;
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
                
                ValidCommands nIsBuiltIn = IsValidCommand(input);
                if (nIsBuiltIn != ValidCommands::invalid && nIsBuiltIn != ValidCommands::cmd)
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
            case ValidCommands::pwd:
            {
                system(input.c_str());
                // call to exec function with "input" as argument
                break;
            }
            case ValidCommands::cd:
            {
                input.erase(0, input.find(" ") + 1); // remove "cd "

                if (std::filesystem::exists(input))
                    std::filesystem::current_path(input);
                else
                    std::cout << "cd: " << input << ": No such file or directory\n";
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
