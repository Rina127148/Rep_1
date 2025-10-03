#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>

std::vector<std::string> loadHistory()
{
  std::vector<std::string> history;
  std::string homeDir = getenv("HOME");
  std::string historyFile = homeDir + "/.kubsh_history";

  std::ifstream file(historyFile);
  if(file.is_open())
  {
    std::string line;
    while (std::getline(file, line))
    {
      if (!line.empty())
      {
        history.push_back(line);
      }
    }
    file.close();
  }
  return history;
}

void saveHistory(const std::vector<std::string>& history)
{
  std::string homeDir = getenv("HOME");
  std::string historyFile = homeDir + "/.kubsh_history";

  std::ofstream file(historyFile);
  if (file.is_open())
  {
    for (const auto& cmd : history)
    {
      file << cmd << std::endl;
    }
    file.close();
  }
}

void handleEcho(const std::string&input)
{
  size_t echoPos = input.find("echo");
  if (echoPos == std::string::npos)return ;
  std::string args=input.substr(echoPos+4);
  size_t firstChar = args.find_first_not_of(" ");
  if (firstChar != std::string::npos)
  {
    args =args.substr(firstChar);
  }
  if (args.size() >= 2 && ((args.front()=='"'&&args.back()=='"')|| (args.front()=='\'' &&args.back()=='\'')))
  {
    args = args.substr(1, args.size()-2);
  }
  std::cout << args << std::endl;
}

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::vector<std::string> history = loadHistory();
  const size_t MAX_HISTORY_SIZE = 100;

  std::string input;
  while (true)
  {
    std::cout  << "$ ";
    std::getline(std::cin, input);
    if (std::cin.eof())
    {
      std::cout << std::endl;
      break;
    }
    if (input == "\\q")
    {
      break;
    }
    if (!input.empty())
    {
      history.push_back(input);
      if (history.size() > MAX_HISTORY_SIZE)
      {
        history.erase(history.begin());
      }
    }
    if (input.find("echo")== 0)
    {
      handleEcho(input);
    }
    else
    {
      std::cout << input << std::endl;
    }
  }
  saveHistory(history);
  return (0);
}
