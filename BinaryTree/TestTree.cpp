#include <iostream>
#include "BinaryTree.h"
using namespace std;

int main(){
    /*测试BinarySearchTree类*/
    BinarySearchTree<int> bst;
    /*TestBinarySearchTree.cpp文件中使用NUMS=400000，GAP=3711，两者互质，所以insert的数据足够多*/
    /*此处沿用这两个数据*/
    cout<<"Test class BinarySearchTree:no more output except printing BinarySearchTree means success"<<endl;
    int NUMS = 400000;
    const int GAP  =   3711;
    int i;
    /*以相对乱序插入1~399999这些数*/
    for( i = GAP; i != 0; i = ( i + GAP ) % NUMS ){
        bst.insert( i );
    }
    /*移去其中的奇数*/
    for( i = 1; i < NUMS; i+= 2 ){
        bst.remove( i );
    }

    /*移去奇数后最小数和最大数应为2和NUMS-2(因为NUMS是偶数)*/
    if( bst.findMin( ) != 2 || bst.findMax( ) != NUMS - 2 ){
        cout << "FindMin or FindMax error!" << endl;
    }

    /*此时应包含2到NUMS-1中的每个偶数，不包含奇数*/
    for( i = 2; i < NUMS; i+=2 ){
        if( !bst.contains( i ) ){
            cout << "contains error1!" << endl;
        }
    }
    for( i = 1; i < NUMS; i+=2 )
    {
        if( bst.contains( i ) )
            cout << "contains error2!" << endl;
    }
    
    for(i=22;i<NUMS;i+=2){
        bst.remove(i);
    }
    cout<<"bst's print:"<<endl;
    bst.printTree();

    /*测试复制赋值运算符*/
    cout<<"bst1's print:"<<endl;
    BinarySearchTree<int> bst1;
    bst1=bst;
    bst1.printTree();

    /*测试拷贝构造函数*/
    BinarySearchTree<int> bst2(bst1);
    cout<<"bst2's print:"<<endl;
    bst2.printTree();
    
    /*测试移动构造函数*/
    BinarySearchTree<int> bst3(move(bst2));
    cout<<"bst3's print:"<<endl;
    bst3.printTree();

    /*测试移动赋值运算符*/
    BinarySearchTree<int> bst4;
    bst4=move(bst3);
    cout<<"bst4's print:"<<endl;
    bst4.printTree();

    /*测试makeEmpty()*/
    bst.makeEmpty();
    if(!bst.isEmpty()){
        cout<<"makeEmpty or is Empty error!"<<endl;
    }
    cout<<"bst's print after makeEmpty:"<<endl;
    /*测试右值插入*/
    bst.printTree();
    bst.insert(1);
    bst.insert(2);
    bst.insert(5);
    bst.insert(0);
    cout<<"bst's print after insert(RightValue Version):"<<endl;
    bst.printTree();
    
    
    /*测试AvlTree类*/
    AvlTree<int> At;
    /*AvlTree.cpp文件中使用NUMS=200000，GAP=37，两者互质，但GAP较小，意味着插入数据中有很大一部分是有序的*/
    /*这也就意味着如果不加以平衡处理，二叉树会比较深，而加以平衡处理后会改善效率*/
    /*此处沿用这两个数据*/
    cout<<"Test class AvlTree:no more output except printing AvlTree means success"<<endl;
    NUMS = 200000;
    const int AGAP  =   37;
    /*以相对乱序插入1~199999这些数*/
    for( i = AGAP; i != 0; i = ( i + AGAP ) % NUMS ){
        At.insert( i );
    }
    /*移去其中的奇数*/
    for( i = 1; i < NUMS; i+= 2 ){
        At.remove( i );
    }

    /*移去奇数后最小数和最大数应为2和NUMS-2(因为NUMS是偶数)*/
    if( At.findMin( ) != 2 || At.findMax( ) != NUMS - 2 ){
        cout << "FindMin or FindMax error!" << endl;
    }

    /*此时应包含2到NUMS-1中的每个偶数，不包含奇数*/
    for( i = 2; i < NUMS; i+=2 ){
        if( !At.contains( i ) ){
            cout << "contains error1!" << endl;
        }
    }
    for( i = 1; i < NUMS; i+=2 )
    {
        if( At.contains( i ) )
            cout << "contains error2!" << endl;
    }
    
    for(i=22;i<NUMS;i+=2){
        At.remove(i);
    }
    cout<<"At's print:"<<endl;
    At.printTree();
    

    /*测试复制赋值运算符*/
    cout<<"At1's print:"<<endl;
    AvlTree<int> At1;
    At1=At;
    At1.printTree();

    /*测试拷贝构造函数*/
    AvlTree<int> At2(At1);
    //cout << "Height of the root: " << At.height(At.root) << endl;
    cout<<"At2's print:"<<endl;
    At2.printTree();
    
    /*测试移动构造函数*/
    AvlTree<int> At3(move(At2));
    cout<<"At3's print:"<<endl;
    At3.printTree();

    /*测试移动赋值运算符*/
    AvlTree<int> At4;
    At4=move(At3);
    cout<<"At4's print:"<<endl;
    At4.printTree();

    /*测试makeEmpty()*/
    At.makeEmpty();
    if(!At.isEmpty()){
        cout<<"makeEmpty or is Empty error!"<<endl;
    }
    cout<<"At's print after makeEmpty:"<<endl;
    At.printTree();
    /*测试右值插入*/
    At.insert(1);
    At.insert(2);
    At.insert(5);
    At.insert(0);
    cout<<"At's print after insert(RightValue Version):"<<endl;
    At.printTree();




    /*测试SplayTree类*/
    SplayTree<int> St;
    /*AvlTree.cpp文件中使用NUMS=200000，GAP=37，两者互质，但GAP较小，意味着插入数据中有很大一部分是有序的*/
    /*此处沿用这两个数据*/
    cout<<"Test class SplayTree:no more output except printing SplayTree means success"<<endl;
    NUMS = 200000;
    const int SGAP  =   37;
    /*以相对乱序插入1~199999这些数*/
    for( i = SGAP; i != 0; i = ( i + SGAP ) % NUMS ){
        St.insert( i );
    }
    /*移去其中的奇数*/
    for( i = 1; i < NUMS; i+= 2 ){
        St.remove( i );
    }

    /*移去奇数后最小数和最大数应为2和NUMS-2(因为NUMS是偶数)*/
    if( St.findMin( ) != 2 || St.findMax( ) != NUMS - 2 ){
        cout << "FindMin or FindMax error!" << endl;
    }

    /*此时应包含2到NUMS-1中的每个偶数，不包含奇数*/
    for( i = 2; i < NUMS; i+=2 ){
        if( !St.contains( i ) ){
            cout << "contains error1!" << endl;
        }
    }
    for( i = 1; i < NUMS; i+=2 )
    {
        if( St.contains( i ) )
            cout << "contains error2!" << endl;
    }
    
    for(i=22;i<NUMS;i+=2){
        St.remove(i);
    }
    cout<<"St's print:"<<endl;
    St.printTree();

    /*测试复制赋值运算符*/
    cout<<"St1's print:"<<endl;
    SplayTree<int> St1;
    St1=St;
    St1.printTree();

    /*测试拷贝构造函数*/
    SplayTree<int> St2(St1);
    cout<<"St2's print:"<<endl;
    St2.printTree();
    
    /*测试移动构造函数*/
    SplayTree<int> St3(move(St2));
    cout<<"St3's print:"<<endl;
    St3.printTree();

    /*测试移动赋值运算符*/
    SplayTree<int> St4;
    St4=move(St3);
    cout<<"St4's print:"<<endl;
    St4.printTree();

    /*测试makeEmpty()*/
    if(St.isEmpty()){
        cout<<"St Error!"<<endl;
    }
    St.makeEmpty();
    if(!St.isEmpty()){
        cout<<"makeEmpty or is Empty error!"<<endl;
    }
    cout<<"St's print after makeEmpty:"<<endl;
    St.printTree();



    /*测试RedBlackTree类*/
    const int NEG_INF = -9999;
    RedBlackTree<int> rbt{ NEG_INF };
    /*AvlTree.cpp文件中使用NUMS=200000，GAP=37，两者互质，但GAP较小，意味着插入数据中有很大一部分是有序的*/
    /*此处沿用这两个数据*/
    cout<<"Test class RedBlackTree:no more output except printing RedBlackTree means success"<<endl;
    NUMS = 200000;
    const int RGAP  =   37;
    /*以相对乱序插入1~199999这些数*/
    for( i = RGAP; i != 0; i = ( i + RGAP ) % NUMS ){
        rbt.insert( i );
    }

    /*最小数和最大数应为1和NUMS-1*/
    if( rbt.findMin( ) != 1 || rbt.findMax( ) != NUMS - 1 ){
        cout << "FindMin or FindMax error!" << endl;
    }

    /*此时应包含2到NUMS-1中的每个偶数，不包含奇数*/
    for( i = 1; i < NUMS; ++i ){
        if( !rbt.contains( i ) ){
            cout << "contains error1!" << endl;
        }
    }
    if( rbt.contains( 0 ) )
        cout << "Oops!" << endl;

    
    /*测试复制赋值运算符*/
    cout<<"rbt1's print:"<<endl;
    RedBlackTree<int> rbt1{ NEG_INF };
    for( i = 1; i<=20 ; i++ ){
        rbt1.insert( i );
    }

    rbt1.printTree();

    /*测试拷贝构造函数*/
    RedBlackTree<int> rbt2(rbt1);
    cout<<"rbt2's print:"<<endl;
    rbt2.printTree();
    
    /*测试移动构造函数*/
    RedBlackTree<int> rbt3(move(rbt2));
    cout<<"rbt3's print:"<<endl;
    rbt3.printTree();

    /*测试移动赋值运算符*/
    RedBlackTree<int> rbt4{NEG_INF};
    rbt4=move(rbt3);
    cout<<"rbt4's print:"<<endl;
    rbt4.printTree();

    /*测试makeEmpty()*/
    if(rbt.isEmpty()){
        cout<<"rbt Error!"<<endl;
    }
    rbt.makeEmpty();
    if(!rbt.isEmpty()){
        cout<<"makeEmpty or is Empty error!"<<endl;
    }
    cout<<"rbt's print after makeEmpty:"<<endl;
    rbt.printTree();
}
