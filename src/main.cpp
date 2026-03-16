#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

int main()
{

  while (true)
  {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::cout << "$ ";

    std::string command;
    std::getline(std::cin, command);

    if (command == "exit")
    {
      break;
    }

    else if (command.substr(0, 4) == "echo")
    {
      std::cout << command.substr(5) << std::endl;
    }

    else if(command.substr(0,3)=="pwd"){
      char path[1024];
      if(getcwd(path,sizeof(path)) != nullptr)
        std::cout << path << std::endl;
    }

    else if (command.substr(0, 4) == "type")
    {
      std::string target = command.substr(5);

      if (target == "echo" || target == "exit" || target == "type" || target=="pwd")
      {
        std::cout << target << " is a shell builtin" << std::endl;
      }
      else
      {

        const char *path_cstr = std::getenv("PATH");
        std::string path_env = path_cstr ? path_cstr : "";

        std::stringstream ss_path(path_env);
        std::string path;
        std::string executable_path;
        bool found = false;

        while (std::getline(ss_path, path, ':'))
        {
          std::string full_path = path + '/' + target;

          if (access(full_path.c_str(), X_OK) == 0)
          {
            std::cout << target << " is " << full_path << std::endl;
            found = true;
            break;
          }
        }

        if (!found)
        {
          std::cout << target << ": not found" << std::endl;
        }
      }
    }

    else
    {
      std::istringstream iss(command);
      std::vector<std::string> args;
      std::string token;

      while (iss >> token)
      {
        args.push_back(token);
      }

      if (args.empty())
        continue;

      const char *path_cstr = std::getenv("PATH");
      std::string path_env = path_cstr ? path_cstr : "";

      std::stringstream ss_path(path_env);
      std::string path;
      std::string executable_path;
      bool found = false;

      while (std::getline(ss_path, path, ':'))
      {
        std::string full_path = path + "/" + args[0];
        if (access(full_path.c_str(), X_OK) == 0)
        {
          executable_path = full_path;
          found = true;
          break;
        }
        
      }

      if (!found)
        {
          std::cout << args[0] << ": command not found" << std::endl;
          continue;
        }

        std::vector<char *> argv;
        for (std::string &arg : args)
        {
          argv.push_back(&arg[0]);
        }

        argv.push_back(nullptr);

        pid_t pid = fork();

        if (pid == 0)
        {
          execv(executable_path.c_str(), argv.data());
          _exit(1);
        }
        else if (pid > 0)
        {
          waitpid(pid, nullptr, 0);
        }

    }
  }
  return 0;
}
