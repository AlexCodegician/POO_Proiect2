//
//  main.cpp
//  poo2
//
//  Created by Alex Barbu on 04/04/2021.
//  Copyright © 2021 Alex Barbu. All rights reserved.
//
#include <iostream>
#include <math.h>
using namespace std;
class Complex
{
    float re, im;
    friend class Matrice;
public:
    Complex();
    Complex(float re, float im);
    friend istream& operator >> (istream &in, Complex &c);
    friend ostream& operator <<(ostream &out, const Complex &c);
    Complex (const Complex &c);
    Complex& operator=(const Complex &c);
    Complex operator+(const Complex &c);
    Complex operator-(const Complex &c);
    Complex operator*(const Complex &c);
    Complex operator*(const double nr);
    Complex operator/(const Complex &c);
    bool operator == (const Complex &c);
    virtual ~Complex(){}
};
Complex::Complex(): re(0),im(0) {}
Complex::Complex(float re, float im): re(re), im(im) {}
istream& operator >> (istream &in, Complex &c)
{
    in >> c.re >> c.im;
    return in;
}
ostream& operator <<(ostream &out, const Complex &c){
    out << c.re << "+" << c.im << "i ";
    return out;
}
Complex::Complex(const Complex &c)
{
    re=c.re;
    im=c.im;
}
Complex& Complex::operator=(const Complex &c)
{
    if (this==&c)
        return *this;
    this->re=c.re;
    this->im=c.im;
    return *this;
}
Complex Complex::operator+(const Complex &c)
{
    Complex rez;
    rez.re=re+c.re;
    rez.im=im+c.im;
    return rez;
}
Complex Complex::operator-(const Complex &c)
{
    Complex rez;
    rez.re=re-c.re;
    rez.im=im-c.im;
    return rez;
}
Complex Complex::operator*(const Complex &c)
{
    Complex rez;
    rez.re=re*c.re-im*c.im;
    rez.im=re*c.im+c.re*im;
    return rez;
}
Complex Complex::operator*(const double nr)
{
    Complex rez;
    rez.re = nr * re;
    rez.im = nr * im;
    return rez;
}
Complex Complex::operator/(const Complex &c)
{
    Complex rez;
    if (c.re==0 && c.im==0)
    {
        cout << "NU e posibila impartirea la 0" << '\n';
        return rez;
    }
    rez.re=(((re)*(c.re))+((im)*(c.im)))/(pow(c.re,2)+pow(c.im,2));
    rez.im=(((c.re)*(im))-((re)*(c.im)))/(pow(c.re,2)+pow(c.im,2));
    return rez;
}
bool Complex::operator ==(const Complex &c)
{
    if (re==c.re && im==c.im)
        return true;
    return false;
}
class Matrice
{
protected:
    static int nrMatriceDeclarate;
    Complex **matrix;
    int lin, col;
public:
    static int GetNrMatriceDeclarate(){
        return nrMatriceDeclarate;
    }
    Matrice();
    Matrice(int lin,int col);
    friend istream& operator >>(istream &in, Matrice &m);
    friend ostream& operator <<(ostream &out, const Matrice &m);
    Matrice& operator=(const Matrice &m);
    Matrice operator+(const Matrice &m);
    Matrice operator-(const Matrice &m);
    Matrice operator*(const Matrice &m);
    virtual Complex determinant(const Matrice &m,int n){cout<<"am intrat in baza";Complex zero; return zero;};
    virtual bool verificaDiagonala(){return 0;};
    int getLin() {return this->lin;}
    ~Matrice(){};
};
Matrice::Matrice(): lin(0), col(0)
{
    nrMatriceDeclarate++;
    matrix=new Complex*[0];
}
Matrice::Matrice(int lin,int col): lin(lin), col(col)
{
    nrMatriceDeclarate++;
    matrix=new Complex*[lin];
    for (int i=0;i<lin;i++)
    {
        matrix[i]=new Complex[col];
        for (int j=0;j<col;j++)
        {
            Complex zero;
            matrix[i][j]=zero;
        }
    }
}
istream& operator >>(istream &in, Matrice &m)
{
    cout<<"Cititi o matrice cu " << m.lin <<" linii si " << m.col << " coloane" << '\n';
    for (int i=0;i<m.lin;i++)
    {
        for (int j=0;j<m.col;j++)
        {
            in >> m.matrix[i][j];
        }
    }
    return in;
}
ostream& operator <<(ostream &out, const Matrice &m)
{
    for (int i=0;i<m.lin;i++)
    {
        for (int j=0;j<m.col;j++)
        {
            out << m.matrix[i][j] << " ";
        }
        out << '\n';
    }
    return out;
}
Matrice& Matrice::operator=(const Matrice& m)
{
    if (this==&m)
        return *this;
    this->lin=m.lin;
    this->col=m.col;
    matrix=new Complex*[lin];
    for (int i=0;i<lin;i++)
    {
        matrix[i]=new Complex[col];
    }
    for (int i=0;i<this->lin;i++)
    {
        for (int j=0;j<this->col;j++)
        {
            this->matrix[i][j]=m.matrix[i][j];
        }
    }
    return *this;
}
Matrice Matrice::operator+(const Matrice &m)
{
    Matrice rez(lin,col);
    for (int i=0;i<lin;i++)
    {
        for (int j=0;j<col;j++)
        {
            rez.matrix[i][j]=matrix[i][j]+m.matrix[i][j];
        }
    }
    return rez;
}
Matrice Matrice::operator-(const Matrice &m)
{
    Matrice rez(m.lin,m.col);
    for (int i=0;i<m.lin;i++)
    {
        for (int j=0;j<m.col;j++)
        {
            rez.matrix[i][j]=matrix[i][j]-m.matrix[i][j];
        }
    }
    return rez;
}
Matrice Matrice::operator*(const Matrice &m)
{
    Matrice rez(lin,m.col);
    for (int i=0;i<lin;i++)
    {
        for (int j=0;j<m.col;j++)
        {
            for (int k=0;k<m.col;k++)
            {
                rez.matrix[i][j]=rez.matrix[i][j]+matrix[i][k]*m.matrix[k][j];
            }
        }
    }
    return rez;
}
 
