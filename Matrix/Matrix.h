/**
 * @file Matrix.h
 * @brief 一个矩阵类
 * 该文件包含了一个用于表示和操作由某种类型元素组成的矩阵的类。
 * 
 * @author 钟琦 (3210103612@zju.edu.cn)
 * @version 3.0
 * @date 2023-10-14
 */

#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;


#ifndef MATRIX_H
#define MATRIX_H

/**
 * @class Matrix
 * @brief 定义了一个模板类，抽象了数据类型ELE_T
 * 用户使用时只需Matrix<实际类型>即可根据需要指定 ELE_T 的实际类型
 * @tparam ELE_T 
 */

template <typename ELE_T>
class Matrix{
    private:
    int rows;   /**矩阵的行数*/
    int cols;   /**矩阵的列数*/
    ELE_T** elements=nullptr; /**矩阵中的元素，由二维数组指针存储*/

    public:
    /**
     * @brief 打印矩阵
     */
    void printMatrix()const;

    /**
     * @brief 清空矩阵
     */
    void makeEmpty();

    /**
     * @brief 找到矩阵中值为val的元素地址
     * 静态函数版本
     * @param  val              My Param doc
     * @return const ELE_T** 
     */
    const ELE_T** find(const ELE_T &val)const;

    /**
     * @brief 找到矩阵中值为val的元素地址
     * 动态函数版本
     * @param  val              My Param doc
     * @return ELE_T** 
     */
    ELE_T** find(const ELE_T &val);

    /**
     * @brief 找到矩阵中值为val的元素所在行
     * @param  val              My Param doc
     * @return int 
     */
    int findRow(const ELE_T &val)const;

    /**
     * @brief 找到矩阵中值为val的元素所在列
     * @param  val              My Param doc
     * @return int 
     */
    int findCol(const ELE_T &val)const;

    /**
     * @brief 得到矩阵第row行第col列的元素
     * 静态版本
     * @param  row              My Param doc
     * @param  col              My Param doc
     * @return const ELE_T** 
     */
    const ELE_T** getElement(int row,int col)const;

    /**
     * @brief 得到矩阵第row行第col列的元素
     * 动态版本
     * @param  row              My Param doc
     * @param  col              My Param doc
     * @return const ELE_T** 
     */
    ELE_T** getElement(int row,int col);

    /**
     * @brief 得到矩阵的迹
     * @return ELE_T 
     */
    ELE_T getTrace()const;

    /**
     * @brief 得到矩阵的行列式
     * @return ELE_T 
     */
    ELE_T getDeterminant()const;

    /**
     * @brief 设置矩阵第row行第col列的元素为element
     * @param  row              My Param doc
     * @param  col              My Param doc
     * @param  element          My Param doc
     */
    void setElement(int row,int col,const ELE_T &element);

    /**
     * @brief 在矩阵第row行后添加n行
     * @param  row              My Param doc
     * @param  n                My Param doc
     */
    void insertRow(int row,int n);

    /**
     * @brief 在矩阵第col列后添加n列
     * @param  col              My Param doc
     * @param  n                My Param doc
     */
    void insertCol(int col,int n);

    /**
     * @brief 移去第row行
     * @param  row              My Param doc
     */
    void removeRow(int row);

    /**
     * @brief 移去第col列
     * @param  col              My Param doc
     */
    void removeCol(int col);

    /**
     * @brief 第row1行减去第row2行
     * 减后结果位于第row1行
     * @param  row1             My Param doc
     * @param  row2             My Param doc
     */
    void minusRow(int row1,int row2);

    /**
     * @brief 第col1列减去第col2列
     * 减后结果位于第col1列
     * @param  col1             My Param doc
     * @param  col2             My Param doc
     */
    void minusCol(int col1,int col2);

    /**
     * @brief 第row1行与第row2行相加
     * 加后结果位于第row1行
     * @param  row1             My Param doc
     * @param  row2             My Param doc
     */
    void plusRow(int row1,int row2);

