#include <iostream>
#include <chrono>
#include "BigInt.h"

int main(){
    // auto start = std::chrono::steady_clock::now();   
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
            std::cout << ((fs < sd) ? "True" : "False") << std::endl;
        }
        else if(symbol == '>'){
            std::cout << ((fs > sd) ? "True" : "False") << std::endl;
        }
        else if(symbol == '='){
            std::cout << ((fs == sd) ? "True" : "False") << std::endl;
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
    // auto end = std::chrono::steady_clock::now();
    // std::chrono::duration<double> elapsed_seconds = end-start;
    // std::cout << "C++ time: " <<  elapsed_seconds.count() << std::endl;
}
