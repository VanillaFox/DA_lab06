#include <iostream>
#include "BigInt.h"

int main()
{
    std::string first, second;
    char symbol;
    while(std::cin >> first >> second >> symbol){
        TBigInt fs(first), sd(second);
        
        if(symbol == '+'){
            std::cout << fs + sd << std::endl;
        }
        else if(symbol == '-'){
            try{
                std::cout << fs - sd << std::endl;
            }
            catch(int i){
                std::cout << "Error\n";
            }
        }
        else if(symbol == '*'){
            std::cout << fs * sd << std::endl;
        }
        else if(symbol == '/'){
            try{
                std::cout << fs / sd << std::endl;
            }
            catch(int i){
                std::cout << "Error\n";
            }
        }
        else if(symbol == '<'){
            std::cout << ((fs < sd) ? "true" : "false") << std::endl;
        }
        else if(symbol == '>'){
            std::cout << ((fs > sd) ? "true" : "false") << std::endl;
        }
        else if(symbol == '='){
            std::cout << ((fs == sd) ? "true" : "false") << std::endl;
        }
        else if(symbol == '^'){
            try{
                std::cout << (fs ^ sd) << std::endl;
            }
            catch(int c){
                std::cout << "Error" << std::endl; 
            }
        }
    }
}
