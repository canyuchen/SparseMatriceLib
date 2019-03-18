#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <vector>
using namespace std;

#include <SparseMatriceLib/CSR/CSRMatrice.h>
#include <SparseMatriceLib/CL/CLMatrice.h>
#include <SparseMatriceLib/TRI/TRIMatrice.h>
#include <SparseMatriceLib/TRI/TRIPoint.h>
#include <SparseMatriceLib/TRI/TRIBasic.h>
#include <SparseMatriceLib/CSR/CSRPoint.h>
#include <SparseMatriceLib/CSR/CSRRow.h>
using namespace SparseMatriceLib;

void help();
void CSRAdd();
void TRIAdd();
void CSRMult();
void TRIMult();
void CSRSub();
void TRISub();
void CSRDotMult();
void TRIDotMult();
void TRIMax();
void TRIMin();
void CLAdd();
void CLSub();
void CLMult();
void CLInv();
void CLDet();
void CSRMin();
void CSRMax();

int main(int argc, char const *argv[])
{
    if ((argc == 1) || (argc == 2))
    {
        //std::cout << "invalid input, input again" << std::endl;
        help();
        return 0;
    }
    else if (argc == 3)
    {
        if (strcmp(argv[1], "-tri") == 0)
        {
            if (strcmp(argv[2], "-add") == 0)
            {
                TRIAdd();
                return 0;
            }
            else if (strcmp(argv[2], "-sub") == 0)
            {
                TRISub();
                return 0;
            }
            else if (strcmp(argv[2], "-mult") == 0)
            {
                TRIMult();
                return 0 ;
            }
            else if (strcmp(argv[2], "-dot") == 0)
            {
                TRIDotMult();
                return 0;
            }
            else if (strcmp(argv[2], "-max") == 0)
            {
                TRIMax();
                return 0;
            }
            else if (strcmp(argv[2], "-min") == 0)
            {
                TRIMin();
                return 0;
            }
            else
            {
                std::cout << "invalid input, input again" << std::endl;
                help();
                return 0;
            }
        }
        else if (strcmp(argv[1], "-cl") == 0)
        {
            if (strcmp(argv[2], "-add") == 0)
            {
                CLAdd();
                return 0;
            }
            else if (strcmp(argv[2], "-sub") == 0)
            {
                CLSub();
                return 0;
            }
            else if (strcmp(argv[2], "-mult") == 0)
            {
                CLMult();
                return 0 ;
            }
            else if (strcmp(argv[2], "-det") == 0)
            {
                CLDet();
                return 0;
            }
            else if (strcmp(argv[2], "-inv") == 0)
            {
                CLInv();
                return 0;
            }
            else
            {
                std::cout << "invalid input, input again" << std::endl;
                help();
                return 0;
            }
        }
       else if (strcmp(argv[1], "-csr") == 0)
       {
           if (strcmp(argv[2], "-add") == 0)
           {
               CSRAdd();
               return 0;
           }
           else if (strcmp(argv[2], "-sub") == 0)
           {
               CSRSub();
               return 0;
           }
           else if (strcmp(argv[2], "-mult") == 0)
           {
               CSRMult();
               return 0 ;
           }
           else if (strcmp(argv[2], "-dot") == 0)
           {
               CSRDotMult();
               return 0;
           }
           else if (strcmp(argv[2], "-max") == 0)
           {
               CSRMax();
               return 0;
           }
           else if (strcmp(argv[2], "-min") == 0)
           {
               CSRMin();
               return 0;
           }
           else
           {
               std::cout << "invalid input, input again" << std::endl;
               help();
               return 0;
           }
       }
        else
        {
            std::cout << "invalid input, input again" << std::endl;
            help();
            return 0;
        }
    }

    return 0;
}

