/**
 * @file BinaryTree.h
 * @brief A header file containing base class BinaryTree and its derived classes provided
 * @author Zhong Qi (3210103612@zju.edu.cn)
 * @date 2024-01-03
 */
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream> 
using namespace std;   

/**
 * @brief 基类 BinaryTree
 * 包含了二叉树算法中基础的二叉树节点结构体BinaryNode，查找最大/小值函数findMax/findMin，
 * 是否存在某节点值的判断函数contains，中序打印函数printTree，清空树函数makeEmpty，
 * 插入值函数insert，移除值函数remove，克隆节点函数clone。
 * 其中findMax/findMin以及contains，printTree，makeEmpty，insert，remove函数提供了public和private版本以实现具体功能
 */
template <typename Comparable>
class BinaryTree{
    public:
        /*构造函数*/
        BinaryTree():root{nullptr}{}
        BinaryTree( const BinaryTree & rhs ) : root{ nullptr }
        {
        root = clone( rhs.root );
        }
        BinaryTree( BinaryTree && rhs ) : root{ rhs.root }
        {
        rhs.root = nullptr;
        }

        /*析构函数*/
        virtual ~BinaryTree(){
            makeEmpty();
        }

        /*拷贝赋值运算符重载函数*/
        BinaryTree & operator=(const BinaryTree & rhs){
            BinaryTree copy = rhs;
            std::swap( *this, copy );
            return *this;
        }

        /*移动赋值运算符重载函数*/
        BinaryTree & operator=( BinaryTree && rhs )
        {
        std::swap( root, rhs.root );       
        return *this;
        }

        /*查找最小值（公有版本）*/
        /*提供公有、私有两个版本，因为让用户去提供内部结构root才能进行操作显然是不合理的*/
        /*返回const Comparable，表示返回的是常引用，防止修改返回的元素*/
        /*findMin没有在像BinarySearchTree.h、AvlTree.h、RedBlackTree.h中一样声明为常量成员函数，*/
        /*主要是考虑SplayTree.h中findMin有修改类成员变量，为了兼容性去掉了这里的const*/
        /*但isEmpty和私有版本的findMin仍然声明为const函数，所以共有版本中即使不声明为const函数，类成员变量被修改的风险也很低*/
        /*下面的findMax、contains也做了去掉const的处理*/
        /*virtual用于声明虚函数，支持多态，派生类可以选择重写基类中的虚函数*/
        virtual const Comparable & findMin( )
        {
        if( isEmpty( ) )
            throw UnderflowException{ };/*异常处理*/
        return findMin( root )->element;
        }

        /*查找最大值（公有版本）*/
        virtual const Comparable & findMax( )
        {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
        }

        /*判断是否包含某值x的函数（公有版本）*/
        virtual bool contains( const Comparable & x )
        {
        return contains( x, root );
        }

        /*判断该二叉树是否为空（公有版本）*/
        virtual bool isEmpty( ) const
        {
            // cerr << root << "root\n";
        return root == nullptr;
        }

