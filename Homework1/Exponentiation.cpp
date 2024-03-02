#include<iostream>
using namespace std;

double pospower(double x,int n){
    if(n==0){
      return 1;//n为0时返回x的零次方，即1
    }else{
        double p=pospower(x,n/2);
        if(n/2*2==n){
	    //n为偶数
            return p*p;
        }else{
	    //n为奇数
            return p*p*x;
        }
    }
}

int main(){
    double x;
    int n;
    cin >> x >> n;//先输入实数x，后输入整数n
    if(n>=0){
        cout << pospower(x,n) << endl;
    }else{
        cout << 1/pospower(x,-n) << endl;
    }
    return 0;
}
