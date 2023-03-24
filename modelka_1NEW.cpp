#include <iostream>
#include<string>
using namespace std;
void filling_matrix(float arr[10][10], int row, int colum);
void lineralaze(float ptr[10][10], int row, int colum);
void find_partial_derivative(float final_mtrx[10][10], float vector_answer[10], float ptr[10][10], int row, int row1);
float determinant(float matrix[10][10], int n);
float KramerMethod(float matriх[10][10], float vector[10], int row, int stolb);

int main()
{
    int count;// количество экспериметов
    int impact;//количество воздейтсвий(Х)
    float det_final;
    float matrix_[10][10];
    float final_mtrx[10][10];
    float vector_answer[10];
    float vector[10]; // для овтетов 
 
    setlocale(LC_ALL, "rus");
    cout << "Добро пожаловать в программу по выполнению лабораторной работы №1 по моделированию!" << endl;
    cout << "Выполнил: Дубовцов Максим Геннадьвич" << endl;
    cout << "Группа: ИВТ-262" << endl;
    cout << "Проверил(-а): Козина Светлана Александровна" << endl;
    cout << "========================================================================================================================" << endl;
    cout << "Введите количество экспериметов:"<<endl;
    cin >> count;
    cout << "Введите количество входных воздействий:" << endl;
    cin >> impact;
    cout << "========================================================================================================================" << endl;
   //<------------------------------------
    filling_matrix(matrix_,impact+1,count);
    //<-----------------------------------
    cout << endl;
    cout << "Вывод матрицы:" << endl;

    for (int y = 0; y < impact+1;y++)
    {
        cout << "================================================="<<endl;
        cout << "X" << y <<"|" << "\t";
        for (int o = 0; o < count; o++)
        {
            cout<<matrix_[y][o] << "\t" << "|" << "\t";

        }
          
        cout << endl;
    }
    cout << "=================================================" << endl;
  
    //<-----------------------------------Линеарализация
     lineralaze(matrix_,impact+1,count);
    //<-----------------------------------ПОИСК ЧАСТННЫХ ПРОИЗВОДНЫХ 

     cout << "Функция ошибки:" << endl;
     for (int u = 0;u < impact+1;u++) // кол-во уравнений. Завист от кол-во воздейтсвий
     {
         cout << "dI/d(a" << u << ")* = 2 * [(a0)";
      //<------------------------------------------------- формировать олдинаковые строки
         if (u == 0)
         {
             for (int t = 0;t < count;t++) //  по кол-во опытов
             {
                // cout << "+ 2 * [(a0)";
                 for (int l = 0;l < impact;l++) // по числу воздействий
                     cout << " + (" << matrix_[l][t] << "a" << l + 1 << ")";
             
                 if(t!=count-1) cout << " - (" << matrix_[impact][t] << ") ] + 2 *[(a0) ";
                 else cout << " - (" << matrix_[impact][t] << ") ]";
             }
             cout << endl;
             cout << endl;
         }
         else // u==1  и т.д
         {
             for (int t = 0;t < count;t++) //  по кол-во опытов
             {
                 // cout << "+ 2 * [(a0)";
                 for (int l = 0;l < impact;l++) // по числу воздействий
                     cout << " + (" << matrix_[l][t] << "a" << l + 1 << ")";
             
                 if (t != count - 1) cout << " - (" << matrix_[impact][t] << ") ]*"<<matrix_[u-1][t] << "+ 2*[(a0) ";
                 else cout << " - (" << matrix_[impact][t] << ") ]*"<< matrix_[u - 1][t];
             }
             cout << endl;
         }
         cout << endl;
         
     }

    find_partial_derivative(final_mtrx, vector_answer, matrix_, impact + 1,count);
    //<-----------------------------------ПОИСК определителя
    det_final = determinant(final_mtrx, impact + 1);
    cout << "Определитель" << det_final<<endl;
    cout << endl;
    //<-----------------------------------Решаем методом Крамера 
    if (det_final != 0)
    {
        cout << "Определитель матрицы не равен нулю. Решим исходную матрицу методом Крамера" << endl;
        for (int i = 0;i < impact + 1;i++)
        {
            vector[i] = KramerMethod(final_mtrx, vector_answer, impact + 1, i);// считает правильно 
            vector[i] = round((vector[i]/det_final) * 100) / 100;


        }
           
        cout << endl;
   
        cout << "Таким образом итоговые значения искомых воздействий равны:" << endl;
        cout << endl;
    
        for (int i = 0;i < impact + 1;i++)
            cout << "a" << i <<"="<< vector[i] << endl;

        cout << "y = "<<vector[0]<<" ";
        for (int i = 1;i < impact + 1;i++)
        {
            if(vector[i]<0) cout<<" " << vector[i] << "(x" << i << ") ";
            else  cout << " +" << vector[i] << "(x" << i << ") ";
        }
         
        cout<< "Вывод строк с производными - ЭТО ВЕРШИНА ИНЖЕНЕРНОГО СЛОВА!!!";

    }
    else
        cout << "Исходная матрица вырожденая!" << endl;
}