void help()
{
    std::cout << "Usage:" << " sml [-formats] [-options]" << '\n';
    std::cout <<'\t'<<"Formats" << '\t' << "Options" <<'\t' << " Descriptions "<< '\n';
    std::cout << '\n';
    std::cout
              << '\t' << "-tri" <<'\n'
              << '\t' << '\t'<< "-mult" << '\t' << "multiplication of two matrices" << '\n'
              << '\t' << '\t'<< "-add" << '\t' << "addition of two matrices." << '\n'
              << '\t' << '\t'<< "-sub" << '\t' << "subtraction of two matrices." << '\n'
              << '\t' << '\t'<< "-dot" << '\t' << "dot product of two matrices" << '\n' 
              << '\t' << '\t'<< "-max" << '\t' << "every point is max of two matrices." << '\n'
              << '\t' << '\t'<< "-min" << '\t' << "every point is min of two matrices." << '\n'<< '\n'
              << '\t' << "-cl" <<'\n'
              << '\t' << '\t'<< "-mult" << '\t' << "multiplication of two matrices" << '\n'
              << '\t' << '\t'<< "-add" << '\t' << "addition of two matrices." << '\n'
              << '\t' << '\t'<< "-sub" << '\t' << "subtraction of two matrices." << '\n' 
              << '\t' << '\t'<< "-det" << '\t' << "calculate the determinant of a matrix." << '\n' 
              << '\t' << '\t'<< "-inv" << '\t' << "output the inversion of a matrix." << '\n' << '\n'
              << '\t' << "-csr" <<'\n'
              << '\t' << '\t'<< "-mult" << '\t' <<"multiplication of two matrices" << '\n'
              << '\t' << '\t'<< "-add" << '\t' << "addition of two matrices." << '\n'
              << '\t' << '\t'<< "-sub" << '\t' << "subtraction of two matrices." << '\n'
              << '\t' << '\t'<< "-dot" << '\t' << "dot product of two matrices" << '\n' 
              << '\t' << '\t'<< "-max" << '\t' << "every point is max of two matrices." << '\n' 
              << '\t' << '\t'<< "-min" << '\t' << "every point is min of two matrices." << '\n' << std::endl;
}

void CSRAdd()
{
    unsigned int row_1, row_2;
    unsigned int col_1, col_2;
    unsigned int num_1, num_2;

    cout << "input the number of the total row, col, non-zero elements of the first matrice (in the format 'row col elem') :" << endl;
    cin >> row_1 >> col_1 >> num_1;


    cout << "input the number of the total row, col, non-zero elements of the second matrice (in the format 'row col elem') :" << endl;
    cin >> row_2 >> col_2 >> num_2;


    for(;;)
    {
        if((row_1 == row_2) && (col_1 == col_2))
        {
            break;
        }
        cout << "input the number of the total row, col, non-zero elements of the first matrice (in the format 'row col elem') :" << endl;
        cin >> row_1 >> col_1 >> num_1;

        cout << "input the number of the total row, col, non-zero elements of the second matrice (in the format 'row col elem') :" << endl;
        cin >> row_2 >> col_2 >> num_2;
    }

    CSR::CSRMatrice<int> CSR_1(row_1,col_1);
    CSR::CSRMatrice<int> CSR_2(row_2,col_2);

    unsigned int row = 0, col = 0;
    int val = 0;

    cout << "input the non-zero elements of the first matrice (int the format 'row col val') :" <<endl;
    for (unsigned int i = 1; i <= num_1; ++i)
    {
        cout << "element" << i << ":" ;
        cin >> row >> col >> val;
        CSR_1.insertElemToMat(row, col, val);
    }
    cout << "input the non-zero elements of the second matrice (int the format 'row col val') :" <<endl;
    for (unsigned int i = 1; i <= num_1; ++i)
    {
        cout << "element" << i << ":" ;
        cin >> row >> col >> val;
        CSR_2.insertElemToMat(row, col, val);
    }

    cout << "the first matrice is:" << endl;
    CSR_1.printMatrix();
    cout << "the second matrice is:" << endl;
    CSR_2.printMatrix();
    cout << "the result matrice is:" << endl;
    (CSR_1+CSR_2).printMatrix();
}

