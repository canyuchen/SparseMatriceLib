
#ifndef CSRPOINT_H
#define CSRPOINT_H
#include <iostream>

#define TRUE 1
#define FALSE 0

namespace SparseMatriceLib
{
namespace CSR
{

template <typename T>
class CSRPoint
{
    public:
        CSRPoint();
        virtual ~CSRPoint();
        void modifyTuple(unsigned int col, T val);
        void destroyTuple();
        void printTuple() const;
        unsigned int getColNum() const;
        T getVal() const;
        void operator=(const CSRPoint &t);
        bool operator!=(const CSRPoint &t) const;
        bool operator==(const CSRPoint &t) const;
        CSRPoint operator+(const CSRPoint &t);
        CSRPoint operator-(const CSRPoint &t);
    protected:
        unsigned int colNum;
        T value;
    private:
};


}
}


#endif //CSRPOINT_H
