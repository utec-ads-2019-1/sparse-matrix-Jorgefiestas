#include <bits/stdc++.h>
#include "matrix.h"

using namespace std;

int main(){
    int n, m;
    cin>>n>>m;

    Matrix<int> mat1(n, m), mat2(m, n);

    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            mat1.set(i, j, rand()%10);
            mat2.set(j, i, rand()%10);
        }
    }

    cout<<"MAT1"<<endl;
    mat1.print();

    mat1.set(0, 0, 0);

    cout<<"MAT1"<<endl;
    mat1.print();

    cout<<"MAT2:"<<endl;
    mat2.print();

    Matrix<int> mat3;
    mat3 = mat1+mat2;
    cout<<"MAT1+MAT2:"<<endl;
    mat3.print();

    Matrix<int> mat4 = mat1-mat2;
    cout<<"MAT1-MAT2:"<<endl;
    mat4.print();

    Matrix<int> mat5 = mat1*mat2;
    cout<<"MAT1*MAT2:"<<endl;
    mat5.print();

    return 0;
}
