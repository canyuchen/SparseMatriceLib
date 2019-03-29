#include "SparseMatriceLib/CSR/CSRRow.h"

namespace SparseMatriceLib
{
namespace CSR
{

template <typename T>
CSRRow<T>::CSRRow(unsigned int row)
{
    this->row = row;
    CSRPoint<T> point(0,0);
    this->point_class.push_back(point);
}


}
}












