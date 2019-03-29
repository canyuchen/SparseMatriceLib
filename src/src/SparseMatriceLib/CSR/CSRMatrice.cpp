
#include "SparseMatriceLib/CSR/CSRMatrice.h"

namespace SparseMatriceLib
{
namespace CSR
{

template <typename T>
CSRMatrice<T>::CSRMatrice(unsigned int width,\
                     unsigned int height)
{
    this->matrixWidth = width;
    this->matrixHeight = height;
    for(unsigned int i = 0; i <= matrixWidth; i++)
    {
        this->rowPtr.push_back(0);
    }
    CSRPoint<T> ins; ins.modifyTuple(0,0);
    this->data.push_back(ins);
}
template <typename T>
void CSRMatrice<T>::displayTable() const
{
    std::cout << '\n'<< "CSRPoint Array:" << '\n';
    for(unsigned int i = 1; i < data.size() ; i++)
    {
        std::cout << data[i].getColNum() << '\t';
    }   std::cout << '\n';
    for(unsigned int i = 1; i < data.size(); i++)
    {
        std::cout << data[i].getVal() << '\t';
    }   std::cout << '\n' << "CSR Row Pointer Array:" << '\n';
    for(unsigned int i = 1; i <= matrixWidth; i++)
    {
        std::cout << rowPtr[i] << '\t';
    }   std::cout << '\n';
}
template <typename T>
void CSRMatrice<T>::clearCSRMatrix(unsigned int matWid,\
                               unsigned int matHgt)
{
    this->matrixWidth = matWid;
    this->matrixHeight = matHgt;
    this->rowPtr.clear(); this->data.clear();
    for(unsigned int i = 0; i <= matrixWidth; i++)
    {
        this->rowPtr.push_back(0);
    }
}
template <typename T>
unsigned int CSRMatrice<T>::getMatrixWidth() const
{
    return matrixWidth;
}
template <typename T>
unsigned int CSRMatrice<T>::getMatrixHeight() const
{
    return matrixHeight;
}
template <typename T>
unsigned int CSRMatrice<T>::getMatrixNonZeroNum() const
{
    return (this->data.size() - 1);
}
template <typename T>
void CSRMatrice<T>::insertTupleToMatrix(unsigned int rowNum,\
                                    CSRPoint<T> ins)
{
    /* Debugged */
    if(this->rowPtr[rowNum] == 0)
    {
        unsigned int i;
        for( i = rowNum; i < rowPtr.size(); i++)
        {
            if(this->rowPtr[i])
            {
                this->data.insert(data.begin()+rowPtr[i], ins);
                rowPtr[rowNum] = rowPtr[i];
                for(unsigned int y = rowNum+1; y < rowPtr.size(); y++)
                {
                    if(rowPtr[y]){rowPtr[y]++;}
                }
                return;
            }
        }
        if(!(i < this->rowPtr.size()))
        {
            this->data.push_back(ins);
            rowPtr[rowNum] = data.size()-1;
            return;
        }
    }
    else
    {
        if(ins.getColNum() < this->data[rowPtr[rowNum]].getColNum())
        {

            this->data.insert(data.begin()+rowPtr[rowNum], ins);
            for(unsigned int y = rowNum+1; y < rowPtr.size(); y++)
            {
                if(rowPtr[y]){rowPtr[y]++;}
            }
            return;
        }
        unsigned int upper = data.size();
        for(unsigned int x = rowNum+1; x < rowPtr.size(); x++)
        {
            if(rowPtr[x]){upper = rowPtr[x]; break;}
        }
        unsigned int i = 0;
        for(i = rowPtr[rowNum]; i < upper; i++)
        {
            if(data[i].getColNum() == ins.getColNum())
            {
                std::cout << "CSRPoint insertion failed. Element existed." << '\n';
                return;
            }
            if(data[i].getColNum() > ins.getColNum())
            {
                this->data.insert(data.begin()+i, ins);
                for(unsigned int y = rowNum+1; y < rowPtr.size(); y++)
                {
                    if(rowPtr[y]){rowPtr[y]++;}
                }
                return;
            }
        }
        this->data.insert(data.begin()+i, ins);
        for(unsigned int y = rowNum+1; y < rowPtr.size(); y++)
        {
            if(rowPtr[y]){rowPtr[y]++;}
        }
        return;
    }
}
template <typename T>
void CSRMatrice<T>::addInsert(unsigned int rowNum,\
                          CSRPoint<T> ins)
{
    if(this->rowPtr[rowNum] == 0)
    {
        unsigned int i;
        for( i = rowNum; i < rowPtr.size(); i++)
        {
            if(this->rowPtr[i])
            {
                this->data.insert(data.begin()+rowPtr[i], ins);
                rowPtr[rowNum] = rowPtr[i];
                for(unsigned int y = rowNum+1; y < rowPtr.size(); y++)
                {
                    if(rowPtr[y])
                    {
                        rowPtr[y]++;
                    }
                }return;
            }
        }
        if(!(i < this->rowPtr.size()))
        {
            this->data.push_back(ins);
            rowPtr[rowNum] = data.size()-1;
            return;
        }
    }
    else
    {
        if(ins.getColNum() < this->data[rowPtr[rowNum]].getColNum())
        {
            this->data.insert(data.begin()+rowPtr[rowNum], ins);
            for(unsigned int y = rowNum+1; y < rowPtr.size(); y++)
            {
                if(rowPtr[y])
                {
                    rowPtr[y]++;
                }
            }return;
        }
        unsigned int upper = data.size();
        for(unsigned int x = rowNum+1; x < rowPtr.size(); x++)
        {
            if(rowPtr[x])
            {
                upper = rowPtr[x]; break;
            }
        }
        unsigned int i = 0;
        for(i = rowPtr[rowNum]; i < upper; i++)
        {
            if(data[i].getColNum() == ins.getColNum())
            {
                this->data[i].modifyTuple(data[i].getColNum(),\
                                          data[i].getVal()+ins.getVal());
                return;
            }
            if(data[i].getColNum() > ins.getColNum())
            {
                this->data.insert(data.begin()+i, ins);
                for(unsigned int y = rowNum+1; y < rowPtr.size(); y++)
                {
                    if(rowPtr[y])
                    {
                        rowPtr[y]++;
                    }
                }return;
            }
        }
        this->data.insert(data.begin()+i, ins);
        for(unsigned int y = rowNum+1; y < rowPtr.size(); y++)
        {
            if(rowPtr[y]){rowPtr[y]++;}
        }
        return;
    }

}

template <typename T>
void CSRMatrice<T>::dotMultiInsert(unsigned int rowNum,\
                          CSRPoint<T> ins)
{
    if(this->rowPtr[rowNum] == 0)
    {
        unsigned int i;
        for( i = rowNum; i < rowPtr.size(); i++)
        {
            if(this->rowPtr[i])
            {
                this->data.insert(data.begin()+rowPtr[i], ins);
                rowPtr[rowNum] = rowPtr[i];
                for(unsigned int y = rowNum+1; y < rowPtr.size(); y++)
                {
                    if(rowPtr[y])
                    {
                        rowPtr[y]++;
                    }
                }return;
            }
        }
        if(!(i < this->rowPtr.size()))
        {
            this->data.push_back(ins);
            rowPtr[rowNum] = data.size()-1;
            return;
        }
    }
    else
    {
        if(ins.getColNum() < this->data[rowPtr[rowNum]].getColNum())
        {
            this->data.insert(data.begin()+rowPtr[rowNum], ins);
            for(unsigned int y = rowNum+1; y < rowPtr.size(); y++)
            {
                if(rowPtr[y])
                {
                    rowPtr[y]++;
                }
            }return;
        }
        unsigned int upper = data.size();
        for(unsigned int x = rowNum+1; x < rowPtr.size(); x++)
        {
            if(rowPtr[x])
            {
                upper = rowPtr[x]; break;
            }
        }
        unsigned int i = 0;
        for(i = rowPtr[rowNum]; i < upper; i++)
        {
            if(data[i].getColNum() == ins.getColNum())
            {
                this->data[i].modifyTuple(data[i].getColNum(),\
                                          data[i].getVal() * ins.getVal());
                return;
            }
            if(data[i].getColNum() > ins.getColNum())
            {
                this->data.insert(data.begin()+i, ins);
                for(unsigned int y = rowNum+1; y < rowPtr.size(); y++)
                {
                    if(rowPtr[y])
                    {
                        rowPtr[y]++;
                    }
                }return;
            }
        }
        this->data.insert(data.begin()+i, ins);
        for(unsigned int y = rowNum+1; y < rowPtr.size(); y++)
        {
            if(rowPtr[y]){rowPtr[y]++;}
        }
        return;
    }

}

template <typename T>
void CSRMatrice<T>::maxInsert(unsigned int rowNum,\
                          CSRPoint<T> ins)
{
    if(this->rowPtr[rowNum] == 0)
    {
        unsigned int i;
        for( i = rowNum; i < rowPtr.size(); i++)
        {
            if(this->rowPtr[i])
            {
                this->data.insert(data.begin()+rowPtr[i], ins);
                rowPtr[rowNum] = rowPtr[i];
                for(unsigned int y = rowNum+1; y < rowPtr.size(); y++)
                {
                    if(rowPtr[y])
                    {
                        rowPtr[y]++;
                    }
                }return;
            }
        }
        if(!(i < this->rowPtr.size()))
        {
            this->data.push_back(ins);
            rowPtr[rowNum] = data.size()-1;
            return;
        }
    }
    else
    {
        if(ins.getColNum() < this->data[rowPtr[rowNum]].getColNum())
        {
            this->data.insert(data.begin()+rowPtr[rowNum], ins);
            for(unsigned int y = rowNum+1; y < rowPtr.size(); y++)
            {
                if(rowPtr[y])
                {
                    rowPtr[y]++;
                }
            }return;
        }
        unsigned int upper = data.size();
        for(unsigned int x = rowNum+1; x < rowPtr.size(); x++)
        {
            if(rowPtr[x])
            {
                upper = rowPtr[x]; break;
            }
        }
        unsigned int i = 0;
        for(i = rowPtr[rowNum]; i < upper; i++)
        {
            if(data[i].getColNum() == ins.getColNum())
            {
                this->data[i].modifyTuple(data[i].getColNum(),\
                                          max(data[i].getVal(), ins.getVal()));
                return;
            }
            if(data[i].getColNum() > ins.getColNum())
            {
                this->data.insert(data.begin()+i, ins);
                for(unsigned int y = rowNum+1; y < rowPtr.size(); y++)
                {
                    if(rowPtr[y])
                    {
                        rowPtr[y]++;
                    }
                }return;
            }
        }
        this->data.insert(data.begin()+i, ins);
        for(unsigned int y = rowNum+1; y < rowPtr.size(); y++)
        {
            if(rowPtr[y]){rowPtr[y]++;}
        }
        return;
    }

}


template <typename T>
void CSRMatrice<T>::minInsert(unsigned int rowNum,\
                          CSRPoint<T> ins)
{
    if(this->rowPtr[rowNum] == 0)
    {
        unsigned int i;
        for( i = rowNum; i < rowPtr.size(); i++)
        {
            if(this->rowPtr[i])
            {
                this->data.insert(data.begin()+rowPtr[i], ins);
                rowPtr[rowNum] = rowPtr[i];
                for(unsigned int y = rowNum+1; y < rowPtr.size(); y++)
                {
                    if(rowPtr[y])
                    {
                        rowPtr[y]++;
                    }
                }return;
            }
        }
        if(!(i < this->rowPtr.size()))
        {
            this->data.push_back(ins);
            rowPtr[rowNum] = data.size()-1;
            return;
        }
    }
    else
    {
        if(ins.getColNum() < this->data[rowPtr[rowNum]].getColNum())
        {
            this->data.insert(data.begin()+rowPtr[rowNum], ins);
            for(unsigned int y = rowNum+1; y < rowPtr.size(); y++)
            {
                if(rowPtr[y])
                {
                    rowPtr[y]++;
                }
            }return;
        }
        unsigned int upper = data.size();
        for(unsigned int x = rowNum+1; x < rowPtr.size(); x++)
        {
            if(rowPtr[x])
            {
                upper = rowPtr[x]; break;
            }
        }
        unsigned int i = 0;
        for(i = rowPtr[rowNum]; i < upper; i++)
        {
            if(data[i].getColNum() == ins.getColNum())
            {
                this->data[i].modifyTuple(data[i].getColNum(),\
                                          min(data[i].getVal(),ins.getVal()));
                return;
            }
            if(data[i].getColNum() > ins.getColNum())
            {
                this->data.insert(data.begin()+i, ins);
                for(unsigned int y = rowNum+1; y < rowPtr.size(); y++)
                {
                    if(rowPtr[y])
                    {
                        rowPtr[y]++;
                    }
                }return;
            }
        }
        this->data.insert(data.begin()+i, ins);
        for(unsigned int y = rowNum+1; y < rowPtr.size(); y++)
        {
            if(rowPtr[y]){rowPtr[y]++;}
        }
        return;
    }

}


template <typename T>
void CSRMatrice<T>::insertElemToMat(unsigned int rowNum,\
                                unsigned int colNum,\
                                T value)
{
    CSRPoint<T> ins; ins.modifyTuple(colNum, value);
    this->insertTupleToMatrix(rowNum, ins);
}
template <typename T>
void CSRMatrice<T>::printMatrix() const
{
    /* Debugged */
    unsigned int row = 1;
    std::cout << "CSRMatrice Print:" << '\n';
    while(row <= this->matrixWidth)
    {
        unsigned int pos = rowPtr[row];
        if(!rowPtr[row])
        {
            for(unsigned int i = 1; i <= matrixHeight; i++)
            {
                std::cout << 0 << '\t';
            }
            row++;
            std::cout << '\n';
        }
        else
        {
            unsigned int upper = data.size(); unsigned int x = row+1;
            while(!rowPtr[x])
            {
                x++;
            }
            if(x < rowPtr.size()){upper = rowPtr[x];}
            for(unsigned int j = 1; j <= matrixHeight; j++)
            {
                if(data[pos].getColNum() == j && pos < upper)
                {
                    std::cout << data[pos].getVal() <<'\t';
                    pos++;
                }
                else
                {
                    std::cout << 0 <<'\t';
                }
            }
            row++;
            std::cout << '\n';
        }
    }
}
template <typename T>
void CSRMatrice<T>::operator=(const CSRMatrice<T> &M)
{
    /* Debugged */
    if(this->matrixWidth != M.getMatrixWidth() ||\
       this->matrixHeight!= M.getMatrixHeight())
    {
        std::cout << "Warning: Matrix Size changed." << '\n';
    }
    this->matrixWidth = M.matrixWidth;
    this->matrixHeight = M.matrixHeight;
    this->data.clear(); this->rowPtr.clear();
    for(unsigned int i = 0; i < M.data.size(); i++)
    {
        this->data.push_back(M.data[i]);
    }
    for(unsigned int i = 0; i < M.rowPtr.size(); i++)
    {
        this->rowPtr.push_back(M.rowPtr[i]);
    }
}

template <typename T>
bool CSRMatrice<T>::operator==(const CSRMatrice<T> &M) const
{
    if(matrixHeight != M.getMatrixHeight() ||\
       matrixWidth  != M.getMatrixWidth())
    {
        std::cout << "Compare Size Error." << '\n';
        return 0;
    }
    else
    {
        if(this->data.size()!= M.data.size())
        {
            return 0;
        }
        for(unsigned int i = 0; i < this->data.size(); i++)
        {
            if(this->data[i] != M.data[i])
            {
                return 0;
            }
        }
        for(unsigned int i = 0; i < this->rowPtr.size(); i++)
        {
            if(this->rowPtr[i] != M.rowPtr[i])
            {
                return 0;
            }
        }
        return 1;
    }
}

//Not Debugged
template <typename T>
CSRMatrice<T> CSRMatrice<T>::operator+(const CSRMatrice<T> &M)
{
    if(this->getMatrixWidth() != M.getMatrixWidth() ||\
       this->getMatrixHeight()!= M.getMatrixHeight())
    {
        std::cout << "Unable to Add." << '\n';
        return *this;
    }
    CSRMatrice<T> temp(M.getMatrixWidth(),\
                   M.getMatrixHeight());
    temp = M;
    unsigned int row = 1;
    while(row <= this->getMatrixWidth())
    {
        if(!rowPtr[row]){row++; continue;}
        unsigned int upper = data.size();
        unsigned int x = row+1;

        while(!rowPtr[x])
        {
            x++;
        }
        if(x < rowPtr.size()){upper = rowPtr[x];}
        for(unsigned int pos = rowPtr[row]; pos < upper; pos++)
        {
            //data[pos].printTuple();
            temp.addInsert(row, data[pos]);
        }
        row++;
    }
    return temp;
}

template <typename T>
CSRMatrice<T> CSRMatrice<T>::dotMutiply(const CSRMatrice<T> &M)
{
    if(this->getMatrixWidth() != M.getMatrixWidth() ||\
       this->getMatrixHeight()!= M.getMatrixHeight())
    {
        std::cout << "Unable to Add." << '\n';
        return *this;
    }
    CSRMatrice<T> temp(M.getMatrixWidth(),\
                   M.getMatrixHeight());
    temp = M;
    unsigned int row = 1;
    while(row <= this->getMatrixWidth())
    {
        if(!rowPtr[row]){row++; continue;}
        unsigned int upper = data.size();
        unsigned int x = row+1;

        while(!rowPtr[x])
        {
            x++;
        }
        if(x < rowPtr.size()){upper = rowPtr[x];}
        for(unsigned int pos = rowPtr[row]; pos < upper; pos++)
        {
            //data[pos].printTuple();
            temp.dotMultiInsert(row, data[pos]);
        }
        row++;
    }
    return temp;
}

template <typename T>
CSRMatrice<T> CSRMatrice<T>::getMaxWith(const CSRMatrice<T> &M)
{
    if(this->getMatrixWidth() != M.getMatrixWidth() ||\
       this->getMatrixHeight()!= M.getMatrixHeight())
    {
        std::cout << "Unable to Add." << '\n';
        return *this;
    }
    CSRMatrice<T> temp(M.getMatrixWidth(),\
                   M.getMatrixHeight());
    temp = M;
    unsigned int row = 1;
    while(row <= this->getMatrixWidth())
    {
        if(!rowPtr[row]){row++; continue;}
        unsigned int upper = data.size();
        unsigned int x = row+1;

        while(!rowPtr[x])
        {
            x++;
        }
        if(x < rowPtr.size()){upper = rowPtr[x];}
        for(unsigned int pos = rowPtr[row]; pos < upper; pos++)
        {
            //data[pos].printTuple();
            temp.maxInsert(row, data[pos]);
        }
        row++;
    }
    return temp;
}

template <typename T>
CSRMatrice<T> CSRMatrice<T>::getMinWith(const CSRMatrice<T> &M)
{
    if(this->getMatrixWidth() != M.getMatrixWidth() ||\
       this->getMatrixHeight()!= M.getMatrixHeight())
    {
        std::cout << "Unable to Add." << '\n';
        return *this;
    }
    CSRMatrice<T> temp(M.getMatrixWidth(),\
                   M.getMatrixHeight());
    temp = M;
    unsigned int row = 1;
    while(row <= this->getMatrixWidth())
    {
        if(!rowPtr[row]){row++; continue;}
        unsigned int upper = data.size();
        unsigned int x = row+1;

        while(!rowPtr[x])
        {
            x++;
        }
        if(x < rowPtr.size()){upper = rowPtr[x];}
        for(unsigned int pos = rowPtr[row]; pos < upper; pos++)
        {
            //data[pos].printTuple();
            temp.minInsert(row, data[pos]);
        }
        row++;
    }
    return temp;
}


template <typename T>
CSRMatrice<T> CSRMatrice<T>::getNegMat() const
{
    CSRMatrice<T> temp(this->getMatrixWidth(), \
                   this->getMatrixHeight());
    temp = *this;
    for(unsigned int i = 1; i < data.size(); i++)
    {
        temp.data[i].modifyTuple(this->data[i].getColNum(),\
                               -(this->data[i].getVal()));
    }
    return temp;
}
template <typename T>
CSRMatrice<T> CSRMatrice<T>::operator-(const CSRMatrice<T> &M)
{
    CSRMatrice<T> temp(this->getMatrixWidth(),\
                   this->getMatrixHeight());
    temp = *this+M.getNegMat();
    return temp;
}
template <typename T>
CSRMatrice<T> CSRMatrice<T>::operator*(const CSRMatrice<T> &M)
{
    if(this->getMatrixHeight() != M.getMatrixWidth())
    {
        std::cout << "ERROR in CSRMatrice Multiplication: size incompatible." << '\n';
        return *this;
    }
    CSRMatrice<T> temp(this->getMatrixWidth(),\
                   M.getMatrixHeight());
    for(unsigned int thisRow = 1; thisRow < this->getMatrixWidth(); thisRow++)
    {
        unsigned int thisUp = data.size();
        for(unsigned int y = thisRow+1; y < rowPtr.size(); y++)
        {
            if(rowPtr[y]){thisUp = rowPtr[y]; break;}
        }
        for(unsigned int pos = rowPtr[thisRow]; pos < thisUp && pos; pos++)
        {
            unsigned int Mrow = this->data[pos].getColNum();
            CSRPoint<T> ins;
            unsigned int upper = M.data.size();
            for(unsigned int x = Mrow+1; x < M.rowPtr.size(); x++)
            {
                if(M.rowPtr[x]){upper = M.rowPtr[x]; break;}
            }
            for(unsigned int Mpos = M.rowPtr[Mrow]; Mpos < upper && Mpos; Mpos++ )
            {
                int insVal = data[pos].getVal()*M.data[Mpos].getVal();
                if(insVal)
                {
                    ins.modifyTuple(M.data[Mpos].getColNum(), insVal);
                    temp.addInsert(thisRow, ins);
                }
            }
        }
    }return temp;
}
template <typename T>
CSRMatrice<T>::~CSRMatrice()
{
    //dtor
}


template class CSRMatrice<double>;
template class CSRMatrice<int>;

}
}