        /*以中序打印二叉树（公有版本）*/
        virtual void printTree( ostream & out = cout ) const
        {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root, out );
        }

        /*清空树*/
        virtual void makeEmpty( )
        {
        makeEmpty( root );
        }

        /*插入函数，适用于左值引用（公有版本）*/
        virtual void insert( const Comparable & x )
        {
        insert( x, root );
        }
        /*插入函数，适用于右值引用（公有版本）*/
        virtual void insert( Comparable && x )
        {
        insert( std::move( x ), root );
        }

        /*移除二叉树中某值的函数（公有版本）*/
        virtual void remove( const Comparable & x )
        {
        remove( x, root );
        }

    /*用protected而非private，便于将下列函数继承给派生类*/
    /*用户不可见*/
    protected:
        /*二叉树基本节点结构体，包含节点值，左节点和右节点*/
        struct BinaryNode{
            Comparable element;
            BinaryNode *left;
            BinaryNode *right;

            BinaryNode( ) : left{ nullptr }, right{ nullptr } { }

            BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
            : element{ theElement }, left{ lt }, right{ rt } { }
        
            BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
            : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
        };

        /*二叉树根节点*/
        BinaryNode *root;

        /*插入函数（受保护版本）*/
        /*私有版本可以利用二叉树的结构进行递归插入*/
        /*同样声明virtual，可以在继承类中进行覆写*/
        virtual void insert( const Comparable & x, BinaryNode * & t )
        {
        if( t == nullptr )
            t = new BinaryNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
            ;  // Duplicate; do nothing
        }
        virtual void insert( Comparable && x, BinaryNode * & t )
        {
        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else
            ;  // Duplicate; do nothing
        }

        /*移除二叉树中某值的函数（受保护版本）*/
        virtual void remove( const Comparable & x, BinaryNode * & t )
        {
        if( t == nullptr )
            return;   // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }
        }

        /*查找最小值（受保护版本）*/
        BinaryNode * findMin( BinaryNode *t ) const
        {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
        }

        /*查找最大值（受保护版本）*/
        BinaryNode * findMax( BinaryNode *t ) const
        {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
        }

        /*判断是否包含某值x的函数（受保护版本）*/
        bool contains( const Comparable & x, BinaryNode *t ) const
        {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
        }

        /*清空二叉树（受保护版本）*/
        virtual void makeEmpty( BinaryNode * & t )
        {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
        }

        /*中序打印二叉树（受保护版本）*/
        virtual void printTree( BinaryNode *t, ostream & out ) const
        {
        if( t != nullptr )
        {
            printTree( t->left, out );
            out << t->element << endl;
            printTree( t->right, out );
        }
        }

        /*克隆节点（受保护版本）*/
        virtual BinaryNode * clone( BinaryNode *t ) const
        {
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
        }
};


/**
 * @brief 派生类 BinarySearchTree
 * 作为二叉树最基本的应用，所以其功能已全部在基类BinarTree中实现
 * 不声明函数时会自动继承BinaryTree中功能，包括构造函数和析构函数等
 */
template <typename Comparable>
class BinarySearchTree:public BinaryTree<Comparable>{
};


/**
 * @brief 派生类AvlTree
 * 实现Avl树，主要是在二叉树的基础上增加了blance操作，用以保证二叉树的相对平衡
 */
template <typename Comparable>
class AvlTree:public BinaryTree<Comparable>{
    public:
    
    /*由于这些函数同名的私有版本在private中有覆写，因此公有版本也不能直接继承*/
    /*所以引入BinaryTree基类中的这些函数到派生类中*/
    using BinaryTree<Comparable>::insert;
    using BinaryTree<Comparable>::remove;

    private:
    /*继承BinaryTree中的结构体BinaryNode，再加上AvlTree中用于判断节点平衡的height*/
    using typename BinaryTree<Comparable>::BinaryNode; 
        struct AvlNode:public BinaryNode{
            int height;
            AvlNode( const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0 )
            : BinaryNode(ele, lt, rt), height{ h } { }
        
            AvlNode( Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0 )
            : BinaryNode(std::move(ele), lt, rt), height{ h } { }
        };

        AvlNode *root;
        
        /*不是基类中insert的覆写，因为参数t不同，但应用时会覆盖基类的insert(x,t)*/
        /*因为这个是内部调用*/
        void insert( const Comparable & x, AvlNode * & t )
        {   
            /*但可以继承BinaryTree中的insert(const Comparable & x, BinaryNode * & t)，避免重复内容的复制粘贴*/
            /*这是可行的因为AvlNode是BinaryNode的子结构体*/
            BinaryTree<Comparable>::insert(x, t);
            balance(t);
        }

        void insert( Comparable && x, AvlNode * & t )
        {
            BinaryTree<Comparable>::insert(std::move(x), t);
            balance(t);
        }

        void remove( const Comparable & x, AvlNode * & t )
        {
            BinaryTree<Comparable>::remove(x,t);
            balance(t);
        }
        
