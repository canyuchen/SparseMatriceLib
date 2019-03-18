#ifndef TRIBASIC_H
#define TRIBASIC_H

#include <iostream>
#include <vector>
#include <SparseMatriceLib/TRI/TRIPoint.h>

namespace SparseMatriceLib
{
namespace TRI
{
template <typename T>
class TRIBasic
{
    public:
        TRIBasic();
        virtual ~TRIBasic();
        // Instance untouched
        void printMatrix() const;
        void displayTable() const;
        unsigned int getMatrixWidth() const;
        unsigned int getMatrixHeight() const;
        unsigned int getMatrixNonZeroNum() const;
        TRIBasic getNegMatrix() const;
        TRIBasic transposeMatrix() const;
        // Instance Modifying
        void resizeMatrix(unsigned int width,\
                          unsigned int height, unsigned int nonZero);
        void insertTripletToMatrix(TRIPoint<T> insertTriplet);
        void nonZeroUpdate();
        // Operators Overload
        void operator=(const TRIBasic &M);
        bool operator==(const TRIBasic &M) const;
        TRIBasic operator+(const TRIBasic &M);
        TRIBasic operator-(const TRIBasic &M);
        TRIBasic operator*(const TRIBasic &M);
        TRIBasic dotMultiply(const TRIBasic &M);
        TRIBasic getMaxWith(const TRIBasic &M);
        TRIBasic getMinWith(const TRIBasic &M);
        std::vector<TRIPoint<T>> data;
    protected:
        unsigned int matrixWidth; unsigned int matrixHeight;
        unsigned int nonZeroNum;

    private:
};

}
}


#endif //TRIBASIC_H
