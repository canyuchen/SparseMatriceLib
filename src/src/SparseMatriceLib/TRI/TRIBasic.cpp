#include <iostream>
#include <SparseMatriceLib/TRI/TRIBasic.h>

namespace SparseMatriceLib
{
namespace TRI
{

//constructor
template <typename T>
TRIBasic<T>::TRIBasic()
{
    matrixWidth = 0; matrixHeight = 0;
    nonZeroNum = 0;
    TRIPoint<T> a;
    a.modifyTriplet(0,0,0);
    data.push_back(a);

}

template <typename T>
void TRIBasic<T>::resizeMatrix(unsigned int width,\
                                    unsigned int height, unsigned int nonZero)
{
    matrixWidth = width; matrixHeight = height;
    nonZeroNum = nonZero;
}


template <typename T>
void TRIBasic<T>::insertTripletToMatrix(TRIPoint<T> insertTriplet)
{
    unsigned int row = insertTriplet.getRowNum();
    unsigned int col = insertTriplet.getColNum();
    unsigned int i;
    for(i = 1; i < data.size() &&
               data[i].getColNum() &&
               row > data[i].getRowNum() ; i++) ;
    for(; row == data[i].getRowNum() &&
          col > data[i].getColNum() &&
          i < data.size(); i++);
    if(row == data[i].getRowNum() &&
       col == data[i].getColNum() &&
       i < data.size())
    {
        std::cout << i << ": "<<"getRowNum: " << data[i].getRowNum() << " getColNum: "
                                              << data[i].getColNum() << " getVal: "
                                              << data[i].getValue()<< '\n';
        std::cout << "row: " << row
                  << "col: " << col
                  << "ERROR inserting" << '\n';
        return;
    }
    else
    {
        data.insert(data.begin()+i, insertTriplet);
    }
    return ;
}

template <typename T>
void TRIBasic<T>::nonZeroUpdate()
{
    /* TODO: get Non-zero number
     * Debugged
     */
    this->nonZeroNum = this->data.size() - 1;
    //std::cout << this->nonZeroNum;
    return;
}
template <typename T>
void TRIBasic<T>::displayTable() const
{
    /* TODO: Display triple table of a matrix
     * Debugged
     */
    std::cout << "Matrix Table Print:" << '\n';
    for(unsigned int i = 0; i<data.size(); i++)
    {
        std::cout << data[i].getRowNum() << '\t';
    }
    std::cout << '\n';
    for(unsigned int i = 0; i<data.size(); i++)
    {
        std::cout << data[i].getColNum() << '\t';
    }
    std::cout << '\n';
    for(unsigned int i = 0; i<data.size(); i++)
    {
        std::cout << data[i].getValue() << '\t';
    }
    std::cout << '\n';


}
template <typename T>
void TRIBasic<T>::printMatrix() const
{
    /* TODO: Print matrix.
     * Debugged
     */
    std::cout << "TRIBasic Print:" << '\n';
    unsigned int pos = 1;
    for(unsigned int i = 1; i <= getMatrixWidth(); i++)
    {
        for(unsigned int j = 1; j <= getMatrixHeight();j++)
        {
            if(data[pos].getRowNum() == i && data[pos].getColNum() == j)
            {
                std::cout << data[pos].getValue() << '\t';
                pos++;
            }
            else
            {
                std::cout << 0 << '\t';
            }
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    return;
}
template <typename T>
unsigned int TRIBasic<T>::getMatrixWidth() const
{
    return matrixWidth;
}
template <typename T>
unsigned int TRIBasic<T>::getMatrixHeight() const
{
    return matrixHeight;
}
template <typename T>
unsigned int TRIBasic<T>::getMatrixNonZeroNum() const
{
    return nonZeroNum;
}


// Operators Overload
template <typename T>
void TRIBasic<T>::operator=(const TRIBasic<T> &M)
{
    /*Debugged*/
    matrixWidth = M.getMatrixWidth();
    matrixHeight = M.getMatrixHeight();
    nonZeroNum = M.getMatrixNonZeroNum();
    this->data.assign(M.data.begin(), M.data.end());
    return;

}
template <typename T>
bool TRIBasic<T>::operator==(const TRIBasic<T> &M) const
{
   /* TODO: Equality Judge
    * Debugged
    */
    if((matrixHeight == M.getMatrixHeight()) &&
       (matrixWidth == M.getMatrixWidth())){;}
    else return false;
    unsigned int i;
    for(i = 1; this->data[i].getRowNum() &&
               M.data[i].getRowNum(); i++)
    {
        if(data[i].getRowNum()!=M.data[i].getRowNum() ||\
           data[i].getColNum()!=M.data[i].getColNum() ||\
           data[i].getValue() !=M.data[i].getValue())
        {
            return false;
        }
    }
    if(i < this->data.size() ||  i < M.data.size())
    {
        return false;
    }
    return true;
    //lixie
}
template <typename T>
TRIBasic<T> TRIBasic<T>::operator+(const TRIBasic<T> &M)
{
   /* TODO: ADD
    * Debugged
    */
    if(this->matrixWidth != M.matrixWidth ||
       this->matrixHeight != M.matrixHeight)
    {
        std::cout << "Unable To Add" << '\n';
        return *this;
    }
    TRIBasic<T> Temp; Temp.resizeMatrix(this->matrixWidth,
                                             this->matrixHeight, 0);
    unsigned int i = 1;
    unsigned int j = 1;
    while(i < data.size() && j < M.data.size())
    {

        if(data[i].getRowNum() == M.data[j].getRowNum())
        {
            if(data[i].getColNum() < M.data[j].getColNum())
            {
                Temp.data.push_back(data[i]) ; i++;
            }
            else if(data[i].getColNum() == M.data[j].getColNum())
            {
                TRIPoint<T> sum = data[i] + M.data[j];
                if(sum.getValue())
                {
                    Temp.data.push_back(sum);
                }
                i++; j++;
            }
            else if(data[i].getColNum() > M.data[j].getColNum())
            {
                Temp.data.push_back(M.data[j]); j++;
            }
            else {;}
        }
        else if(data[i].getRowNum() < M.data[j].getRowNum())
        {
            Temp.data.push_back(data[i]); i++;
        }
        else if(data[i].getRowNum() > M.data[j].getRowNum())
        {
            Temp.data.push_back(M.data[j]); j++;
        }
        else {;}
    }
    while(i < data.size())
    {
        Temp.data.push_back(data[i]);
        i++;
    }
    while(j < M.data.size())
    {
        Temp.data.push_back(M.data[j]);
        j++;
    }
    Temp.nonZeroUpdate();
    return Temp;

}
template <typename T>
TRIBasic<T> TRIBasic<T>::getNegMatrix() const
{
    /* TODO: reverse the value
     * Debugged
     */
    TRIBasic<T> NegMat; TRIPoint<T> now;
    NegMat.resizeMatrix(this->getMatrixWidth(),
                        this->getMatrixHeight(),
                        this->getMatrixNonZeroNum());
    for(unsigned int i = 1; i < data.size(); i++)
    {
        //std::cout<<i;
        now.modifyTriplet(data[i].getRowNum(),
                          data[i].getColNum(),
                          -(data[i].getValue()));
        NegMat.data.push_back(now);
    }
    return NegMat;
}
template <typename T>
TRIBasic<T> TRIBasic<T>::transposeMatrix() const
{
    /* TODO: transpose
     * Debugged
     */
    TRIBasic<T> Temp;
    Temp.resizeMatrix(this->matrixWidth,
                      this->matrixHeight,
                      this->nonZeroNum);
    TRIPoint<T> ins;
    for(unsigned int i = 1; i < data.size(); i++)
    {
        ins.modifyTriplet(data[i].getColNum(),
                          data[i].getRowNum(), data[i].getValue());
        Temp.insertTripletToMatrix(ins);
    }
    return Temp;

}

template <typename T>
TRIBasic<T> TRIBasic<T>::operator*(const TRIBasic<T> &M)
{
    /* TODO: Multiply
     * Debugged
     */
    TRIBasic<T> Temp;
    if(this->getMatrixHeight() != M.getMatrixWidth() ||
       this->getMatrixWidth() == 0 ||
       M.getMatrixHeight() == 0)
    {
        std::cout<< "ERROR in Multiplication." << '\n';
        return *this;
    }
    Temp.resizeMatrix(this->getMatrixWidth(), M.getMatrixHeight(), 0);
    //array used to store intermediate result
    std::vector<int> heightArray(M.getMatrixHeight()+1, 0);


    for(unsigned int tableRow = 1; tableRow <= this->getMatrixWidth(); tableRow++)// Each row
    {
        for(unsigned colNum = 0; colNum <= M.getMatrixHeight(); colNum++)
        {
            heightArray[colNum] = 0;
        }
        for(unsigned int j = 1; j < this->data.size(); j++)//Traverse this Matrix data vector
        {
            if(this->data[j].getRowNum() == tableRow)
            {
                for(unsigned int k = 1; k < M.data.size(); k++)//Traverse M data vector
                {
                    if(this->data[j].getColNum() == M.data[k].getRowNum())
                    {
                        heightArray[M.data[k].getColNum()] += (this->data[j].getValue())*M.data[k].getValue();
                    }
                }
            }
        }
        for(unsigned int colNum = 1; colNum <= M.getMatrixHeight(); colNum++)
        {
            if(heightArray[colNum])
            {
                TRIPoint<T> add;
                add.modifyTriplet(tableRow, colNum, heightArray[colNum]);
                Temp.insertTripletToMatrix(add);

            }
        }
    }
    Temp.nonZeroUpdate();
    return Temp;
}

template <typename T>
TRIBasic<T> TRIBasic<T>::dotMultiply(const TRIBasic<T> &M)
{
    if(this->matrixWidth != M.matrixWidth ||
       this->matrixHeight != M.matrixHeight)
    {
        std::cout << "Unable To dotMultiply" << '\n';
        return *this;
    }
    TRIBasic<T> Temp; Temp.resizeMatrix(this->matrixWidth,
                                             this->matrixHeight, 0);
    unsigned int i = 1;
    unsigned int j = 1;
    while(i < data.size() && j < M.data.size())
    {

        if(data[i].getRowNum() == M.data[j].getRowNum())
        {
            if(data[i].getColNum() < M.data[j].getColNum())
            {
                Temp.data.push_back(data[i]) ; i++;
            }
            else if(data[i].getColNum() == M.data[j].getColNum())
            {
                TRIPoint<T> sum = this->data[i].pointDotMultiply(M.data[j]);
                if(sum.getValue())
                {
                    Temp.data.push_back(sum);
                }
                i++; j++;
            }
            else if(data[i].getColNum() > M.data[j].getColNum())
            {
                Temp.data.push_back(M.data[j]); j++;
            }
            else {;}
        }
        else if(data[i].getRowNum() < M.data[j].getRowNum())
        {
            Temp.data.push_back(data[i]); i++;
        }
        else if(data[i].getRowNum() > M.data[j].getRowNum())
        {
            Temp.data.push_back(M.data[j]); j++;
        }
        else {;}
    }
    while(i < data.size())
    {
        Temp.data.push_back(data[i]);
        i++;
    }
    while(j < M.data.size())
    {
        Temp.data.push_back(M.data[j]);
        j++;
    }
    Temp.nonZeroUpdate();
    return Temp;
}

template <typename T>
TRIBasic<T> TRIBasic<T>::getMaxWith(const TRIBasic<T> &M)
{
    if(this->matrixWidth != M.matrixWidth ||
       this->matrixHeight != M.matrixHeight)
    {
        std::cout << "Unable To dotMultiply" << '\n';
        return *this;
    }
    TRIBasic<T> Temp; Temp.resizeMatrix(this->matrixWidth,
                                             this->matrixHeight, 0);
    unsigned int i = 1;
    unsigned int j = 1;
    while(i < data.size() && j < M.data.size())
    {

        if(data[i].getRowNum() == M.data[j].getRowNum())
        {
            if(data[i].getColNum() < M.data[j].getColNum())
            {
                Temp.data.push_back(data[i]) ; i++;
            }
            else if(data[i].getColNum() == M.data[j].getColNum())
            {
                TRIPoint<T> sum = this->data[i].pointGetMaxWith(M.data[j]);
                if(sum.getValue())
                {
                    Temp.data.push_back(sum);
                }
                i++; j++;
            }
            else if(data[i].getColNum() > M.data[j].getColNum())
            {
                Temp.data.push_back(M.data[j]); j++;
            }
            else {;}
        }
        else if(data[i].getRowNum() < M.data[j].getRowNum())
        {
            Temp.data.push_back(data[i]); i++;
        }
        else if(data[i].getRowNum() > M.data[j].getRowNum())
        {
            Temp.data.push_back(M.data[j]); j++;
        }
        else {;}
    }
    while(i < data.size())
    {
        Temp.data.push_back(data[i]);
        i++;
    }
    while(j < M.data.size())
    {
        Temp.data.push_back(M.data[j]);
        j++;
    }
    Temp.nonZeroUpdate();
    return Temp;
}


template <typename T>
TRIBasic<T> TRIBasic<T>::getMinWith(const TRIBasic<T> &M)
{
    if(this->matrixWidth != M.matrixWidth ||
       this->matrixHeight != M.matrixHeight)
    {
        std::cout << "Unable To dotMultiply" << '\n';
        return *this;
    }
    TRIBasic<T> Temp; Temp.resizeMatrix(this->matrixWidth,
                                             this->matrixHeight, 0);
    unsigned int i = 1;
    unsigned int j = 1;
    while(i < data.size() && j < M.data.size())
    {

        if(data[i].getRowNum() == M.data[j].getRowNum())
        {
            if(data[i].getColNum() < M.data[j].getColNum())
            {
                Temp.data.push_back(data[i]) ; i++;
            }
            else if(data[i].getColNum() == M.data[j].getColNum())
            {
                TRIPoint<T> sum = this->data[i].pointGetMinWith(M.data[j]);
                if(sum.getValue())
                {
                    Temp.data.push_back(sum);
                }
                i++; j++;
            }
            else if(data[i].getColNum() > M.data[j].getColNum())
            {
                Temp.data.push_back(M.data[j]); j++;
            }
            else {;}
        }
        else if(data[i].getRowNum() < M.data[j].getRowNum())
        {
            Temp.data.push_back(data[i]); i++;
        }
        else if(data[i].getRowNum() > M.data[j].getRowNum())
        {
            Temp.data.push_back(M.data[j]); j++;
        }
        else {;}
    }
    while(i < data.size())
    {
        Temp.data.push_back(data[i]);
        i++;
    }
    while(j < M.data.size())
    {
        Temp.data.push_back(M.data[j]);
        j++;
    }
    Temp.nonZeroUpdate();
    return Temp;
}

template <typename T>
TRIBasic<T> TRIBasic<T>::operator-(const TRIBasic<T> &M)
{
    TRIBasic<T> Temp;
    Temp = *this+M.getNegMatrix();
    return Temp;
}
//destructor
//xie
template <typename T>
TRIBasic<T>::~TRIBasic<T>()
{
    data.clear();
   //std::cout << "TripleMatrix Destructed." << '\n';
}

template class TRIBasic<int>;
template class TRIBasic<double>;

}
}