    /**
     * @brief 第col1列与第col2列相加
     * 加后结果位于第col1列
     * @param  col1             My Param doc
     * @param  col2             My Param doc
     */
    void plusCol(int col1,int col2);

    /**
     * @brief 矩阵加法运算
     * 原矩阵加上一个other矩阵
     * @param  other            My Param doc
     * @return Matrix 
     */
    Matrix addMatrix(const Matrix& other)const;

    /**
     * @brief 矩阵数乘运算
     * 原矩阵乘以一个数字num
     * @param  num              My Param doc
     * @return Matrix 
     */
    Matrix multiplyByNum(double num)const;

    /**
     * @brief 矩阵乘法运算
     * 原矩阵乘以一个矩阵other
     * @param  other            My Param doc
     * @return Matrix 
     */
    Matrix multiplyByMatrix(const Matrix& other)const;

    /**
     * @brief 矩阵乘以向量
     * @param  vector           My Param doc
     * @return vector<ELE_T> 
     */
    vector<ELE_T> mutiplyByVector(const vector<ELE_T>& vector)const;

    /**
     * @brief 矩阵求逆
     * @return Matrix 
     */
    Matrix inverse()const;

    /**
     * @brief 随机初始化矩阵元素值 
     */
    void randomize();

    /**
     * @brief 构造函数
     * 创建一个空的矩阵对象
     */
    Matrix();

    /**
     * @brief 构造函数
     * 创建一个row行col列的空的矩阵对象
     * @param  row              My Param doc
     * @param  col              My Param doc
     */
    Matrix(int row,int col);

    /**
     * @brief 析构函数
     * 释放矩阵对象占用的内存
     */
    ~Matrix();

    /**
     * @brief 复制构造函数
     * @param  rhs              My Param doc
     */
    Matrix(const Matrix &rhs);

    /**
     * @brief 赋值运算的重载
     * @param  rhs              My Param doc
     * @return Matrix& 
     */
    Matrix &operator=(const Matrix &rhs);

    /**
     * @brief 加法运算的重载
     * @param  rhs              My Param doc
     * @return Matrix& 
     */
    Matrix &operator+(const Matrix &rhs);

    /**
     * @brief 减法运算的重载
     * @param  rhs              My Param doc
     * @return Matrix& 
     */
    Matrix &operator-(const Matrix &rhs);

    /**
     * @brief 移动赋值
     * @param  other            My Param doc
     * @return Matrix& 
     */
    Matrix& operator=(Matrix&& other)noexcept;

    /**
     * @brief 移送构造
     * @param  other            My Param doc
     */
    Matrix(Matrix&& other)noexcept;
};


template <typename ELE_T>
void Matrix<ELE_T>::printMatrix()const{
    /**如果矩阵为空，则输出The Matrix is empty.*/
    if(rows==0){
        std::cout << "The Matrix is empty." << std::endl;
        return;
    }
    for (int i = 0; i < rows; i++){
        for(int j=0;j<cols;j++){
            cout<<elements[i][j]<<" ";
        }
            cout<<"\n";
    }
    cout << endl;
    return;
}

template <typename ELE_T>
Matrix<ELE_T>::Matrix(int row,int col){
    this->rows=row;
    this->cols=col;
    elements=new ELE_T*[row];
    for(int i=0;i<row;i++){
        elements[i]=new ELE_T[col];
    }
}

template <typename ELE_T>
Matrix<ELE_T>::~Matrix(){
    for(int i=0;i<rows;i++){
        delete[] elements[i];
    }
    delete elements;
}

template <typename ELE_T>
void Matrix<ELE_T>::setElement(int row,int col,const ELE_T &element){
        if (row < 0 || row >= rows || col < 0 || col >= cols) {  
            cout << "Invalid index." << endl;  
            return;  
        }  
        elements[row][col] = element;
}


#endif
