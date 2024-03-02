#ifndef COIN_H
#define COIN_H
/**
 * @file coin.h
 * @brief 用于硬币找零问题的头文件
 * @author ZhongQi (3210103612@zju.edu.cn)
 * @version 1.0
 * @date 2023-12-23
 */
#include <vector>
#include <algorithm>
#include <climits>

struct coin
{
    int num;/*所需硬币总数目*/
    int number[4];/*number[0]~number[3]分别表示所需1、5、10、25美分硬币数目*/
};

/**
 * @brief 返回最少所需硬币数目的函数
 * @param  Amount           输入总金额
 * @param  coins            1、5、10、25美分硬币的数目
 * @return int 
 */
int MinCoinNumber(int Amount,std::vector<int>& coins){
        int i;
        std::vector<int> T={1,5,10,25};
        std::vector<coin> n(4,{INT_MAX,0,0,0,0});/*对应动态规划Amount-1、Amount-5、Amount-10、Amount-25四种策略所需要的硬币数目情况*/
        std::vector<coin> dp(Amount+1,{INT_MAX,0,0,0,0});/*存储0～Amount金额所需硬币数目最少时的情况*/
        dp[0].num=0;
        for(i=1;i<=Amount;i++){
            n[0].num=INT_MAX;n[1].num=INT_MAX;n[2].num=INT_MAX;n[3].num=INT_MAX;/*初始化为最大值，便于后续比较*/
            for(int t=0;t<=3;t++){/*遍历四种策略*/
                    if(i>=T[t]&&dp[i-T[t]].num!=INT_MAX){
                        /*i>=T[t]保证dp[i-T[t]]的存在性，否则该策略无意义*/
                        /*dp[i-T[t]].num!=INT_MAX保证总金额为i-T[t]时硬币分配方法存在的可能性，否则该策略无意义*/
                    if(dp[i-T[t]].number[t]<coins[t]){
                        /*保证先前所有的t种类硬币还有所剩余，否则该策略没办法应用于动态规划中*/
                        n[t].num=dp[i-T[t]].num+1;
                        /*多一个t种类的硬币，所以总硬币数+1*/
                        n[t].number[t]=dp[i-T[t]].number[t]+1;
                        /*t种类的硬币数也+1*/
                        for(int j=0;j<=3;j++){
                            if(j!=t){
                                n[t].number[j]=dp[i-T[t]].number[j];
                                /*其他种类的硬币数不变*/
                            }
                        }
                    }
                    if(dp[i].num>n[t].num){
                        /*选择所需总硬币数最少的情况，并复制该情况到dp[i]中*/
                        dp[i].num=n[t].num;
                        for(int p=0;p<=3;p++){
                            dp[i].number[p]=n[t].number[p];
                        }
                    }
                }
            }
        }
            if(dp[Amount].num!=INT_MAX){
                /*总金额为Amount时该问题有解，返回最小总硬币数*/
                return dp[Amount].num;
            }else{
                /*该问题无解，返回-1*/
                return -1;
            }
    }


#endif
