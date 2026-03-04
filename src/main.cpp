#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>


int main() {
  
  while(true){
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

   std::cout << "$ ";

  std::string command;
  std::getline(std::cin,command);

if(command=="exit"){
  break;
}

else if(command.substr(0,4)=="echo"){
  std::cout << command.substr(5) << std::endl;
}

else if(command.substr(0,4)=="type"){
  if(command.substr(5,8)=="echo")
    std::cout << command.substr(5,8) << " is a shell builtin" << std::endl;

    else if(command.substr(5,8)=="exit")
    std::cout << command.substr(5,8)<< " is a shell builtin" << std::endl;
    
  else if(command.substr(5,8)=="type")
    std::cout << command.substr(5,8)<< " is a shell builtin" << std::endl;

    else{
      std::string path_env=std::getenv("PATH");
      std::stringstream ss_path(path_env);
      std::string path;
      bool found=false;
      while(std::getline(ss_path,path,':')){
        std::string full_path=path + '/' + command.substr(5);
        if(access(full_path.c_str(),X_OK)==0){
          std::cout << command.substr(5) << " is " << full_path << std::endl;
          found=true;
          break;
        }
        if(!found)
            std::cout << command.substr(5) << ": not found" << std::endl;
      }
    }

}

  else{
  std::cout<<command <<": command not found" << "\n";
}
  }

}