void TRIAdd()
{
    unsigned int row_1, row_2;
    unsigned int col_1, col_2;
    unsigned int num_1, num_2;

    cout << "input the number of the total row, col, non-zero elements of the first matrice (in the format 'row col elem') :" << endl;
    cin >> row_1 >> col_1 >> num_1;


    cout << "input the number of the total row, col, non-zero elements of the second matrice (in the format 'row col elem') :" << endl;
    cin >> row_2 >> col_2 >> num_2;


    for(;;)
    {
        if((row_1 == row_2) && (col_1 == col_2))
        {
            break;
        }
        cout << "input the number of the total row, col, non-zero elements of the first matrice (in the format 'row col elem') :" << endl;
        cin >> row_1 >> col_1 >> num_1;

        cout << "input the number of the total row, col, non-zero elements of the second matrice (in the format 'row col elem') :" << endl;
        cin >> row_2 >> col_2 >> num_2;
    }

    TRI::TRIMatrice<int> TRI_1;
    TRI::TRIMatrice<int> TRI_2;
    TRI_1.resizeMatrix(row_1,col_1,num_1);
    TRI_2.resizeMatrix(row_2,col_2,num_2);

    unsigned int row = 0, col = 0;
    int val = 0;

    cout << "input the non-zero elements of the first matrice (int the format 'row col val') :" <<endl;
    for (unsigned int i = 1; i <= num_1; ++i)
    {
        cout << "element" << i << ":" ;
        cin >> row >> col >> val;
        TRI::TRIPoint<int> point_1;
        point_1.modifyTriplet(row,col,val);
        TRI_1.insertTripletToMatrix(point_1);
    }
    cout << "input the non-zero elements of the second matrice (int the format 'row col val') :" <<endl;
    for (unsigned int i = 1; i <= num_1; ++i)
    {
        cout << "element" << i << ":" ;
        cin >> row >> col >> val;
        TRI::TRIPoint<int> point_2;
        point_2.modifyTriplet(row,col,val);
        TRI_2.insertTripletToMatrix(point_2);
    }

    cout << "the first matrice is:" << endl;
    TRI_1.printMatrix();
    cout << "the second matrice is:" << endl;
    TRI_2.printMatrix();
    cout << "the result matrice is:" << endl;
    (TRI_1+TRI_2).printMatrix();

}


void CSRMult()
{
    unsigned int row_1, row_2;
    unsigned int col_1, col_2;
    unsigned int num_1, num_2;

    cout << "input the number of the total row, col, non-zero elements of the first matrice (in the format 'row col elem') :" << endl;
    cin >> row_1 >> col_1 >> num_1;


    cout << "input the number of the total row, col, non-zero elements of the second matrice (in the format 'row col elem') :" << endl;
    cin >> row_2 >> col_2 >> num_2;


    for(;;)
    {
        if((row_1 == row_2) && (col_1 == col_2))
        {
            break;
        }
        cout << "input the number of the total row, col, non-zero elements of the first matrice (in the format 'row col elem') :" << endl;
        cin >> row_1 >> col_1 >> num_1;

        cout << "input the number of the total row, col, non-zero elements of the second matrice (in the format 'row col elem') :" << endl;
        cin >> row_2 >> col_2 >> num_2;
    }

    CSR::CSRMatrice<int> CSR_1(row_1,col_1);
    CSR::CSRMatrice<int> CSR_2(row_2,col_2);

    unsigned int row = 0, col = 0;
    int val = 0;

    cout << "input the non-zero elements of the first matrice (int the format 'row col val') :" <<endl;
    for (unsigned int i = 1; i <= num_1; ++i)
    {
        cout << "element" << i << ":" ;
        cin >> row >> col >> val;
        CSR_1.insertElemToMat(row, col, val);
    }
    cout << "input the non-zero elements of the second matrice (int the format 'row col val') :" <<endl;
    for (unsigned int i = 1; i <= num_1; ++i)
    {
        cout << "element" << i << ":" ;
        cin >> row >> col >> val;
        CSR_2.insertElemToMat(row, col, val);
    }

    cout << "the first matrice is:" << endl;
    CSR_1.printMatrix();
    cout << "the second matrice is:" << endl;
    CSR_2.printMatrix();
    cout << "the result matrice is:" << endl;
    (CSR_1*CSR_2).printMatrix();
}



