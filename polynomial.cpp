#include "polynomial.h"
#include <iostream>
#include <math.h>


// Copy constructor
Polynomial::Polynomial(const Polynomial& source)
{
    terms = source.terms;
    capacity = source.capacity;
    termArray = new Term[terms];
    for(int i = 0; i < terms; i++)
        termArray[i] = source.termArray[i]; //deep copy
}

// Destructor
Polynomial::~Polynomial()
{
    delete[] termArray;
    terms = 0;
    capacity = 0;
    termArray = nullptr;    //initalize with nullptr
}


Polynomial& Polynomial::operator = (const Polynomial& source)
{

    if(this != &source)//when it's not same with the original
    {
        capacity = source.capacity;
        terms = source.terms;
        termArray = new Term[terms];
        for(int i = 0; i < terms; i++)
            termArray[i] = source.termArray[i]; //deep copy
    }
    return *this;   //return pointer value
}



// Sum of *this and source polynomials
Polynomial Polynomial::operator +(const Polynomial& source)
{
    Polynomial c;
    int A_index = 0;
    int B_index = 0;
    while(A_index <= terms && B_index <= terms)   //it works when the indexes are smaller than the terms
    {
        if(termArray[A_index].exp == source.termArray[B_index].exp) //when original termArray's exp is smae with the source.termArray's exp
        {
            float Coef_Sum = 0;
            Coef_Sum = termArray[A_index].coef + source.termArray[B_index].coef;    //add with coefficients
            if(Coef_Sum != 0)   //store in Polynomial c when coefficient is not 0
                c.CreateTerm(Coef_Sum, termArray[A_index].exp);
            
            A_index++;  // add 1 as A_index is used
            B_index++;  // add 1 as B_index is used
        }
        else if(termArray[A_index].exp > source.termArray[B_index].exp) //when termArray's exp is bigger than source.termArray.exp
        {
            c.CreateTerm(termArray[A_index].coef, termArray[A_index].exp);  //store termArray[A_index].coef and exp.
            A_index++;  //add 1 as only A_index is used.
        }
        else
        {
            c.CreateTerm(source.termArray[B_index].coef, source.termArray[B_index].exp);    //when termArray's exp is smaller than source.termArray.exp
            B_index++;//add 1 as only B_index is used.
        }
    }
    for(; A_index < terms; A_index++)   //add left termArray[A_index].coef and exp
        c.CreateTerm(termArray[A_index].coef, termArray[A_index].exp);
    for(; B_index < source.terms; B_index++)    //add left termArray[B_index].coef and exp
        c.CreateTerm(source.termArray[B_index].coef, source.termArray[B_index].exp);
    
    return c;
}

Polynomial Polynomial::operator - (const Polynomial& source)
{
    Polynomial c;
    int A_index = 0;
    int B_index = 0;
    while(A_index <= terms && B_index <= terms)   //it works when indexes are smaller or same with temrs.
    {
        if(termArray[A_index].exp == source.termArray[B_index].exp) //when termpArray's exp and source.termArray's exp is same.
        {
            float Coef_Sum = 0;
            Coef_Sum = termArray[A_index].coef - source.termArray[B_index].coef;  //subtract with coefficients
            if(Coef_Sum != 0) //store in Polynomial C when coefficient is not 0
                c.CreateTerm(Coef_Sum, termArray[A_index].exp);
            A_index++;  // add 1 as A_index is used.
            B_index++;  // add 1 as B_index is used.
        }
        else if(termArray[A_index].exp > source.termArray[B_index].exp) //when termArray's exp is bigger than source.termArray's exp.
        {
            c.CreateTerm(termArray[A_index].coef, termArray[A_index].exp);  //store termArray[A_index].coef and exp.
            A_index++;  //add 1 as A_index is used.
        }
        else    //when termArray's exp is smaller than source.termArray's exp.
        {
            c.CreateTerm((-1)*(source.termArray[B_index].coef), source.termArray[B_index].exp); //store after multiply -1 at source.termArray[B_index].coef. exp is same.
            B_index++;  //add 1 as B_index is used.
        }
    }
    for(; A_index < terms; A_index++)   //store left termArray values.
        c.CreateTerm(termArray[A_index].coef, termArray[A_index].exp);
    for(; B_index < source.terms; B_index++)    //store left termArray multiply -1
        c.CreateTerm((-1)*(source.termArray[B_index].coef), source.termArray[B_index].exp);
    return c;
    
}

