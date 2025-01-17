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
    printf("(%dcolumns)\n\n", a[NumC1][NumC2]);
}

void Sort(int R[MaxR][MaxC])//置換の上行の数を昇順にソート
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

void Subs(int b[MaxR][MaxC], int a[MaxR][MaxC])//置換bに置換aを代入
{
    int i;
    for (i = 0; i < a[NumC1][NumC2]; i++)
        b[0][i] = a[0][i];
    for (i = 0; i < a[NumC1][NumC2]; i++)
        b[1][i] = a[1][i];
    b[NumC1][NumC2] = a[NumC1][NumC2];
}

/*
入力する置換は1からnの間を省略せず
  1    2    3  …   n 
a(1) a(2) a(3) … a(n)
の形にしてください
戻り値は置換とは限らないので常に繰り返し適用できるわけではないです
*/
void MultiplicativeOf(int A[MaxR][MaxC])//↖に詳細 n↦A(n) = n↦A⁽¹⁾(n) すなわち n↦Aⁿ(1)
{
    int i, j;
    int temp[A[NumC1][NumC2]];
    temp[0] = A[1][0];
    for (i = 1; i < A[NumC1][NumC2]; i++)
    {
        int Cond = 1;
        for (j = 0; j < A[NumC1][NumC2] && Cond == 1; j++)
        {
            if (temp[i-1] == A[0][j])
            {
                temp[i] = A[1][j];
                Cond = 0;
            }
        }
        if (Cond == 1)
        {
            temp[i] = temp[i-1]+1;
        }
    }
    for (i = 0; i < A[NumC1][NumC2]; i++)
    {
        A[1][i] = temp[i];
    }
}

void ActSuccInv(int a[MaxR][MaxC])//a = a^(Succ⁻¹) = Succ◦a◦Succ⁻¹
{
    int i;
    for (i = 0; i < a[NumC1][NumC2]; i++)
        a[0][i]++;
    for (i = 0; i < a[NumC1][NumC2]; i++)
        a[1][i]++;
}

void Inv(int a[MaxR][MaxC])// a = a⁻¹
{
    int i, temp;
    for (i = 0; i < a[NumC1][NumC2]; i++)
    {
        temp = a[0][i];
        a[0][i] = a[1][i];
        a[1][i] = temp;
    }
}

void CyclicProd(int b[MaxR][MaxC], int a[MaxR][MaxC])//置換の積 a = b◦a、ただしaおよびbは変化する部分が有限な置換
{
    int i, j;
    int k = a[NumC1][NumC2];
    for (i = 0; i < a[NumC1][NumC2]; i++)
    {
        int Cond = 1;
        for (j = 0; j < b[NumC1][NumC2] && Cond == 1; j++)
        {
            if (a[1][i] == b[0][j])
            {
                //printf("%d, %d, %d, %d\n", a[0][i], a[1][i], b[0][j], b[1][j]);
                a[1][i] = b[1][j];
                Cond = 0;
                //printf("置き換えた、%d, %d\n", a[0][i], a[1][i]);
            }
        }
        if (Cond == 1)
        {
            //printf("置き換えなかった、%d, %d\n", a[0][i], a[1][i]);
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
            a[0][k] = b[0][i];
            a[1][k] = b[1][i];
            //printf("追加した、%d, %d\n", a[0][k], a[1][k]);
            k++;
        }
    }
    a[NumC1][NumC2] = k;
}

void PreAdditiveOf(int a[MaxR][MaxC])//a = a◦Succ◦a◦Succ⁻¹
{
    int temp[MaxR][MaxC];
    Subs(temp, a);
    Inv(a);
    ActSuccInv(a);
    CyclicProd(temp, a);
}

void RightSuccInv(int a[MaxR][MaxC])//a = a◦Succ⁻¹
{
    int i;
    for (i = 0; i < a[NumC1][NumC2]; i++)
        a[0][i]++;
}

void RightSucc(int a[MaxR][MaxC])//a = a◦Succ
{
    int i;
    for (i = 0; i < a[NumC1][NumC2]; i++)
        a[0][i]--;
}

void AdditiveOf(int r, int A[MaxR][MaxC])//A = A⁽⁻ʳ⁾
{
    RightSuccInv(A);
    int i;
    for (i = 0; i < r; i++)
        PreAdditiveOf(A);
    RightSucc(A);
}

int main(void)
{
    int A[MaxR][MaxC] =
    {
        {1, 2, 3, 4, 5, 6},//A(n) = 5☆n ただし何もない部分は+1することを表す
        {5, 2, 3, 4, 7, 6}
    };
    A[NumC1][NumC2] = 6;//行列Aの列の数
    PrintS(A);//A(n) = 5☆n ただし何もない部分は+1することを表す
    AdditiveOf(1, A);
    Sort(A);
    PrintS(A);//A(n) = 5☆⁽⁻¹⁾n
    MultiplicativeOf(A);
    PrintS(A);//A(n) = 5☆n
    MultiplicativeOf(A);
    PrintS(A);//A(n) = 5+n
    int A2[MaxR][MaxC] =
    {
        {1, 2, 3, 4, 5, 6},//A(n) = 5☆n
        {5, 2, 3, 4, 7, 6}
    };
    A2[NumC1][NumC2] = 6;//行列Aの列の数
    AdditiveOf(100, A2);
    Sort(A2);
    PrintS(A2);//A(n) = 5☆⁽⁻¹⁰⁰⁾n
    return 0;
}