void TRIMult()
{
    //BUG
    unsigned int row_1, row_2;
    unsigned int col_1, col_2;
    unsigned int num_1, num_2;

    cout << "input the number of the total row, col, non-zero elements of the first matrice (in the format 'row col elem') :" << endl;
    cin >> row_1 >> col_1 >> num_1;


    cout << "input the number of the total row, col, non-zero elements of the second matrice (in the format 'row col elem') :" << endl;
    cin >> row_2 >> col_2 >> num_2;


    for(;;)
    {
        if((row_1 == row_2) && (col_1 == col_2))
        {
            break;
        }
        cout << "input the number of the total row, col, non-zero elements of the first matrice (in the format 'row col elem') :" << endl;
        cin >> row_1 >> col_1 >> num_1;

        cout << "input the number of the total row, col, non-zero elements of the second matrice (in the format 'row col elem') :" << endl;
        cin >> row_2 >> col_2 >> num_2;
    }

    TRI::TRIMatrice<int> TRI_1;
    TRI::TRIMatrice<int> TRI_2;
    TRI_1.resizeMatrix(row_1,col_1,num_1);
    TRI_2.resizeMatrix(row_2,col_2,num_2);

    unsigned int row = 0, col = 0;
    int val = 0;

    cout << "input the non-zero elements of the first matrice (int the format 'row col val') :" <<endl;
    for (unsigned int i = 1; i <= num_1; ++i)
    {
        cout << "element" << i << ":" ;
        cin >> row >> col >> val;
        TRI::TRIPoint<int> point_1;
        point_1.modifyTriplet(row,col,val);
        TRI_1.insertTripletToMatrix(point_1);
    }
    cout << "input the non-zero elements of the second matrice (int the format 'row col val') :" <<endl;
    for (unsigned int i = 1; i <= num_1; ++i)
    {
        cout << "element" << i << ":" ;
        cin >> row >> col >> val;
        TRI::TRIPoint<int> point_2;
        point_2.modifyTriplet(row,col,val);
        TRI_2.insertTripletToMatrix(point_2);
    }

    cout << "the first matrice is:" << endl;
    TRI_1.printMatrix();
    cout << "the second matrice is:" << endl;
    TRI_2.printMatrix();
    cout << "the result matrice is:" << endl;
    (TRI_1*TRI_2).printMatrix();

}


void CSRSub()
{
    unsigned int row_1, row_2;
    unsigned int col_1, col_2;
    unsigned int num_1, num_2;

    cout << "input the number of the total row, col, non-zero elements of the first matrice (in the format 'row col elem') :" << endl;
    cin >> row_1 >> col_1 >> num_1;


    cout << "input the number of the total row, col, non-zero elements of the second matrice (in the format 'row col elem') :" << endl;
    cin >> row_2 >> col_2 >> num_2;


    for(;;)
    {
        if((row_1 == row_2) && (col_1 == col_2))
        {
            break;
        }
        cout << "input the number of the total row, col, non-zero elements of the first matrice (in the format 'row col elem') :" << endl;
        cin >> row_1 >> col_1 >> num_1;

        cout << "input the number of the total row, col, non-zero elements of the second matrice (in the format 'row col elem') :" << endl;
        cin >> row_2 >> col_2 >> num_2;
    }

    CSR::CSRMatrice<int> CSR_1(row_1,col_1);
    CSR::CSRMatrice<int> CSR_2(row_2,col_2);

    unsigned int row = 0, col = 0;
    int val = 0;

    cout << "input the non-zero elements of the first matrice (int the format 'row col val') :" <<endl;
    for (unsigned int i = 1; i <= num_1; ++i)
    {
        cout << "element" << i << ":" ;
        cin >> row >> col >> val;
        CSR_1.insertElemToMat(row, col, val);
    }
    cout << "input the non-zero elements of the second matrice (int the format 'row col val') :" <<endl;
    for (unsigned int i = 1; i <= num_1; ++i)
    {
        cout << "element" << i << ":" ;
        cin >> row >> col >> val;
        CSR_2.insertElemToMat(row, col, val);
    }

    cout << "the first matrice is:" << endl;
    CSR_1.printMatrix();
    cout << "the second matrice is:" << endl;
    CSR_2.printMatrix();
    cout << "the result matrice is:" << endl;
    (CSR_1-CSR_2).printMatrix();
}



