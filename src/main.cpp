#include <iostream>
#include <string>

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

    else 
    std::cout << command.substr(5) << ": not found";
}

  else{
  std::cout<<command <<": command not found" << "\n";
}
  }

}