class Matrice_oarecare: public Matrice
{
public:
    Matrice_oarecare();
    Matrice_oarecare(int lin, int col);
    ~Matrice_oarecare(){};
};
Matrice_oarecare::Matrice_oarecare(): Matrice() {}
Matrice_oarecare::Matrice_oarecare(int lin,int col): Matrice(lin,col) {}
 
class Matrice_patratica : public Matrice
{
public:
    Matrice_patratica():Matrice(){}
    Matrice_patratica(int lin): Matrice(lin,lin) {}
    Complex determinant(const Matrice &m, int n);
    bool verificaDiagonala();
    ~Matrice_patratica(){};
};
 
Complex Matrice_patratica::determinant(const Matrice &m, int n)
{
    Complex det;
    Matrice_patratica submatrix(n);
    if (n==2){
        return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
    }
    else
    {
        for (int x=0;x<n;x++)
        {
            int subi=0;
            for (int i=1;i<n;i++)
            {
                int subj=0;
                for (int j=0;j<n;j++)
                {
                    if (j==x)
                        continue;
                    submatrix.matrix[subi][subj] = matrix[i][j];
                    subj++;
                }
                subi++;
            }
            det=det+(matrix[0][x]*determinant(submatrix,n-1)*pow(-1,x));
        }
    }
    return det;
}
bool Matrice_patratica::verificaDiagonala()
{
    Complex zero;
    for(int i=0;i<lin;i++)
    {
        for(int j=0;j<lin;j++)
        {
            if (i!=j && !(matrix[i][j]==zero))
                return false;
        }
    }
    return true;
}
int Matrice::nrMatriceDeclarate = 0;
int main()
{
    int n;
    cout<<"Cititi numarul de matrice din vector: ";
    cin>>n;
    Matrice **vectorDeMatrice = new Matrice*[n];
    for(int i=0;i<n;i++)
    {
        cout<<"Cititi numarul de linii: ";
        int linii;
        cin>>linii;
        cout<<"Cititi numarul de coloane: ";
        int coloane;
        cin>>coloane;
        if(linii>0 && coloane>0)
        {
            int comanda;
            cout << "Introduceti comanda: \n";
            cout << "Comanda 1. Verificarea faptului ca matricea introdusa este matrice diagonala \n";
            cout << "Comanda 2. Calculul determinantului \n";
            cin >> comanda;
            if (comanda==1)
            {
                if(linii==coloane)
                {
                    vectorDeMatrice[i] = new Matrice_patratica(linii);
                    cin>>(*vectorDeMatrice[i]);
                    cout<<(*vectorDeMatrice[i]).verificaDiagonala() << '\n';
                }
                else
                    cout << "Matricea nu are diagonala principala \n";
            }
            else if (comanda==2)
            {
                if (linii==coloane)
                {
                    vectorDeMatrice[i] = new Matrice_patratica(linii);
                    cin>>(*vectorDeMatrice[i]);
                    cout<<(*vectorDeMatrice[i]).determinant(*vectorDeMatrice[i], linii) << '\n';
                }
                else
                    cout << "Nu poate fi calculat determinantul \n";
            }
        }
        else
            cout<<"Ati introdus niste date invalide pentru matricea curenta \n";
    }
}
