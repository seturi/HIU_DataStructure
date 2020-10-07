#include "matrixb.h"

Matrix::Matrix(int a, int b, int c, int d, int e, int f, int g, int h, int i) {
    m[0][0] = a;
    m[0][1] = b;
    m[0][2] = c;
    m[1][0] = d;
    m[1][1] = e;
    m[1][2] = f;
    m[2][0] = g;
    m[2][1] = h;
    m[2][2] = i;
}
void Matrix::Transpose() {
    Matrix b(m[0][0], m[0][1], m[0][2], m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2]);   // 현재 행렬을 복사한 행렬

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            m[j][i] = b.m[i][j];
        }
    }
}
Matrix Matrix::operator+(const Matrix &a) {
    Matrix b;               // 연산 결과를 저장할 행렬

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            b.m[i][j] = m[i][j] + a.m[i][j];
        }
    }

    return b;
}
Matrix Matrix::operator-(const Matrix &a) {
    Matrix b;               // 연산 결과를 저장할 행렬

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            b.m[i][j] = m[i][j] - a.m[i][j];
        }
    }

    return b;
}
Matrix Matrix::operator*(const Matrix &a) {
    Matrix b;               // 연산 결과를 저장할 행렬

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                b.m[i][k] += (m[i][j] * a.m[j][i]);
            }
        }
    }

    return b;
}
void Matrix::operator=(const Matrix &a) {
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            m[i][j] = a.m[i][j];
        }
    }
}
void Matrix::ShowMatrix() {
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout.width(4);
            cout << left << m[i][j];
        }
        cout << endl;
    }
}
int Matrix::GetDet() {
    return (m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) + m[0][2] * (m[1][0]*m[2][1]-m[1][1] * m[2][0]));
}