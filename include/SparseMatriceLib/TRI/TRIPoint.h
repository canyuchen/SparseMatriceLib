#ifndef TRIPOINT_H
#define TRIPOINT_H

#include <iostream>

namespace SparseMatriceLib
{
namespace TRI
{
template <typename T>
class TRIPoint
{
    public:
        TRIPoint();
        /* ATTENTION:
         * row number of first row is 1
         * 0 means the end of the list.
         */
        virtual ~TRIPoint();
        // Methods that do no change to instance: add const qualifier.
        unsigned int getRowNum() const;
        unsigned int getColNum() const;
        T getValue() const;
        void displayTriplet() const;

        void modifyTriplet(unsigned int newRow,\
                           unsigned int newCol, T newVal);
        void operator=(const TRIPoint &t);
        bool operator==(const TRIPoint &t) const;
        TRIPoint operator+(const TRIPoint &t);
        TRIPoint operator-(const TRIPoint &t);
        TRIPoint pointDotMultiply(const TRIPoint &t);
        TRIPoint pointGetMaxWith(const TRIPoint &t);
        TRIPoint pointGetMinWith(const TRIPoint &t);
    protected:
        unsigned int rowNum;
        unsigned int colNum;
        T value;
    private:
};

}
}


#endif //TRIPOINT_H
