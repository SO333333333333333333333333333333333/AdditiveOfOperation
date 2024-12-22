#include <stdio.h>

#define MaxR 3
#define MaxC 200
int NumC1 = 2;
int NumC2 = 0;

void PrintS(int a[MaxR][MaxC])//置換aを表示
{
    int i;
    for (i = 0; i < a[NumC1][NumC2]; i++)
        printf("%3d ", a[0][i]);
    printf("\n");
    for (i = 0; i < a[NumC1][NumC2]; i++)
        printf("%3d ", a[1][i]);
    printf("\n");
    printf("%3d\n\n", a[NumC1][NumC2]);
}

void Subs(int b[MaxR][MaxC], int a[MaxR][MaxC])//置換bに置換aを代入
{
    int i;
    for (i = 0; i < a[NumC1][NumC2]; i++)
        b[0][i] = a[0][i];
    for (i = 0; i < a[NumC1][NumC2]; i++)
        b[1][i] = a[1][i];
    b[NumC1][NumC2] = a[NumC1][NumC2];
}

void ActSucc(int R[MaxR][MaxC], int a[MaxR][MaxC])//R = Succ◦a◦Succ⁻¹
{
    int i;
    for (i = 0; i < a[NumC1][NumC2]; i++)
        R[0][i] = a[0][i]+1;
    for (i = 0; i < a[NumC1][NumC2]; i++)
        R[1][i] = a[1][i]+1;
    R[NumC1][NumC2] = a[NumC1][NumC2];
}

void Inv(int R[MaxR][MaxC], int a[MaxR][MaxC])// R = a⁻¹
{
    int i;
    for (i = 0; i < a[NumC1][NumC2]; i++)
        R[0][i] = a[1][i];
    for (i = 0; i < a[NumC1][NumC2]; i++)
        R[1][i] = a[0][i];
    R[NumC1][NumC2] = a[NumC1][NumC2];
}

void CyclicProd(int R[MaxR][MaxC], int b[MaxR][MaxC], int a[MaxR][MaxC]) //巡回置換の積 R = b◦a
{
    int i, j;
    int k = a[NumC1][NumC2];
    for (i = 0; i < a[NumC1][NumC2]; i++)
    {
        int Cond = 1;
        for (j = 0; j < b[NumC1][NumC2]; j++)
        {
            if (a[1][i] == b[0][j])
            {
                //printf("%d, %d, %d, %d\n", a[0][i], a[1][i], b[0][j], b[1][j]);
                R[0][i] = a[0][i];
                R[1][i] = b[1][j];
                Cond = 0;
                //printf("%d, %d\n", R[0][i], R[1][i]);
            }
        }
        if (Cond == 1)
        {
            R[0][i] = a[0][i];
            R[1][i] = a[1][i];
            //printf("%d, %d\n", R[0][i], R[1][i]);
        }
    }
    for (i = 0; i < b[NumC1][NumC2]; i++)
    {
        int Cond = 1;
        for (j = 0; j < a[NumC1][NumC2]; j++)
        {
            if (b[0][i] == a[0][j])
            {
                Cond = 0;
            }
        }
        if (Cond == 1)
        {
            R[0][k] = b[0][i];
            R[1][k] = b[1][i];
            //printf("%d, %d\n", R[0][k], R[1][k]);
            k++;
        }
    }
    R[NumC1][NumC2] = k;
}

void Sort(int R[MaxR][MaxC])//上の数を昇順にソート
{
    int i, j;
    int temp[2][1];
    for (i = 0; i+1 < R[NumC1][NumC2]; i++)
    {
        for(j = i; j < R[NumC1][NumC2]; j++)
        {
            if (R[0][i] > R[0][j])
            {
                temp[0][0] = R[0][i];
                temp[1][0] = R[1][i];
                R[0][i] = R[0][j];
                R[1][i] = R[1][j];
                R[0][j] = temp[0][0];
                R[1][j] = temp[1][0];
            }
        }
    }
}

void AdditiveOf(int R[MaxR][MaxC], int a[MaxR][MaxC])
{
    int temp1[MaxR][MaxC];
    int temp2[MaxR][MaxC];
    Inv(temp1, a);
    ActSucc(temp2, temp1);
    CyclicProd(R, a, temp2);
}

void RightSucc(int R[MaxR][MaxC])//R = a◦Succ
{
    int i;
    for (i = 0; i < R[NumC1][NumC2]; i++)
        R[0][i] = R[0][i]-1;
}

int main(void)
{
    int a[MaxR][MaxC] =
    {
        {2, 3, 4, 5, 6, 7},//a◦Succ(n) = 5☆n ただし何もない部分はそのままであることを表す
        {5, 2, 3, 4, 7, 6}
    };
    a[NumC1][NumC2] = 6;//行列aの列の数は6
    int b[MaxR][MaxC];
    int i;
    for (i = 0; i < 100; i++)//100回additiveをとるのを繰り返している
    {
        AdditiveOf(b, a);
        Subs(a, b);
    }
    RightSucc(b);
    Sort(b);
    PrintS(b);//b(n) = 5☆⁽⁻¹⁰⁰⁾n ただし何もない部分は+1することを表す
    return 0;
}