        /*每一节点左子树和右子树高度差允许值*/
        static const int ALLOWED_IMBALANCE = 1;
        /*平衡函数，AvlTree的精髓*/
        void balance( AvlNode * & t )
        {
        if( t == nullptr )
            return;
        
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE ){
            if( height( t->left->left ) >= height( t->left->right ) )
                rotateWithLeftChild( t );/*旋转左子树，即右旋*/
            else
                doubleWithLeftChild( t );/*先左旋再右旋*/
        }else if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE ){
            if( height( t->right->right ) >= height( t->right->left ) )
                rotateWithRightChild( t );/*旋转右子树，即左旋*/
            else
                doubleWithRightChild( t );/*先右旋再左旋*/
        }
        t->height = max( height( t->left ), height( t->right ) ) + 1;
        }

        /*克隆函数*/
        AvlNode * clone( AvlNode *t ) const
        {
        if( t == nullptr )
            return nullptr;
        else
            return new AvlNode{ t->element, clone( t->left ), clone( t->right ), t->height };
        }

        /*高度函数，空节点高度为-1，叶子节点高度为0*/
        int height( AvlNode *t ) const
        {
            return t == nullptr ? -1 : t->height;
        }

        /*得出最大值函数*/
        int max( int lhs, int rhs ) const
        {
            return lhs > rhs ? lhs : rhs;
        }

        /*旋转左子树，即把左子树右旋*/
        void rotateWithLeftChild( AvlNode * & k2 )
        {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
        }

        /*与上相反*/
        void rotateWithRightChild( AvlNode * & k1 )
        {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
        }

        void doubleWithLeftChild( AvlNode * & k3 )
        {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
        }

        void doubleWithRightChild( AvlNode * & k1 )
        {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
        }
};

/**
 * @brief 派生类SplayTree
 * 实现Splay树，主要是每次访问数据后进行Splay操作将访问的数据移动到根节点
 * 这样做可以在每次访问时提早平衡二叉树，且判断条件较AvlTree和RedBlackTree弱，操作简单
 */
template <typename Comparable>
class SplayTree:public BinaryTree<Comparable>{
    public:
        /*构造函数，SplayTree和之后的RedBlackTree引入了nullNode这一特殊节点*/
        SplayTree( )
        {
        nullNode = new BinaryNode;
        nullNode->left = nullNode->right = nullNode;
        root = nullNode;
        }

        SplayTree( const SplayTree & rhs )
        {
        nullNode = new BinaryNode;
        nullNode->left = nullNode->right = nullNode;
        root = clone( rhs.root );
        }

        SplayTree( SplayTree && rhs ) : root{ rhs.root }, nullNode{ rhs.nullNode }
        {
        rhs.root = nullptr;
        rhs.nullNode = nullptr;
        }

        ~SplayTree( )
        {
        makeEmpty( );
        delete nullNode;
        }

        SplayTree & operator=( const SplayTree & rhs )
        {
        SplayTree copy = rhs;
        std::swap( *this, copy );
        return *this;
        }

        SplayTree & operator=( SplayTree && rhs )
        {
        std::swap( root, rhs.root );
        std::swap( nullNode, rhs.nullNode );
        return *this;
        }

        /*findMin函数，直接在public版本中实现代码*/
        /*override表示覆写了基类的findMin*/
        const Comparable & findMin( )override
        {
        if( isEmpty( ) )
            throw UnderflowException{ };

        BinaryNode *ptr = root;

        while( ptr->left != nullNode )
            ptr = ptr->left;

        splay( ptr->element, root );/*多了一步splay操作，每次找到最小值后都将其作为根节点*/
        return ptr->element;
        }
        
        const Comparable & findMax( )override
        {
        if( isEmpty( ) )
            throw UnderflowException{ };

        BinaryNode *ptr = root;

        while( ptr->right != nullNode )
            ptr = ptr->right;

        splay( ptr->element, root );
        return ptr->element;
        }

        bool contains( const Comparable & x )override
        {
        if( isEmpty( ) )
            return false;
        splay( x, root );/*也使用了splay操作*/
        return root->element == x;
        }

        bool isEmpty( ) const override
        {
        return root == nullNode;
        }

