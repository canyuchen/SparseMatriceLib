#ifndef CSRMATRICE_H
#define CSRMATRICE_H

#include <iostream>
#include <vector>

#define TRUE 1
#define FALSE 0
#define max(a,b) (((a)>(b)) ? (a) : (b))
#define min(a,b) (((a)<(b)) ? (a) : (b))

#include "SparseMatriceLib/CSR/CSRPoint.h"
#include "SparseMatriceLib/CSR/CSRRow.h"
namespace SparseMatriceLib
{
namespace CSR
{
template <typename T>
class CSRMatrice
{
    public:
        CSRMatrice(unsigned int width, \
                  unsigned int height);
        virtual ~CSRMatrice();
        void printMatrix() const;
        void displayTable() const;

        unsigned int getMatrixWidth() const;
        unsigned int getMatrixHeight() const;
        unsigned int getMatrixNonZeroNum() const;
        CSRMatrice getNegMat() const;
        //instance modifying
        void clearCSRMatrix(unsigned int matWid,\
                            unsigned int matHgt);
        void insertTupleToMatrix(unsigned int rowNum,\
                                 CSRPoint<T> ins);
        void insertElemToMat(unsigned int rowNum,\
                             unsigned int colNum, T value);
        void addInsert(unsigned int rowNum,\
                       CSRPoint<T> ins);
        void dotMultiInsert(unsigned int rowNum,\
                          CSRPoint<T> ins);
        void maxInsert(unsigned int rowNum,\
                          CSRPoint<T> ins);
        void minInsert(unsigned int rowNum,\
                          CSRPoint<T> ins);
        //operator overload
        void operator=(const CSRMatrice<T> &M);
        bool operator==(const CSRMatrice<T> &M) const;
        CSRMatrice operator+(const CSRMatrice<T> &M);
        CSRMatrice operator-(const CSRMatrice<T> &M);
        CSRMatrice operator*(const CSRMatrice<T> &M);
        CSRMatrice dotMutiply(const CSRMatrice<T> &M);
        CSRMatrice getMaxWith(const CSRMatrice<T> &M);
        CSRMatrice getMinWith(const CSRMatrice<T> &M);
    protected:
        unsigned int matrixWidth;
        unsigned int matrixHeight;
        std::vector<int>rowPtr;
        std::vector<CSRPoint<T>> data;
    private:
        enum ErrorStatus
        {
            INSERT_ERROR,\
            MULTIPLY_ERROR,\
            ADD_ERROR,\
            SUB_ERROR,\
            COL_CONFLICT_ERROR,\
            NON_ERROR,\
            ROW_CONFLICT_ERROR
        };

        ErrorStatus error_status;

};
}
}

#endif //CSRMATRICE_H