void TRISub()
{
    //BUG
    unsigned int row_1, row_2;
    unsigned int col_1, col_2;
    unsigned int num_1, num_2;

    cout << "input the number of the total row, col, non-zero elements of the first matrice (in the format 'row col elem') :" << endl;
    cin >> row_1 >> col_1 >> num_1;


    cout << "input the number of the total row, col, non-zero elements of the second matrice (in the format 'row col elem') :" << endl;
    cin >> row_2 >> col_2 >> num_2;


    for(;;)
    {
        if((row_1 == row_2) && (col_1 == col_2))
        {
            break;
        }
        cout << "input the number of the total row, col, non-zero elements of the first matrice (in the format 'row col elem') :" << endl;
        cin >> row_1 >> col_1 >> num_1;

        cout << "input the number of the total row, col, non-zero elements of the second matrice (in the format 'row col elem') :" << endl;
        cin >> row_2 >> col_2 >> num_2;
    }

    TRI::TRIMatrice<int> TRI_1;
    TRI::TRIMatrice<int> TRI_2;
    TRI_1.resizeMatrix(row_1,col_1,num_1);
    TRI_2.resizeMatrix(row_2,col_2,num_2);

    unsigned int row = 0, col = 0;
    int val = 0;

    cout << "input the non-zero elements of the first matrice (int the format 'row col val') :" <<endl;
    for (unsigned int i = 1; i <= num_1; ++i)
    {
        cout << "element" << i << ":" ;
        cin >> row >> col >> val;
        TRI::TRIPoint<int> point_1;
        point_1.modifyTriplet(row,col,val);
        TRI_1.insertTripletToMatrix(point_1);
    }
    cout << "input the non-zero elements of the second matrice (int the format 'row col val') :" <<endl;
    for (unsigned int i = 1; i <= num_1; ++i)
    {
        cout << "element" << i << ":" ;
        cin >> row >> col >> val;
        TRI::TRIPoint<int> point_2;
        point_2.modifyTriplet(row,col,val);
        TRI_2.insertTripletToMatrix(point_2);
    }

    cout << "the first matrice is:" << endl;
    TRI_1.printMatrix();
    cout << "the second matrice is:" << endl;
    TRI_2.printMatrix();
    cout << "the result matrice is:" << endl;
    (TRI_1-TRI_2).printMatrix();
}




void CSRDotMult()
{
    unsigned int row_1, row_2;
    unsigned int col_1, col_2;
    unsigned int num_1, num_2;

    cout << "input the number of the total row, col, non-zero elements of the first matrice (in the format 'row col elem') :" << endl;
    cin >> row_1 >> col_1 >> num_1;


    cout << "input the number of the total row, col, non-zero elements of the second matrice (in the format 'row col elem') :" << endl;
    cin >> row_2 >> col_2 >> num_2;


    for(;;)
    {
        if((row_1 == row_2) && (col_1 == col_2))
        {
            break;
        }
        cout << "input the number of the total row, col, non-zero elements of the first matrice (in the format 'row col elem') :" << endl;
        cin >> row_1 >> col_1 >> num_1;

        cout << "input the number of the total row, col, non-zero elements of the second matrice (in the format 'row col elem') :" << endl;
        cin >> row_2 >> col_2 >> num_2;
    }

    CSR::CSRMatrice<int> CSR_1(row_1,col_1);
    CSR::CSRMatrice<int> CSR_2(row_2,col_2);

    unsigned int row = 0, col = 0;
    int val = 0;

    cout << "input the non-zero elements of the first matrice (int the format 'row col val') :" <<endl;
    for (unsigned int i = 1; i <= num_1; ++i)
    {
        cout << "element" << i << ":" ;
        cin >> row >> col >> val;
        CSR_1.insertElemToMat(row, col, val);
    }
    cout << "input the non-zero elements of the second matrice (int the format 'row col val') :" <<endl;
    for (unsigned int i = 1; i <= num_1; ++i)
    {
        cout << "element" << i << ":" ;
        cin >> row >> col >> val;
        CSR_2.insertElemToMat(row, col, val);
    }

    cout << "the first matrice is:" << endl;
    CSR_1.printMatrix();
    cout << "the second matrice is:" << endl;
    CSR_2.printMatrix();
    cout << "the result matrice is:" << endl;
    (CSR_1.dotMutiply(CSR_2)).printMatrix();
}