        void printTree(ostream & out = cout) const override
        {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root,out);
        }

        /*这个清空树的函数很好地体现了SplayTree的特点*/
        /*由于基类BinaryTree的递归版本在退化树中的效率较低，这里采用了依次找到最大值然后删除的方法并覆写了makeEmpty函数*/
        /*好在每次寻找最大值时会将其移动到根节点，改变树的结构，使二叉树趋于平衡*/
        void makeEmpty( )override
        {
        while( !isEmpty( ) )
        {
            findMax( );        
            remove( root->element );
        }
        }

        /*首先将二叉树伸展到以比x大的最小值或比x小的最大值为根的节点为根节点的二叉树结构*/
        /*再将左树右树分别接到newNode两侧(包括root)*/
        void insert( const Comparable & x )override
        {
        static BinaryNode *newNode = nullptr;

        if( newNode == nullptr )
            newNode = new BinaryNode;
        newNode->element = x;

        if( root == nullNode )
        {
            newNode->left = newNode->right = nullNode;
            root = newNode;
        }
        else
        {
            splay( x, root );
            if( x < root->element )
            {
                newNode->left = root->left;
                newNode->right = root;
                root->left = nullNode;
                root = newNode;
            }
            else
            if( root->element < x )
            {
                newNode->right = root->right;
                newNode->left = root;
                root->right = nullNode;
                root = newNode;
            }
            else
                return;
        }
        newNode = nullptr;   // So next insert will call new
        }

        /*原代码未提供SplayTree插入右值引用的情况*/
        void insert(Comparable && x )override
        {
        cout<<"Warning:There Is No Rvalue Reference Version For SplayTree!"<<endl;
        exit(-1);
        }

        /*remove，通过伸展操作进行一系列查找访问与变动操作*/
        void remove( const Comparable & x )override
        {
            /*contains函数会调用splay操作把值为x的节点移动到root处*/
        if( !contains( x ) )
            return;   // Item not found; do nothing

        BinaryNode *newTree;

        if( root->left == nullNode )
            newTree = root->right;
        else
        {
            /*将左子树的最大值替代根节点*/
            newTree = root->left;
            splay( x, newTree );
            newTree->right = root->right;
        }
        delete root;
        root = newTree;
        }

    private:
        /*结构体SplayNode和BinaryNode一致*/
        using typename BinaryTree<Comparable>::BinaryNode; 
        BinaryNode *root;
        BinaryNode *nullNode;

        /*递归形式的清空，实际上没有被使用，原因在上述SplayTree::makeEmpty注释中已解释*/
        void reclaimMemory( BinaryNode * t )
        {
        /*加入nullNode后的判断条件由t!=nullptr变成了t!=t->left*/
        if( t != t->left )
        {
            reclaimMemory( t->left );
            reclaimMemory( t->right );
            delete t;
        }
        }

        /*中序打印，覆写原因为判断条件的改变*/
        void printTree( BinaryNode *t,ostream & out ) const override
        {
        if( t != t->left )
        {
            printTree( t->left ,out);
            cout << t->element << endl;
            printTree( t->right,out);
        }
        }

        /*克隆函数，覆写原因同上*/
        BinaryNode * clone( BinaryNode * t ) const override
        {
        if( t == t->left )
            return nullNode;
        else
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
        }

        /*旋转左子节点*/
        void rotateWithLeftChild( BinaryNode * & k2 )
        {
        BinaryNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2 = k1;
        }

        /*旋转右子节点*/
        void rotateWithRightChild( BinaryNode * & k1 )
        {
        BinaryNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1 = k2;
        }

        /*伸展函数，SplayTree提高效率的核心*/
        void splay( const Comparable & x, BinaryNode * & t )
        {
        BinaryNode *leftTreeMax, *rightTreeMin;
        static BinaryNode header;

        header.left = header.right = nullNode;
        leftTreeMax = rightTreeMin = &header;

        nullNode->element = x;   // Guarantee a match

        for( ; ; )
            if( x < t->element )
            {
                if( x < t->left->element )
                    rotateWithLeftChild( t );
                if( t->left == nullNode )
                    break;
                // Link Right
                rightTreeMin->left = t;
                rightTreeMin = t;
                t = t->left;
            }
            else if( t->element < x )
            {
                if( t->right->element < x )
                    rotateWithRightChild( t );
                if( t->right == nullNode )
                    break;
                // Link Left
                leftTreeMax->right = t;
                leftTreeMax = t;
                t = t->right;
            }
            else
                break;

        leftTreeMax->right = t->left;
        rightTreeMin->left = t->right;
        t->left = header.right;
        t->right = header.left;
        }
};

