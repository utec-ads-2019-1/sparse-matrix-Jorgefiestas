#ifndef SPARSE_MATRIX_NODE_H
#define SPARSE_MATRIX_NODE_H

template <typename T>
class Matrix;

template <typename T>
class Node {
protected:
    Node<T> *next = nullptr;
    Node<T> *down = nullptr;
    unsigned rpos = 0;
    unsigned cpos = 0;
    T data;

public:
    explicit Node() = default;

    Node(unsigned rpos, unsigned cpos, T data){
        this->rpos = rpos;
        this->cpos = cpos;
        this->data = data;
    };

    void killSelf(){
        if(next)
            next->killSelf();
        delete this;
    }

    ~Node(){};

    friend class Matrix<T>;
};

#endif //SPARSE_MATRIX_NODE_H
