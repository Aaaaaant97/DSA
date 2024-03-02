#include "coin.h"
#include <iostream>
#include <chrono> 

int main(){
    std::vector<int> CoinLimit(4,0);
    int Amount;
    std::cout<<"请输入总金额（要求整数，单位：美分）：";
    std::cin>>Amount;
    std::cout<<"请依次输入金额为1、5、10、25美分的硬币数目（要求整数，用空格隔开）：";
    std::cin>>CoinLimit[0]>>CoinLimit[1]>>CoinLimit[2]>>CoinLimit[3];
    auto start = std::chrono::high_resolution_clock::now(); 
    int solution=MinCoinNumber(Amount,CoinLimit);
    auto end = std::chrono::high_resolution_clock::now();  
    std::chrono::duration<double> duration = end - start;  
    std::cout<<solution<<std::endl;
    std::cout << "程序运行时间：" << duration.count() << "秒" << std::endl; 
}