Polynomial Polynomial::operator * (const Polynomial& source)
{
    Polynomial c;
    float c_coef = 0;// temporarily store Polynomial c's coef.
    int c_exp = 0;// temporarily store Polynomial c's exp.
    
    for(int i = 0; i < terms; i++)  // Outer Loop: Use double for loop to manipulate two polynomials.(1st loop)
    {
        for(int j = 0; j < source.terms; j++)   //Outer Loop: (2nd loop)
        {
            c_coef = termArray[i].coef * source.termArray[j].coef;
            c_exp = termArray[i].exp + source.termArray[j].exp;
            int same = -5;  //temporarily store the index of same exp with original polynomial. Initialize with negative number.
            for(int k = 0; k < c.terms; k++)    //Inner: compare already stored c.termArray[].exp with c_exp by using single for loop.
            {
                if(c.termArray[k].exp == c_exp) //if exp is same then add c.termArray[].coef at c_coef.
                    same = k;   //store same exp index at temporary variable.
            }
            if(same != -5)  //when same exp index is stored in variable "same".
            c.termArray[same].coef += c_coef;   //store after add to original polynomial's coef.
            else    //while variable "same" has not changed.
            c.CreateTerm(c_coef, c_exp);    //create new Term.
        }
    }
    
    return c;
}

bool Polynomial::operator == (const Polynomial& source)
{
    bool ret;
    ret = true;    //initialize return as true.
    
    if(terms != source.terms)   //first of all, if terms are different than return false.
    {
        ret = false;
        return ret;
    }
    else
    {
        for (int i = 0; i < terms; i++)
        {
            if(termArray[i].coef != source.termArray[i].coef)   //Using loop, return false if temrArray.coef and source.temrmArray.coef is different.
                {
                    ret = false;
                    return ret;
                }
        
            if(termArray[i].exp != source.termArray[i].exp)   //Using loop, return false if temrArray.exp and source.temrmArray.exp is different.
            {
                ret = false;
                return ret;
            }
        }
    ret = true;     //if all same then return true.
    return ret;
    }
}

float Polynomial::Eval(float x)
{
    float ret = 0;
    
    float pow_x = x;    //temporary value for using power.
    for(int i = 0; i < terms; i++)   //loop that loop indexes once.
    {
        if(termArray[i].exp == 0) //when exp is 0.
            ret += termArray[i].coef; //add coef to ret.
        else //when exp is not 0
        {
            for(int j = 0; j < termArray[i].exp - 1; j++) //we need to subtract 1
                x *= pow_x;
            ret += (termArray[i].coef * x); //multiply factor's involution at coef.
            x = pow_x;
        }
    }
    return ret;
}

// Compute derivative of the current polynomial
Polynomial Polynomial::Derivative()
{
    Polynomial c;
    
    for(int i = 0; i < terms; i++)  //Loop which loop indexes once.
    {
        if(termArray[i].exp != 0)    //when exp is not 0
        {
            termArray[i].coef *= termArray[i].exp;  //store coef * exp at termArray[i].coef
            termArray[i].exp -= 1;  //store exp subtract 1
            c.CreateTerm(termArray[i].coef, termArray[i].exp);
        }
    }
    return c;
}

void Polynomial::CreateTerm(const float coef, const int exp)
{
    
    if(terms == capacity)//if terms get bigger than origianl capacity then we should increase capacity and copy them to the new one.
    {
        capacity *= 2;  //doubling strategy
        Term *N_Term = new Term[capacity];
        for(int i = 0; i < terms; i++) // deliver copy value.
        {
            N_Term[i].coef = termArray[i].coef;
            N_Term[i].exp = termArray[i].exp;
        }
        delete[] termArray; //initialize termArray
        termArray = N_Term; //assign N_Term at termArray.
        
    }
    
    int same = -5;  //index which is used to find if there's any same exp. initialize with negative number.
    for(int i_exp = 0; i_exp < terms; i_exp++)
        if(termArray[i_exp].exp == exp) //if exp is same then store index at variable "same".
            same = i_exp;
    
    if(same == -5 && coef != 0 ) //store new if same has not changed and coef is not 0.
    {
        termArray[terms].coef = coef;
        termArray[terms].exp = exp;
    }
    else if(same != - 5)    //if exp is same then substitute index.coef. 
        termArray[same].coef = coef;
    
    for(int i = 0; i < terms; i++)//bubble sort
    {
        for(int j = 0; j < terms - i; j++)
        {
            if(termArray[j].exp < termArray[j+1].exp)
            {
                Term temp = termArray[j];
                termArray[j] = termArray[j+1];
                termArray[j+1] = temp;
            }
        }
    }
    terms++;
}