/**
 * @brief 派生类RedBlackTree
 * 主要是在节点结构体中加入了color这一变量，减少了旋转的可能性，较AvlTree的height更为有效
 */
template <typename Comparable>
class RedBlackTree:public BinaryTree<Comparable>{
    public:
    /*构造函数，增加了header这一哨兵节点*/
    explicit RedBlackTree( const Comparable & negInf )
    {
        nullNode    = new RedBlackNode;
        nullNode->left = nullNode->right = nullNode;
        
        header      = new RedBlackNode{ negInf };
        header->left = header->right = nullNode;
    }

    RedBlackTree( const RedBlackTree & rhs )
    {
        nullNode    = new RedBlackNode;
        nullNode->left = nullNode->right = nullNode;
        
        header      = new RedBlackNode{ rhs.header->element };
        header->left = nullNode;
        header->right = clone( rhs.header->right );
    }

    RedBlackTree( RedBlackTree && rhs )
    : nullNode{ rhs.nullNode }, header{ rhs.header }
    {
        rhs.nullNode = nullptr;
        rhs.header = nullptr;
    }

    ~RedBlackTree( )
    {
        makeEmpty( );
        delete nullNode;
        delete header;
    }

    RedBlackTree & operator=( const RedBlackTree & rhs )
    {
        RedBlackTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }

    RedBlackTree & operator=( RedBlackTree && rhs )
    {
        std::swap( header, rhs.header );
        std::swap( nullNode, rhs.nullNode );
        
        return *this;
    }

    /*覆写了findMin，用循环方式找到最小值*/
    /*此处可以注意到header与root较为不同，事实上header->right类似于root*/
    const Comparable & findMin( ) override
    {
        if( isEmpty( ) )
            throw UnderflowException{ };

        RedBlackNode *itr = header->right;

        while( itr->left != nullNode )
            itr = itr->left;

        return itr->element;
    }

    const Comparable & findMax( )override
    {
        if( isEmpty( ) )
            throw UnderflowException{ };

        RedBlackNode *itr = header->right;

        while( itr->right != nullNode )
            itr = itr->right;

        return itr->element;
    }

    /*contains函数覆写，同样使用了循环方式*/
    bool contains( const Comparable & x )override
    {
        nullNode->element = x;
        RedBlackNode *curr = header->right;

        for( ; ; )
        {
            if( x < curr->element )
                curr = curr->left;
            else if( curr->element < x )
                curr = curr->right;
            else
                return curr != nullNode;
        }
    }

    /*想法与之前类似，主要区别在于加入了header这一特殊节点*/
    bool isEmpty( ) const override
    {
        return header->right == nullNode;
    }

    void printTree(ostream & out = cout) const override
    {
        if( header->right == nullNode )/*相当于isEmpty()，或许使用isEmpty更统一*/
            cout << "Empty tree" << endl;
        else
            printTree( header->right,out);
    }

    /*覆写makeEmpty，递归思路与之前相似*/
    void makeEmpty( )override
    {
        if( header == nullptr )
            return;
        
        reclaimMemory( header->right );
        header->right = nullNode;
    }
    
    /*红黑树特有的insert，用于调整其需要满足的三个条件，降低旋转的可能性*/
    void insert( const Comparable & x )override
    {
        current = parent = grand = header;
        nullNode->element = x;

        while( current->element != x )
        {
            great = grand; grand = parent; parent = current;
            current = x < current->element ?  current->left : current->right;

            if( current->left->color == RED && current->right->color == RED )
                handleReorient( x );/*由于插入节点为红色，此时违反红黑树规则，需要调整*/
        }


        if( current != nullNode )
            return;
        current = new RedBlackNode{ x, nullNode, nullNode };

        if( x < parent->element )
            parent->left = current;
        else
            parent->right = current;
        handleReorient( x );
    }

