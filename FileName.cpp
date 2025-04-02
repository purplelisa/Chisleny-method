#include <iostream>
#include <conio.h>
#include <fstream>


double matrix_norm(double** matrix, int sizer, int sizec)
{
    double matrix_norm = 0;
    for (int i = 0; i < sizer; i++)
        for (int j = 0; j < sizec; j++)
        {
            if (matrix_norm < abs(matrix[i][j]))
            {
                matrix_norm = abs(matrix[i][j]);
            }
        }
    return matrix_norm;
}

double vectorcolumn_norm(double* vec, int size)
{
    double vectorcolumn_norm = 0;
    for (int i = 0; i < size; i++)
    {
        if (vectorcolumn_norm < abs(vec[i]))
        {
            vectorcolumn_norm = abs(vec[i]);
        }
    }
    return vectorcolumn_norm;
}


void main()
{
    int inp = 0;
    std::cout << "Choose input methtod" << std::endl;
    std::cout << "1 - Input from file" << std::endl;
    std::cout << "2 - Keyboard input" << std::endl;
    std::cin >> inp;
    switch (inp)
    {
    case(1):
    {
        std::ifstream fin("test.txt");
        int sizerows;
        int sizecol;
        fin >> sizerows;
        fin >> sizecol;
        double** matrix = new double* [sizerows];
        for (int i = 0; i < sizerows; i++)
            matrix[i] = new double[sizecol];

        double* systemsolution = new double[sizerows];
        double* additional = new double[sizerows];

        for (int i = 0; i < sizerows; i++)
        {
            additional[i] = 0;
        }


        for (int i = 0; i < sizerows; i++)
            for (int j = 0; j < sizecol; j++)
            {
                fin >> matrix[i][j];
            }

        for (int i = 0; i < sizerows; i++)
        {
            fin >> systemsolution[i]; std::cout << std::endl;
        }
        for (int i = 0; i < sizerows; i++)
        {
            for (int j = 0; j < sizecol; j++)
            {
                additional[i] = additional[i] + (matrix[i][j] * systemsolution[j]);
            }
        }
        system("cls");
        std::cout << "Right side of the system" << std::endl;
        for (int i = 0; i < sizerows; i++)
        {
            std::cout << additional[i] << std::endl;
        }

        _getch();
        system("cls");

        delete[] systemsolution;

        double* initialapproximations = new double[sizerows];
        std::cout << "Initial approximations" << std::endl;
        for (int i = 0; i < sizerows; i++)
        {
            initialapproximations[i] = additional[i] / matrix[i][i];
            std::cout << initialapproximations[i] << std::endl;
        }

        double eps = 0;

        double** matA = new double* [sizerows];
        for (int i = 0; i < sizerows; i++)
        {
            matA[i] = new double[sizecol];
        }

        for (int i = 0; i < sizerows; i++)
            for (int j = 0; j < sizecol; j++)
            {
                if (i != j)
                {
                    matA[i][j] = -(matrix[i][j] / matrix[i][i]);
                }
                else
                {
                    matA[i][j] = 0;
                }
            }

        _getch();
        system("cls");
        std::cout << "Choose a methtod: " << std::endl;
        std::cout << "1 - Jacobi's methtod" << std::endl;
        std::cout << "2 - Seidel's methtod" << std::endl;
        int num;
        std::cin >> num;
        std::cout << "Set the required precision:" << std::endl;
        std::cin >> eps;
        switch (num)
        {
        case(1):
        {
            double* tmp1, * tmp2, * delta;
            int k = 0;
            tmp1 = new double[sizerows];
            tmp2 = new double[sizerows];
            delta = new double[sizerows];
            for (int i = 0; i < sizerows; i++)
            {
                tmp1[i] = initialapproximations[i];
                delta[i] = 0;
            }
            do
            {
                for (int i = 0; i < sizerows; i++)
                {
                    tmp2[i] = initialapproximations[i];
                    for (int j = 0; j < sizecol; j++)
                    {
                        tmp2[i] += matA[i][j] * tmp1[j];
                    }
                }
                for (int i = 0; i < sizerows; i++)
                    delta[i] = tmp2[i] - tmp1[i];
                for (int i = 0; i < sizerows; i++)
                    tmp1[i] = tmp2[i];
                k++;
            } while (vectorcolumn_norm(delta, sizerows) >= (1 - matrix_norm(matA, sizerows, sizecol)) / matrix_norm(matA, sizerows, sizecol) * eps);
            std::cout << "The resulting solution: " << std::endl;
            for (int i = 0; i < sizerows; i++)
                std::cout << tmp2[i] << std::endl;
            std::cout << "Number of iterations: " << k << std::endl;
            delete[] tmp1;
            delete[] tmp2;
            delete[] delta;
            break;
        }
        case(2):
        {
            double* tmp1, * tmp2, * delta;
            int k = 0;
            tmp1 = new double[sizerows];
            tmp2 = new double[sizerows];
            delta = new double[sizerows];
            for (int i = 0; i < sizerows; i++)
            {
                tmp1[i] = initialapproximations[i];
                tmp2[i] = 0;
                delta[i] = 0;
            }
            do
            {
                for (int i = 0; i < sizerows; i++)
                {
                    tmp2[i] = initialapproximations[i];
                    for (int j = 0; j < i; j++)
                    {
                        tmp2[i] += matA[i][j] * tmp2[j];
                    }
                    for (int j = i + 1; j < sizecol; j++)
                    {
                        tmp2[i] += matA[i][j] * tmp1[j];
                    }
                }
                for (int i = 0; i < sizerows; i++)
                    delta[i] = tmp2[i] - tmp1[i];
                for (int i = 0; i < sizerows; i++)
                    tmp1[i] = tmp2[i];
                k++;
            } while (vectorcolumn_norm(delta, sizerows) >= (1 - matrix_norm(matA, sizerows, sizecol)) / matrix_norm(matA, sizerows, sizecol) * eps);
            std::cout << "The resulting solution: " << std::endl;
            for (int i = 0; i < sizerows; i++)
                std::cout << tmp2[i] << std::endl;
            std::cout << "Number of iterations: " << k << std::endl;
            delete[] tmp1;
            delete[] tmp2;
            delete[] delta;
            break;
        }
        }
        for (int i = 0; i < sizerows; i++)
        {
            delete[] matrix[i];
            delete[] matA[i];
        }
        delete[] matrix;
        delete[] matA;
        delete[] additional;
        delete[] initialapproximations;
        break;
    }
    case(2):
    {
        int sizerows;
        int sizecol;
        std::cout << "******@Write matrix size@******" << std::endl;
        std::cout << "Enter number of rows: " << std::endl;
        std::cin >> sizerows;
        std::cout << "Enter number of columns: " << std::endl;
        std::cin >> sizecol;
        double** matrix = new double* [sizerows];
        for (int i = 0; i < sizerows; i++)
            matrix[i] = new double[sizecol];

        double* systemsolution = new double[sizerows];
        double* additional = new double[sizerows];

        for (int i = 0; i < sizerows; i++)
        {
            additional[i] = 0;
        }

        system("cls");
        std::cout << "Enter matrix elements" << std::endl;
        std::cout << "For reference: the matrix is entered line by line" << std::endl;
        for (int i = 0; i < sizerows; i++)
            for (int j = 0; j < sizecol; j++)
            {
                std::cin >> matrix[i][j]; std::cout << std::endl;
            }
        system("cls");
        std::cout << "Enter system solution elements" << std::endl;
        for (int i = 0; i < sizerows; i++)
        {
            std::cin >> systemsolution[i]; std::cout << std::endl;
        }
        for (int i = 0; i < sizerows; i++)
        {
            for (int j = 0; j < sizecol; j++)
            {
                additional[i] = additional[i] + (matrix[i][j] * systemsolution[j]);
            }
        }
        system("cls");
        std::cout << "Right side of the system" << std::endl;
        for (int i = 0; i < sizerows; i++)
        {
            std::cout << additional[i] << std::endl;
        }

        _getch();
        system("cls");

        delete[] systemsolution;

        double* initialapproximations = new double[sizerows];
        std::cout << "Initial approximations" << std::endl;
        for (int i = 0; i < sizerows; i++)
        {
            initialapproximations[i] = additional[i] / matrix[i][i];
            std::cout << initialapproximations[i] << std::endl;
        }

        double eps = 0;

        double** matA = new double* [sizerows];
        for (int i = 0; i < sizerows; i++)
        {
            matA[i] = new double[sizecol];
        }

        for (int i = 0; i < sizerows; i++)
            for (int j = 0; j < sizecol; j++)
            {
                if (i != j)
                {
                    matA[i][j] = -(matrix[i][j] / matrix[i][i]);
                }
                else
                {
                    matA[i][j] = 0;
                }
            }

        _getch();
        system("cls");
        std::cout << "Choose a methtod: " << std::endl;
        std::cout << "1 - Jacobi's methtod" << std::endl;
        std::cout << "2 - Seidel's methtod" << std::endl;
        int num;
        std::cin >> num;
        std::cout << "Set the required precision:" << std::endl;
        std::cin >> eps;
        switch (num)
        {
        case(1):
        {
            double* tmp1, * tmp2, * delta;
            int k = 0;
            tmp1 = new double[sizerows];
            tmp2 = new double[sizerows];
            delta = new double[sizerows];
            for (int i = 0; i < sizerows; i++)
            {
                tmp1[i] = initialapproximations[i];
                delta[i] = 0;
            }
            do
            {
                for (int i = 0; i < sizerows; i++)
                {
                    tmp2[i] = initialapproximations[i];
                    for (int j = 0; j < sizecol; j++)
                    {
                        tmp2[i] += matA[i][j] * tmp1[j];
                    }
                }
                for (int i = 0; i < sizerows; i++)
                    delta[i] = tmp2[i] - tmp1[i];
                for (int i = 0; i < sizerows; i++)
                    tmp1[i] = tmp2[i];
                k++;
            } while (vectorcolumn_norm(delta, sizerows) >= (1 - matrix_norm(matA, sizerows, sizecol)) / matrix_norm(matA, sizerows, sizecol) * eps);
            std::cout << "The resulting solution: " << std::endl;
            for (int i = 0; i < sizerows; i++)
                std::cout << tmp2[i] << std::endl;
            std::cout << "Number of iterations: " << k << std::endl;
            delete[] tmp1;
            delete[] tmp2;
            delete[] delta;
            break;
        }
        case(2):
        {
            double* tmp1, * tmp2, * delta;
            int k = 0;
            tmp1 = new double[sizerows];
            tmp2 = new double[sizerows];
            delta = new double[sizerows];
            for (int i = 0; i < sizerows; i++)
            {
                tmp1[i] = initialapproximations[i];
                tmp2[i] = 0;
                delta[i] = 0;
            }
            do
            {
                for (int i = 0; i < sizerows; i++)
                {
                    tmp2[i] = initialapproximations[i];
                    for (int j = 0; j < i; j++)
                    {
                        tmp2[i] += matA[i][j] * tmp2[j];
                    }
                    for (int j = i + 1; j < sizecol; j++)
                    {
                        tmp2[i] += matA[i][j] * tmp1[j];
                    }
                }
                for (int i = 0; i < sizerows; i++)
                    delta[i] = tmp2[i] - tmp1[i];
                for (int i = 0; i < sizerows; i++)
                    tmp1[i] = tmp2[i];
                k++;
            } while (vectorcolumn_norm(delta, sizerows) >= (1 - matrix_norm(matA, sizerows, sizecol)) / matrix_norm(matA, sizerows, sizecol) * eps);
            std::cout << "The resulting solution: " << std::endl;
            for (int i = 0; i < sizerows; i++)
                std::cout << tmp2[i] << std::endl;
            std::cout << "Number of iterations: " << k << std::endl;
            delete[] tmp1;
            delete[] tmp2;
            delete[] delta;
            break;
        }
        }
        for (int i = 0; i < sizerows; i++)
        {
            delete[] matrix[i];
            delete[] matA[i];
        }
        delete[] matrix;
        delete[] matA;
        delete[] additional;
        delete[] initialapproximations;
        break;
    }
    }


}