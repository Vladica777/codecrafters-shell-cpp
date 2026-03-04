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

  std::cout<<command <<": command not found" << "\n";
  }

}
