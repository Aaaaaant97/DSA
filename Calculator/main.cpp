/**
 * @file main.cpp
 * @brief a simple calculator to achieve the four fundamental admixture operations of arithmetic
 * @author 钟琦 (3210103612@zju.edu.cn)
 * @version 3.0
 * @date 2023-10-30
 */
#include<iostream>
#include<string>
#include<stack>
#include<queue>
#include<cstdlib>
#include <fstream>  

/**
 * @brief 用于储存输入中缀表达式中的元素
 */
struct ele{
    double num;
    char symbol;
};

/**
 * @brief 表达式错误警告
 */
void _err_exp(){
        std::cout<<"Error"<<std::endl;
};

/**
 * @brief 无法识别有效表达式
 */
void _no_exp(){
        std::cout<<"No Expressions Identified!"<<std::endl;
};

/**
 * @brief 除数为零警告
 */
void _div_zero(){
    std::cout<<"Can not be divided by zero!"<<std::endl;
}

/**
 * @brief 无法打开测试文件input.txt警告
 */
void _err_file(){
        std::cerr << "Cannot open the file!" << std::endl;  
        exit(-1);
};

/**
 * @brief 判断是否是'+''-''*''/'
 * @param  c                My Param doc
 * @return true 
 * @return false 
 */
bool isOp(char c){
    if(c=='+'||c=='-'||c=='*'||c=='/'){
        return true;
    }else{
        return false;
    }
};

/**
 * @brief 判断是否是数字
 * @param  c                My Param doc
 * @return true 
 * @return false 
 */
bool isDigit(char c){
    if(c>='0'&&c<='9'){
        return true;
    }else{
        return false;
    }
};

/**
 * @brief 判断是否是'+''-''*''/''('')'
 * @param  c                My Param doc
 * @return true 
 * @return false 
 */
bool isOpall(char c)
{
    if(c=='+'||c=='-'||c=='*'||c=='/'||c=='.'||c=='('||c==')'){
        return true;
    }else{
        return false;
    }
};

/**
 * @brief 判断输入的字符串是否能组成合法的中缀表达式
 * @param  s                My Param doc
 * @return true 
 * @return false 
 */
bool isValid(const std::string& s){
    bool flag=false;        /**用于判断小数点是否重复*/
    bool flagNum=false;     /**用于判断是否已经出现过数字*/
    bool flagOp=false;      /**用于判断是否连续出现运算符*/
    bool flagPoint;     
    std::stack<char> myStack;   /**用于判断括号使用是否合理*/
    for(int i=0;i<s.size();i++){
        if(isDigit(s[i])){
            /**
             * if(flagNum){···}语句块的作用：
             * 当已经出现过数字时，再次出现的数字与上一数字间若有空格，且两者之间无运算符，则不符合合法的中缀表达式
             * 如"1 2""1.s 4""1( 4)"均不合法
             */
            if(flagNum){
                bool Blank=false;  
                bool Operator=false;
                int t=i-1;
                while(!isDigit(s[t])){
                    if(isOp(s[t])){
                        Operator=true;      /**两数间存在运算符*/
                    }else if(s[t]==' '){
                        Blank=true;     /**两数间存在空格*/
                    }
                    t--;
                }
                if(Operator==false&&Blank==true){
                    return false;
                }
            }
            flagNum=true;   /**true表示该表达式已出现过数字*/
            flagOp=false;   /**除括号外，运算符之间需要用数字隔开，数字出现则运算符的连续性变为false*/
        }

        /**
         * 用于判断是否发生'+''-''*''/'是否连续出现或出现在开头、结尾的情况
         * 如"1+*2"，则return false
         */
        if(isOp(s[i])){
            if(!flagNum){
                return false;   /**出现在数字出现前，不合法*/
            }
            flag=false;
            if(i<s.size()){     
                if(flagOp==true){
                    return false;   /**连续出现*/
                }
            }
            flagOp=true;
            int t=i+1;
            bool Digit=false;
            while(!Digit&&t<s.size()){  
                if(isDigit(s[t])){
                    Digit=true;
                }
                t++;
            }
            if(!Digit){
                return false;       /**出现在结尾，即在字符串结束之前都没有出现数字*/
            }
        }

        /**
         * 用于判断小数点是否出现在开头/后面没有跟数字/在同一数字中出现两次/出现在结尾的情况
         * 如" .1+2""1. 2""1.2.2""12.  "均不合法
         */
        if(s[i]=='.'){
            flagPoint=false;
            if(!flagNum){   
                return false;   /**出现在开头*/
            }
            if(i==s.size()-1){
                return false;
            }else if(isOp(s[i+1])||s[i+1]==' '||s[i+1]=='('||s[i+1]==')'){
                return false;   /**后面没有跟数字*/
            }
            if(flag==true){
                return false;   /**连续出现*/
            }
            int t=i+1;
            if(!isDigit(s[t])){
                while(!isOp(s[t])&&t<s.size()){
                if(isDigit(s[t])){
                    flagPoint=true;
                }
                t++;
                }
                if(!flagPoint){
                    return false;      /**出现在结尾*/
                }
            }
            flag=true;
        }

        /**
         * 用于判断括号是否配对
         * 如"1((+2)"不合法
         */
        if(s[i]=='('){
            flag=false;
            myStack.push(s[i]);     /**'('压入栈*/
        }else if(s[i]==')'){
            if(flagOp==true){
                return false;   /**')'出现在数字前，不合法*/
            }
            flag=false;
            if(myStack.empty()){
                return false;   /**')'没有配对的'('，不合法*/
            }
            myStack.pop();
        }
    }
    return myStack.empty();
};