    /*原代码未提供RedBlackTree插入右值引用的情况*/
    void insert(Comparable && x )override
    {
        cout<<"Warning:There Is No Rvalue Reference Version For RedBlackTree!"<<endl;
        exit(-1);
    }

    /*原代码未提供，仅做覆写防止错误调用*/
    void remove( const Comparable & x )override
    {
        cout << "Sorry, remove unimplemented; " << x <<
                " still present" << endl;
    }

    private:
    /*红黑树结构体，加入了color这一限制变量*/
        enum { RED, BLACK };
        struct RedBlackNode
        {
        Comparable    element;
        RedBlackNode *left;
        RedBlackNode *right;
        int           color;

        RedBlackNode( const Comparable & theElement = Comparable{ },
                            RedBlackNode *lt = nullptr, RedBlackNode *rt = nullptr,
                            int c = BLACK )
            : element{ theElement }, left{ lt }, right{ rt }, color{ c } { }
        
        RedBlackNode( Comparable && theElement, RedBlackNode *lt = nullptr,
                      RedBlackNode *rt = nullptr, int c = BLACK )
            : element{ std::move( theElement ) }, left{ lt }, right{ rt }, color{ c } { }
        };
        /*
        using typename BinaryTree<Comparable>::BinaryNode; 
        struct RedBlackNode:public BinaryNode{
            int color;
            RedBlackNode( const Comparable & theElement = Comparable{ },
                            RedBlackNode *lt = nullptr, RedBlackNode *rt = nullptr,
                            int c = BLACK )
            : BinaryNode(theElement, lt, rt), color{ c } { }
        
            RedBlackNode( Comparable && theElement, RedBlackNode *lt = nullptr,
                      RedBlackNode *rt = nullptr, int c = BLACK )
            : BinaryNode(std::move(theElement), lt, rt), color{c}  { }
        };
        */

        RedBlackNode *header;   
        RedBlackNode *nullNode;

        /*由于红黑树的调整需要与父辈及以上节点产生联系，所以加入了parent、grand、great节点，起到追踪和辅助处理的作用*/
        RedBlackNode *current;
        RedBlackNode *parent;
        RedBlackNode *grand;
        RedBlackNode *great;

        void reclaimMemory( RedBlackNode *t )
        {
        if( t != t->left )
        {
            reclaimMemory( t->left );
            reclaimMemory( t->right );
            delete t;
        }
        }

        void printTree( RedBlackNode *t, ostream & out ) const
        {
        if( t != t->left )
        {
            printTree( t->left, out );
            out << t->element << endl;
            printTree( t->right, out );
        }
        }

        RedBlackNode * clone( RedBlackNode * t ) const
        {
        if( t == t->left )  
            return nullNode;
        else
            return new RedBlackNode{ t->element, clone( t->left ),
                                    clone( t->right ), t->color };
        }

        /*红黑树insert操作中的调整处理*/
        void handleReorient( const Comparable & item )
        {

        current->color = RED;
        current->left->color = BLACK;
        current->right->color = BLACK;

        if( parent->color == RED )/*红节点的父辈不能是红节点*/
        {
            grand->color = RED;
            if( item < grand->element != item < parent->element )
                parent = rotate( item, grand );  
            current = rotate( item, great );
            current->color = BLACK;
        }
        header->right->color = BLACK; /*根节点始终保持黑色*/
        }

        RedBlackNode * rotate( const Comparable & item, RedBlackNode *theParent )
        {
        if( item < theParent->element )
        {
            item < theParent->left->element ?
                rotateWithLeftChild( theParent->left )  :  // LL
                rotateWithRightChild( theParent->left ) ;  // LR
            return theParent->left;
        }
        else
        {
            item < theParent->right->element ?
                rotateWithLeftChild( theParent->right ) :  // RL
                rotateWithRightChild( theParent->right );  // RR
            return theParent->right;
        }
        }

        void rotateWithLeftChild( RedBlackNode * & k2 )
        {
        RedBlackNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2 = k1;
        }

        void rotateWithRightChild( RedBlackNode * & k1 )
        {
        RedBlackNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1 = k2;
        }
};

#endif
