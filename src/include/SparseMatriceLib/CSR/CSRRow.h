#ifndef CSRROW_H
#define CSRROW_H
#include <iostream>
#include <vector>

#define TRUE 1
#define FALSE 0

#include <SparseMatriceLib/CSR/CSRPoint.h>

namespace SparseMatriceLib
{
namespace CSR
{

template <typename T>
class CSRRow
{
    public:
        CSRRow(unsigned int row);
        ~CSRRow();

        CSRRow operator*(const CSRRow &t);
        CSRRow operator+(const CSRRow &t);
        CSRRow operator-(const CSRRow &t);
        bool operator==(const CSRRow &t) const;
        bool operator!=(const CSRRow &t) const;
        void operator=(const CSRRow &t);

        bool isEmptyRow();

    protected:
        unsigned int row;
        std::vector<CSRPoint<T>> point_class;
    private:
};


}
}


#endif //CSRROW_H
