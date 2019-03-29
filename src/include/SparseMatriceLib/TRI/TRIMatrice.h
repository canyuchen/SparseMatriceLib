#ifndef TRIMATRICE_H
#define TRIMATRICE_H
#include <iostream>
#include <vector>
#include <SparseMatriceLib/TRI/TRIBasic.h>

namespace SparseMatriceLib
{
namespace TRI
{
template <typename T>
class TRIMatrice : public TRIBasic<T>
{
    public:
        TRIMatrice();
        virtual ~TRIMatrice();
        void resizeMatrix(unsigned int width,\
                          unsigned int height, unsigned int nonZero);
        void insertTripletToMatrix(TRIPoint<T> insertTriplet);
        void displayTable() const;
        void operator=(const TRIMatrice &M);
        TRIMatrice operator+(const TRIMatrice &M);
        TRIMatrice operator*(const TRIMatrice &M);
    protected:
        std::vector<unsigned int> rowPtr;
    private:
};
}

}


#endif //TRIMATRICE_H
