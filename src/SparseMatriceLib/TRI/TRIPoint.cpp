#include <iostream>
#include <SparseMatriceLib/TRI/TRIPoint.h>

namespace SparseMatriceLib
{
namespace TRI
{

template <typename T>
TRIPoint<T>::TRIPoint()
{
    rowNum = 0; colNum = 0;
    value = 0;//ctor
}
template <typename T>
unsigned int TRIPoint<T>::getRowNum() const
{
    return rowNum;
}
template <typename T>
unsigned int TRIPoint<T>::getColNum() const
{
    return colNum;
}
template <typename T>
void TRIPoint<T>::displayTriplet() const
{
    std::cout << rowNum <<'\t'<< colNum << '\t' << value << '\n';
}
template <typename T>
T TRIPoint<T>::getValue() const
{
    return value;
}
template <typename T>
void TRIPoint<T>::modifyTriplet(unsigned int newRow, unsigned int newCol, T newVal)
{
    rowNum = newRow; colNum = newCol;
    value = newVal;
}

template <typename T>
TRIPoint<T> TRIPoint<T>::pointDotMultiply(const TRIPoint<T> &t)
{
    TRIPoint<T> temp;

    if ((t.getColNum() != this->getColNum()) || (t.getRowNum() != this->getRowNum()))
    {
        std::cout << "ERROR" << '\n';
        return *this;
    }

    temp.rowNum = t.getRowNum();
    temp.colNum = t.getColNum();
    temp.value = (t.getValue()) * (this->getValue());
    return temp;
}

template <typename T>
TRIPoint<T> TRIPoint<T>::pointGetMaxWith(const TRIPoint<T> &t)
{
    TRIPoint<T> temp;

    if ((t.getColNum() != this->getColNum()) || (t.getRowNum() != this->getRowNum()))
    {
        std::cout << "ERROR" << '\n';
        return *this;
    }
    
    temp.rowNum = t.getRowNum();
    temp.colNum = t.getColNum();
    temp.value = (t.getValue() > this->getValue()) ? t.getValue() : this->getValue();
    return temp;
}

template <typename T>
TRIPoint<T> TRIPoint<T>::pointGetMinWith(const TRIPoint<T> &t)
{
    TRIPoint<T> temp;

    if ((t.getColNum() != this->getColNum()) || (t.getRowNum() != this->getRowNum()))
    {
        std::cout << "ERROR" << '\n';
        return *this;
    }
    
    temp.rowNum = t.getRowNum();
    temp.colNum = t.getColNum();
    temp.value = (t.getValue() < this->getValue()) ? t.getValue() : this->getValue();
    return temp;
}


template <typename T>
void TRIPoint<T>::operator=(const TRIPoint<T> &t)
{
    rowNum = t.getRowNum();
    colNum = t.getColNum();
    value = t.getValue();
}
template <typename T>
bool TRIPoint<T>::operator==(const TRIPoint<T> &t) const
{
    if(rowNum == t.getRowNum() && colNum == t.getColNum() && value == t.getValue())
    {
        return true;
    }
    else return false;
}
template <typename T>
TRIPoint<T> TRIPoint<T>::operator+(const TRIPoint<T> &t)
{
    if(this->getRowNum() != t.getRowNum() || this->getColNum() != t.getColNum())
    {
        std::cout << "ERROR: Unable to add Triple" << '\n';
        return *this;
    }
    TRIPoint<T> Temp;
    Temp.rowNum = this->getRowNum(); Temp.colNum = this->getColNum();
    Temp.value = this->getValue() + t.getValue();
    if(Temp.getValue() == 0)
    {
        Temp.modifyTriplet(0,0,0);
    }
    return Temp;
}



template <typename T>
TRIPoint<T>::~TRIPoint()
{
    //dtor
}

template class TRIPoint<double>;
template class TRIPoint<int>;

}
}