void filling_matrix(float ptr[10][10] ,int row, int colum)
{
    cout << "Заполните массив:" << endl;
    for (int i = 0; i < row - 1; i++)
    {
        cout << "Значения воздействия " << i + 1 << endl;
        for (int y = 0; y < colum; y++)
            cin >> ptr[i][y];
    }

    cout << "Заполните Y экспериментальное:" << endl;
    for (int y = 0; y < colum; y++) 
    {
        cin >> ptr[row - 1][y];
        if (ptr[row - 1][y] == 0)
        {

            cout << "НЕЛЬЗЯ ИНИЦИАЛИЗИРОВАТЬ НУЛЕМ!!!!!" << endl;
            return;
        }

    }
    

}
void lineralaze(float ptr[10][10], int row, int colum)
{
    cout << endl;
    cout << "Линеаризация значений исходного уравнения:" << endl;
    cout << "y* = 1 / y; (xj)* = x^j" << endl;
    for (int i = 0;i < row - 1;i++)
    {
        for (int y = 0; y < colum; y++)
            ptr[i][y] = pow(ptr[i][y], i + 1);
    }
    for (int a = 0; a < colum; a++)
        ptr[row - 1][a] = round((1 / ptr[row - 1][a]) * 10) / 10;


    for (int y = 0; y < row;y++) // вывод 
    {
        cout << "=================================================" << endl;
        cout << "X" << y << "|" << "\t";
        for (int o = 0; o < colum; o++)
        {
            cout << ptr[y][o] << "\t" << "|" << "\t";

        }
        cout << endl;
    }
    cout << "=================================================" << endl;

}
void find_partial_derivative(float final_mtrx[10][10], float vector_answer[10], float ptr[10][10], int row,int row1)
{
    float res = 0, res1 = 0; // row = impact+1
    int index;

    for (int j = 0;j < row;j++) // для номера строк 
    {
        if (j == 0)// заполнение первой(нулевой строки)
        {
            for (int p = 0;p < row;p++) // для столбов в нулевой строке  row
            {
                if (p == 0) // arr[0][0]
                {
                    final_mtrx[j][p] = 2 * row1;

                }
                else if (p != 0) // arr[0][i]
                {
                    index = p - 1;
                    for (int o = 0; o < row1; o++)
                    {
                        //cout << res << "\t";
                        res += 2 * ptr[index][o];

                    }
                     res = (res * 100) / 100;
                    final_mtrx[0][p] = res;

                }
                res = 0;
                // 
            } // для столбов в нулевой строке КОНЕЦ!!!!!!
        }
        else//  для заполнения всех остольных строк
        {
            for (int i = 0;i < row;i++) // для столбов(заполняем всю строчку)
            {
                if (i == 0)  // нулевые элементы строк
                {
                    for (int o = 0; o < row1; o++)
                        res += 2 * ptr[j - 1][o];
                    res = res * 100 / 100;
                    final_mtrx[j][i] = res;

                    res = 0;
                }
                else if (i == j) // диагональные элементы матрицы
                {

                    for (int o = 0; o < row1; o++)
                        res += 2 * pow(ptr[j - 1][o], 2);
                    res = res * 100 / 100;
                    final_mtrx[j][i] = res;
                }
                else if (i != j && i!=0&& i!=1) // когда другие варики(Предусмотрел количество опытов >2)  j другие жлементы строки 
                {
                    for (int o = 0; o < row1; o++)
                        res += 2 * ptr[j][o] * ptr[j - 1][o];
                    res = res * 100 / 100;
                    final_mtrx[j][i] = res;
                }
                else if (i == 1 && i!=j) // j 
                {
                    for (int o = 0; o < row1; o++)
                        res += 2 * ptr[j - 1][o] * ptr[j - 2][o];
                    res = res * 100 / 100;
                    final_mtrx[j][i] = res;

                }
                res = 0;
            } // Конец заполнения j строки


        } // КОНЕЦ... для заполнения всех остольных строк

       // res = 0;
    } // конец заполнения выводного массива. Я УСТАЛ ПОМОГИТЕ МНЕ ЛЮДИ ДОБРЫЕ. У МЕНЯ БОЛЬШЕ НЕТ СИЛ!!!

    // Вектор ответов. Надо было писать на питоне...
    for (int h = 0;h < row;h++)
    {
        if (h == 0)
        {
            for (int o = 0;o < row1;o++)
            {
                if (ptr[h][o] < 0)  res1 += (-1) * 2 * ptr[row - 1][o]; // число было отриц. в формуле поменяет знак на плюс
                else if (ptr[h][o] > 0) res1 += 2 * ptr[row - 1][o];

            }
            if (res1 < 0) res1 *= -1;
            res1 = res1 * 100 / 100;
            vector_answer[h] = res1;
            res1 = 0;
        }
        else if (h != 0) // для остальных элементов. ТОже самое,но домножить на частную производную
        {
            for (int o = 0;o < row1;o++)
            {
                if (ptr[h][o] < 0)  res1 += (-1) * 2 * ptr[row - 1][o] * ptr[h - 1][o]; // число было отриц. в формуле поменяет знак на плюс
                else if (ptr[h][o] > 0) res1 += 2 * ptr[row - 1][o] * ptr[h - 1][o];

            }
            if (res1 < 0) res1 *= -1;
            res1 = res1 * 100 / 100;
            vector_answer[h] = res1;
            res1 = 0;
        }

    }

 

    // вывод 
    cout << endl;
    cout << "Матрица ответов" << endl;
    for (int y = 0; y < row;y++) // вывод 
    {
        cout << "=================================================================" << endl;
        cout << "dI/da" << y << "|" << "\t";
        for (int o = 0; o < row; o++)
        {
            cout << final_mtrx[y][o]<<"a"<<o<< "\t" << "|" << "\t";

        }
        cout <<"= " << vector_answer[y] << "\t" << "|" << endl;
    }
    cout << "=================================================================" << endl;
}
float determinant(float matrix[10][10], int n) {
    float det = 0; // свой дет передать
    float submatrix[10][10];
    if (n == 2)
        return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
    else {
        for (int x = 0; x < n; x++) {
            int subi = 0;
            for (int i = 1; i < n; i++) {
                int subj = 0;
                for (int j = 0; j < n; j++) {
                    if (j == x)
                        continue;
                    submatrix[subi][subj] = matrix[i][j];
                    subj++;
                }
                subi++;
            }
            det += (pow(-1, x) * matrix[0][x] * determinant(submatrix, n - 1));
        }
    }
    return det;
}
void subMatrix(float mat[10][10], float temp[10][10], int p, int q, int n)
{
    int i = 0, j = 0;
    // filling the sub matrix
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            // skipping if the current row or column is not equal to the current
            // element row and column
            if (row != p && col != q) {
                temp[i][j++] = mat[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}
float определитель_матрицы(float matrix[10][10], int n)
{
    int determinant = 0;
    if (n == 1) {
        return matrix[0][0];
    }
    if (n == 2) {
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
    }
    float temp[10][10], sign = 1;
    for (int i = 0; i < n; i++) {
        subMatrix(matrix, temp, 0, i, n);
        determinant += sign * matrix[0][i] * определитель_матрицы(temp, n - 1);
        sign = -sign;
    }
    return determinant;
}
float KramerMethod(float matriх[10][10], float vector [10], int row, int stolb)
{
    float mass[10][10];

    for (int kek1 = 0; kek1 < row;kek1++)
    {
        for (int lol = 0;lol < row;lol++)
            mass[kek1][lol] = matriх[kek1][lol];
    }

    for (int kek = 0; kek < row;kek++)
        mass[kek][stolb] = vector[kek];

    float answer = determinant(mass, row);
    return answer;
}

