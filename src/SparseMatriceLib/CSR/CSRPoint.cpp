#include <iostream>
#include "SparseMatriceLib/CSR/CSRPoint.h"

namespace SparseMatriceLib
{
namespace CSR
{
template <typename T>
CSRPoint<T>::CSRPoint()
{
    //ctor
}
template <typename T>
void CSRPoint<T>::modifyTuple(unsigned int col, T val)
{
    colNum = col; value = val;
}
template <typename T>
void CSRPoint<T>::printTuple() const
{
    if(colNum)
        std::cout<< colNum << '\t' \
                 << value  << '\n';
}
template <typename T>
void CSRPoint<T>::destroyTuple()
{
    colNum = 0; value = 0;
}
template <typename T>
unsigned int CSRPoint<T>::getColNum() const
{
    return colNum;
}
template <typename T>
T CSRPoint<T>::getVal() const
{
    return value;
}
template <typename T>
void CSRPoint<T>::operator=(const CSRPoint<T> &t)
{
    colNum = t.getColNum(); value = t.getVal();
}
template <typename T>
bool CSRPoint<T>::operator==(const CSRPoint<T> &t) const
{
    if(colNum == t.getColNum() && value == t.getVal())
    {
        return true;
    }
    return false;
}
template <typename T>
CSRPoint<T> CSRPoint<T>::operator+(const CSRPoint<T> &t)
{
    if(colNum != t.getColNum())
    {
        std::cout << "ERROR Adding CSRPoints" << '\n';
        return *this;
    }
    CSRPoint<T> Temp;
    Temp.modifyTuple(this->getColNum(), \
                     this->getVal() + t.getVal());
    if(Temp.getVal() == 0)
    {
        Temp.modifyTuple(0,0);
    }
    return Temp;


}
template <typename T>
bool CSRPoint<T>::operator!=(const CSRPoint<T> &t) const
{
    if(this->colNum != t.getColNum() ||\
       this->value  != t.getVal())
    {
        return true;
    }
    else
    {
        return false;
    }
}
template <typename T>
CSRPoint<T> CSRPoint<T>::operator-(const CSRPoint<T> &t)
{
    if(colNum != t.getColNum())
    {
        std::cout << "ERROR Sub CSRPoints." << '\n';
        return *this;
    }
    CSRPoint<T> Temp;
    if(this->getVal() == t.getVal())
    {
        Temp.modifyTuple(0,0);
    }
    else
    {
        Temp.modifyTuple(this->getColNum(),\
                         this->getVal() - t.getVal());
    }
    return Temp;
}
template <typename T>
CSRPoint<T>::~CSRPoint<T>()
{
    //dtor
}

template class CSRPoint<double>;
template class CSRPoint<int>;

}
}