void CSRMax()
{
    unsigned int row_1, row_2;
    unsigned int col_1, col_2;
    unsigned int num_1, num_2;

    cout << "input the number of the total row, col, non-zero elements of the first matrice (in the format 'row col elem') :" << endl;
    cin >> row_1 >> col_1 >> num_1;


    cout << "input the number of the total row, col, non-zero elements of the second matrice (in the format 'row col elem') :" << endl;
    cin >> row_2 >> col_2 >> num_2;


    for(;;)
    {
        if((row_1 == row_2) && (col_1 == col_2))
        {
            break;
        }
        cout << "input the number of the total row, col, non-zero elements of the first matrice (in the format 'row col elem') :" << endl;
        cin >> row_1 >> col_1 >> num_1;

        cout << "input the number of the total row, col, non-zero elements of the second matrice (in the format 'row col elem') :" << endl;
        cin >> row_2 >> col_2 >> num_2;
    }

    CSR::CSRMatrice<int> CSR_1(row_1,col_1);
    CSR::CSRMatrice<int> CSR_2(row_2,col_2);

    unsigned int row = 0, col = 0;
    int val = 0;

    cout << "input the non-zero elements of the first matrice (int the format 'row col val') :" <<endl;
    for (unsigned int i = 1; i <= num_1; ++i)
    {
        cout << "element" << i << ":" ;
        cin >> row >> col >> val;
        CSR_1.insertElemToMat(row, col, val);
    }
    cout << "input the non-zero elements of the second matrice (int the format 'row col val') :" <<endl;
    for (unsigned int i = 1; i <= num_1; ++i)
    {
        cout << "element" << i << ":" ;
        cin >> row >> col >> val;
        CSR_2.insertElemToMat(row, col, val);
    }

    cout << "the first matrice is:" << endl;
    CSR_1.printMatrix();
    cout << "the second matrice is:" << endl;
    CSR_2.printMatrix();
    cout << "the result matrice is:" << endl;
    (CSR_1.getMaxWith(CSR_2)).printMatrix();
}


void CSRMin()
{
    unsigned int row_1, row_2;
    unsigned int col_1, col_2;
    unsigned int num_1, num_2;

    cout << "input the number of the total row, col, non-zero elements of the first matrice (in the format 'row col elem') :" << endl;
    cin >> row_1 >> col_1 >> num_1;


    cout << "input the number of the total row, col, non-zero elements of the second matrice (in the format 'row col elem') :" << endl;
    cin >> row_2 >> col_2 >> num_2;


    for(;;)
    {
        if((row_1 == row_2) && (col_1 == col_2))
        {
            break;
        }
        cout << "input the number of the total row, col, non-zero elements of the first matrice (in the format 'row col elem') :" << endl;
        cin >> row_1 >> col_1 >> num_1;

        cout << "input the number of the total row, col, non-zero elements of the second matrice (in the format 'row col elem') :" << endl;
        cin >> row_2 >> col_2 >> num_2;
    }

    CSR::CSRMatrice<int> CSR_1(row_1,col_1);
    CSR::CSRMatrice<int> CSR_2(row_2,col_2);

    unsigned int row = 0, col = 0;
    int val = 0;

    cout << "input the non-zero elements of the first matrice (int the format 'row col val') :" <<endl;
    for (unsigned int i = 1; i <= num_1; ++i)
    {
        cout << "element" << i << ":" ;
        cin >> row >> col >> val;
        CSR_1.insertElemToMat(row, col, val);
    }
    cout << "input the non-zero elements of the second matrice (int the format 'row col val') :" <<endl;
    for (unsigned int i = 1; i <= num_1; ++i)
    {
        cout << "element" << i << ":" ;
        cin >> row >> col >> val;
        CSR_2.insertElemToMat(row, col, val);
    }

    cout << "the first matrice is:" << endl;
    CSR_1.printMatrix();
    cout << "the second matrice is:" << endl;
    CSR_2.printMatrix();
    cout << "the result matrice is:" << endl;
    (CSR_1.getMinWith(CSR_2)).printMatrix();
}


