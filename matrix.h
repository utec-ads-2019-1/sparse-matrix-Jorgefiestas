#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include <stdexcept>
#include <iostream>

#include "node.h"

using namespace std;

template <typename T>
class Matrix {
private:
    typedef Node<T> node;

    node *root;
    unsigned rows, columns;

    void check(unsigned, unsigned) const;

public:

    Matrix(unsigned rows, unsigned columns);

    void set(unsigned, unsigned, T);
    T operator()(unsigned, unsigned) const;
    Matrix<T> operator*(T scalar) const;
    Matrix<T> operator*(Matrix<T> other) const;
    Matrix<T> operator+(Matrix<T> other) const;
    Matrix<T> operator-(Matrix<T> other) const;
    Matrix<T> transpose() const;
    void print() const;
    
    void clear(){
        for(node* temp = root->down; temp; temp = temp->down){
            node* temp2 = temp->next;
            if(temp2)
                temp2->killSelf();
        }
    }

    ~Matrix(){};
};

template <typename T>
Matrix<T>::Matrix(unsigned rows, unsigned columns){
    this->rows = rows;
    this->columns = columns;
    root = new node();
    node* temp;

    temp = root;
    for(int i = 0; i<=rows; i++){
        temp->down = new node();
        temp = temp->down;
    }

    temp = root;
    for(int i = 0; i<=columns; i++){
        temp->next = new node();
        temp = temp->next;
    }
}

template <typename T>
void Matrix<T>::check(unsigned row, unsigned column) const{
    if(row >= rows || column >= columns){
        throw "Index out of matrix range";
    }
}

template <typename T>
void Matrix<T>::set(unsigned row, unsigned column, T data){
    check(row, column);
    if(data == 0) return;
    node* toAdd = new node(row, column, data);

    node** temp = &root;
    for(int i = 0; i<=row; i++){
        temp = &((*temp)->down);
    }

    temp = &((*temp)->next);
    while(*temp && (*temp)->cpos < column){
        temp = &((*temp)->next);
    }

    if(*temp && (*temp)->cpos == column) throw "Index already set!";

    toAdd->next = *temp;
    *temp = toAdd;

    temp = &root;
    for(int i = 0; i<=column; i++){
        temp = &((*temp)->next);
    }

    temp = &((*temp)->down);
    while(*temp && (*temp)->rpos < row){
        temp = &((*temp)->down);
    }

    toAdd->down = *temp;
    *temp = toAdd;
}

template <typename T>
T Matrix<T>::operator()(unsigned row, unsigned column) const{
    check(row, column);
    node* temp = root;

    for(int i = 0; i<=row; i++){
        temp = temp->down;
    }

    temp = temp->next;
    while(temp && temp->cpos < column){
        temp = temp->next;
    }

    if(!temp || temp->cpos > column)
        return 0;

    return temp->data;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(T scalar) const{
    Matrix<T> ans(rows, columns);

    for(node* t = root->down; t; t = t->down){
        node* temp = t->next;
        while(temp){
            ans.set(temp->rpos, temp->cpos, temp->data*scalar);
            temp = temp->next;
        }
    }
    return ans;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T> other) const{
    Matrix<T> ans(rows, other.columns);
    
    for(int i = 0; i<rows; i++){
        for(int j = 0; j<other.columns; j++){
            T tempData = 0;
            for(int k = 0; k<columns; k++){
                T l = (*this)(i, k);
                T r = other(k, j);
                tempData += l*r;
            }
            if(tempData)
                ans.set(i, j, tempData);
        }
    }

    return ans;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T> other) const{
    Matrix<T> ans(rows, columns);

    for(int i = 0; i<rows; i++){
        for(int j = 0; j<columns; j++){
            T l = (*this)(i, j);
            T r = other(i, j);
            if(l + r)
                ans.set(i, j, l+r);
        }
    }

    return ans;
}
            
template <typename T>
Matrix<T> Matrix<T>::operator-(Matrix<T> other) const{
    Matrix<T> ans(rows, columns);

    for(int i = 0; i<rows; i++){
        for(int j = 0; j<columns; j++){
            T l = (*this)(i, j);
            T r = other(i, j);
            if(l - r)
                ans.set(i, j, l-r);
        }
    }

    return ans;
}


template <typename T>
Matrix<T> Matrix<T>::transpose() const{
    Matrix<T> ans(rows, columns);

    for(int i = 0; i<rows; i++){
        for(int j = 0; j<columns; j++){
            T temp = (*this)(i, j);
            if(temp)
                ans.set(j, i, temp);
        }
    }

    return ans;
}

template <typename T>
void Matrix<T>::print() const{
    for(int i = 0; i<rows; i++){
        for(int j = 0; j<rows; j++){
            cout<<(*this)(i, j)<<" ";
        }
        cout<<endl;
    }
}

#endif //SPARSE_MATRIX_MATRIX_H