/**
 * @brief 将代表数字的char字符转化为double类型的数字，用于后续计算
 * @param  a                My Param doc
 * @return double 
 */
double CharToDouble(char a){
    if(a<='9'&&a>='0'){
        return static_cast<double>(a-'0');
    }else{
        std::cerr<<"Not a number!"<<std::endl;
        exit(-1);
    }
};

/**
 * @brief 计算10的负i次幂
 * @param  i                My Param doc
 * @return double 
 */
double ten_neg_exponent(int i){
    double ans=1;
    if(i<=0){
        std::cerr<<"Invalid exponent!"<<std::endl;
    }
    for(int j=0;j<i;j++){
        ans=ans*10;
    }
    ans=1/ans;
    return ans;
};

int main(){
    std::queue<ele> mid_exp;        /**用于储存合理的中缀表达式的队列，数据类型是struct ele*/
    std::queue<ele> exp;        /**用于储存转换后的后缀表达式*/
    std::stack<ele> op;         /**用于在中缀表达式转化为后缀表达式的过程中短暂储存运算符*/
    std::stack<double> number;      /**用于储存后缀表达式运行中的数字结果*/
    int i,j,step;       /**step用于记录小数点后的数字位于第几位*/
    ele p,q;    
    char c;
    double x;
    bool zerodeno=false;
    std::ifstream file("input.txt");    /**打开测试数据input.txt*/
    if (file.is_open()) {  
        std::string line;  
        while (std::getline(file, line)) {      /**按行读取字符串*/
            if(isValid(line)){      
                /**当检验到字符串是合法时，筛选有效自符转换为计算的中缀表达式*/
                for(i=0;i<line.size();i++){
                    c=line[i];
                    if(isDigit(c)){     /**若检验到的字符是数字，计算数字的大小*/
                        step=0;
                        p.num=CharToDouble(c); 
                        p.symbol='$';       /**将数字存储到结构ele中，添加识别符'$'*/
                        j=i+1;
                        while(!isOpall(line[j])&&j<line.size()){
                            if(isDigit(line[j])){
                                p.num=p.num*10+CharToDouble(line[j]);
                            }
                            j++;
                        }
                        if(line[j]=='.'){
                            j++;
                            while(!isOpall(line[j])&&j<line.size()){
                                    if(isDigit(line[j])){
                                        step++;
                                        x=CharToDouble(line[j]);
                                        p.num=p.num+x*ten_neg_exponent(step); 
                                    }
                                j++;
                            }
                        }
                        i=j-1;
                        mid_exp.push(p);    /**压入中缀表达式的栈*/
                    }else if(isOp(c)||c=='('||c==')'){
                        p.num=0;
                        p.symbol=c;
                        mid_exp.push(p);    /**若为运算符'+''-''*''/''('')'，直接压入栈*/
                    }
                }

                /**将中缀表达式转化为后缀表达式*/
                while(!mid_exp.empty()){
                    q=mid_exp.front();
                    if(q.symbol=='$'){
                        exp.push(q);    /**若检验到的是数字，直接推入存储后缀表达式的队列exp*/
                    }
                    else if(q.symbol==')')      /**若检验到')'，把'('前的存储在栈op中的运算符压入队列exp*/
                    {
                        while(!op.empty()&&op.top().symbol!='(')
                        {
                            exp.push(op.top());
                            op.pop();
                        }
                        op.pop();           /**推出'('*/
                    }
                    else if(q.symbol=='+'||q.symbol=='-')   /**若检验到'+''-'，将栈op中'('后的运算符压入队列exp*/
                    {
                        if(!op.empty())
                        {
                            while(!op.empty()&&op.top().symbol!='(')
                            {
                                exp.push(op.top());
                                op.pop();
                            }
                        }
                        op.push(q);
                    }
                    else if(q.symbol=='*'||q.symbol=='/')   /**若检验到'*''/'，将此之前栈op中连续的'*''/'压入队列exp*/
                    {
                        if(!op.empty())
                        {
                            while(!op.empty()&&(op.top().symbol=='*'||op.top().symbol=='/'))
                            {
                                exp.push(op.top());
                                op.pop();
                            }
                        }
                        op.push(q);
                    }
                    else if(q.symbol=='(')      /**若检验到'('，直接压入栈op*/
                    {
                        op.push(q);
                    }
                    else
                    {
                        _err_exp();
                    }
                    mid_exp.pop();
                }
                if(!op.empty()){        /**将剩余的运算符直接压入栈*/
                    while(!op.empty()){
                            exp.push(op.top());
                            op.pop();
                        }
                    }
                /**计算后缀表达式*/
                while(!exp.empty()){
                    if(exp.front().symbol=='$'){
                        number.push(exp.front().num);
                    }else{
                        double y1=number.top();
                        number.pop();
                        double y2=number.top();
                        number.pop();
                        double y;
                        /**检验到运算符时，用该运算符连接前两个数字并计算*/
                        if(exp.front().symbol=='+'){
                            y=y2+y1;
                        }else if(exp.front().symbol=='-'){
                            y=y2-y1;
                        }else if(exp.front().symbol=='*'){
                            y=y2*y1;
                        }else if(exp.front().symbol=='/'){
                            
                            if(y1!=0){
                                y=y2/y1;
                            }else{
                                zerodeno=true;
                            }
                        }
                        number.push(y);
                    }
                    exp.pop();
                }
                double ans;
                bool validans=false;
                if(!number.empty()){
                    ans=number.top();
                    number.pop();
                    validans=true;      /**存在有效结果，排除了例如"abcd"等无有效表达式的结果*/
                }
                if(!number.empty()){
                    _err_exp();     /**事实上，前面的isValid()若排除所有错误情况，则已经避免了栈number不为空的情况。但为了弥补可能存在的漏洞，仍然给出此判别*/
                    while(!number.empty()){
                        number.pop();
                    }
                }else if(validans&&!zerodeno){
                    std::cout<<ans<<std::endl;
                }else if(!zerodeno){
                    _no_exp();
                }else{
                    _div_zero();
                    zerodeno=false;
                }
            }else{
                _err_exp();     /**输入的字符串无法组成合法的中缀表达式*/
            }
        }
        file.close(); 
    } else {  
        _err_file();        /**无法打开input.txt文件*/
    } 
    return 0; 
}