void TRIDotMult()
{
    unsigned int row_1, row_2;
    unsigned int col_1, col_2;
    unsigned int num_1, num_2;

    cout << "input the number of the total row, col, non-zero elements of the first matrice (in the format 'row col elem') :" << endl;
    cin >> row_1 >> col_1 >> num_1;


    cout << "input the number of the total row, col, non-zero elements of the second matrice (in the format 'row col elem') :" << endl;
    cin >> row_2 >> col_2 >> num_2;


    for(;;)
    {
        if((row_1 == row_2) && (col_1 == col_2))
        {
            break;
        }
        cout << "input the number of the total row, col, non-zero elements of the first matrice (in the format 'row col elem') :" << endl;
        cin >> row_1 >> col_1 >> num_1;

        cout << "input the number of the total row, col, non-zero elements of the second matrice (in the format 'row col elem') :" << endl;
        cin >> row_2 >> col_2 >> num_2;
    }

    TRI::TRIMatrice<int> TRI_1;
    TRI::TRIMatrice<int> TRI_2;
    TRI_1.resizeMatrix(row_1,col_1,num_1);
    TRI_2.resizeMatrix(row_2,col_2,num_2);

    unsigned int row = 0, col = 0;
    int val = 0;

    cout << "input the non-zero elements of the first matrice (int the format 'row col val') :" <<endl;
    for (unsigned int i = 1; i <= num_1; ++i)
    {
        cout << "element" << i << ":" ;
        cin >> row >> col >> val;
        TRI::TRIPoint<int> point_1;
        point_1.modifyTriplet(row,col,val);
        TRI_1.insertTripletToMatrix(point_1);
    }
    cout << "input the non-zero elements of the second matrice (int the format 'row col val') :" <<endl;
    for (unsigned int i = 1; i <= num_1; ++i)
    {
        cout << "element" << i << ":" ;
        cin >> row >> col >> val;
        TRI::TRIPoint<int> point_2;
        point_2.modifyTriplet(row,col,val);
        TRI_2.insertTripletToMatrix(point_2);
    }

    cout << "the first matrice is:" << endl;
    TRI_1.printMatrix();
    cout << "the second matrice is:" << endl;
    TRI_2.printMatrix();
    cout << "the result matrice is:" << endl;
    (TRI_1.dotMultiply(TRI_2)).printMatrix();

}

void TRIMin()
{
    unsigned int row_1, row_2;
    unsigned int col_1, col_2;
    unsigned int num_1, num_2;

    cout << "input the number of the total row, col, non-zero elements of the first matrice (in the format 'row col elem') :" << endl;
    cin >> row_1 >> col_1 >> num_1;


    cout << "input the number of the total row, col, non-zero elements of the second matrice (in the format 'row col elem') :" << endl;
    cin >> row_2 >> col_2 >> num_2;


    for(;;)
    {
        if((row_1 == row_2) && (col_1 == col_2))
        {
            break;
        }
        cout << "input the number of the total row, col, non-zero elements of the first matrice (in the format 'row col elem') :" << endl;
        cin >> row_1 >> col_1 >> num_1;

        cout << "input the number of the total row, col, non-zero elements of the second matrice (in the format 'row col elem') :" << endl;
        cin >> row_2 >> col_2 >> num_2;
    }

    TRI::TRIMatrice<int> TRI_1;
    TRI::TRIMatrice<int> TRI_2;
    TRI_1.resizeMatrix(row_1,col_1,num_1);
    TRI_2.resizeMatrix(row_2,col_2,num_2);

    unsigned int row = 0, col = 0;
    int val = 0;

    cout << "input the non-zero elements of the first matrice (int the format 'row col val') :" <<endl;
    for (unsigned int i = 1; i <= num_1; ++i)
    {
        cout << "element" << i << ":" ;
        cin >> row >> col >> val;
        TRI::TRIPoint<int> point_1;
        point_1.modifyTriplet(row,col,val);
        TRI_1.insertTripletToMatrix(point_1);
    }
    cout << "input the non-zero elements of the second matrice (int the format 'row col val') :" <<endl;
    for (unsigned int i = 1; i <= num_1; ++i)
    {
        cout << "element" << i << ":" ;
        cin >> row >> col >> val;
        TRI::TRIPoint<int> point_2;
        point_2.modifyTriplet(row,col,val);
        TRI_2.insertTripletToMatrix(point_2);
    }

    cout << "the first matrice is:" << endl;
    TRI_1.printMatrix();
    cout << "the second matrice is:" << endl;
    TRI_2.printMatrix();
    cout << "the result matrice is:" << endl;
    (TRI_1.getMinWith(TRI_2)).printMatrix();

}

void TRIMax()
{
    unsigned int row_1, row_2;
    unsigned int col_1, col_2;
    unsigned int num_1, num_2;

    cout << "input the number of the total row, col, non-zero elements of the first matrice (in the format 'row col elem') :" << endl;
    cin >> row_1 >> col_1 >> num_1;


    cout << "input the number of the total row, col, non-zero elements of the second matrice (in the format 'row col elem') :" << endl;
    cin >> row_2 >> col_2 >> num_2;


    for(;;)
    {
        if((row_1 == row_2) && (col_1 == col_2))
        {
            break;
        }
        cout << "input the number of the total row, col, non-zero elements of the first matrice (in the format 'row col elem') :" << endl;
        cin >> row_1 >> col_1 >> num_1;

        cout << "input the number of the total row, col, non-zero elements of the second matrice (in the format 'row col elem') :" << endl;
        cin >> row_2 >> col_2 >> num_2;
    }

    TRI::TRIMatrice<int> TRI_1;
    TRI::TRIMatrice<int> TRI_2;
    TRI_1.resizeMatrix(row_1,col_1,num_1);
    TRI_2.resizeMatrix(row_2,col_2,num_2);

    unsigned int row = 0, col = 0;
    int val = 0;

    cout << "input the non-zero elements of the first matrice (int the format 'row col val') :" <<endl;
    for (unsigned int i = 1; i <= num_1; ++i)
    {
        cout << "element" << i << ":" ;
        cin >> row >> col >> val;
        TRI::TRIPoint<int> point_1;
        point_1.modifyTriplet(row,col,val);
        TRI_1.insertTripletToMatrix(point_1);
    }
    cout << "input the non-zero elements of the second matrice (int the format 'row col val') :" <<endl;
    for (unsigned int i = 1; i <= num_1; ++i)
    {
        cout << "element" << i << ":" ;
        cin >> row >> col >> val;
        TRI::TRIPoint<int> point_2;
        point_2.modifyTriplet(row,col,val);
        TRI_2.insertTripletToMatrix(point_2);
    }

    cout << "the first matrice is:" << endl;
    TRI_1.printMatrix();
    cout << "the second matrice is:" << endl;
    TRI_2.printMatrix();
    cout << "the result matrice is:" << endl;
    (TRI_1.getMaxWith(TRI_2)).printMatrix();

}



void CLAdd()
{
    CrossList M,N,T;

    CreatCLM(&M);
    CreatCLM(&N);

    T = AddCLM(M,N);
    PrintCLM(T);
    return;
}

void CLSub()
{
    CrossList M,N,T;

    CreatCLM(&M);
    CreatCLM(&N);

    T = SubCLM(M,N);
    PrintCLM(T);
    return;
}

void CLMult()
{
    CrossList M,N,T;

    CreatCLM(&M);
    CreatCLM(&N);

    T = MulCLM(M,N);
    PrintCLM(T);
    return;
}

void CLInv()
{
    CrossList M,T;

    CreatCLM(&M);

    T = InvCLM(M);
    PrintCLM(T);
    return;
}

void CLDet()
{
    CrossList M;

    CreatCLM(&M);

    printf("%f", DetCLM(M));
    return;
}

