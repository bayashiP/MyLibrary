/******************************************************************************

                              .

*******************************************************************************/

#include <iostream>
#include <string>
#include <cmath>
#include <climits>
using namespace std;

#define DEBUG_FRACTION

int gcd(int a, int b)  
{  
    a=abs(a); b=abs(b);
    if (a == 0 || b == 0)  
        return 0;  
    if (a == b)  
        return a;  
    if (a > b)  
        return gcd(a-b, b);  
    return gcd(a, b-a);  
}  
  
// Function to return LCM of two numbers  
int lcm(int a, int b)  
{  
    a=abs(a); b=abs(b);
    return (a*b)/gcd(a, b);  
}  
  
/*####################################################################*/
/*    Class Definition     */

class Fraction{
private:
    int num,den; //num/den
    
    void reduction(){ 
        int tmp=gcd(num,den); 
        if(tmp!=0){
            num/=tmp; den/=tmp; 
        }
        else{
            num=den=0;
        }
    }

public:
    //Constructor
    /*
    *    - Denominator must be greater than 0
    */
    Fraction(int n,int d){
        num=n; 
        den=d;
        if(den<0){ den*=-1; num*=-1; }
        reduction();
    }
    Fraction(const Fraction& f){
        num = f.num;
        den = f.den;
    }

    
    //Functions to access the number
    double toDouble(){ 
        if(den!=0) return num/den; 
        else       return INT_MAX*(num/abs(num));
    }
    string toString(){ 
        if(den==1 || den==0) return to_string(num);
        else                 return to_string(num)+"/"+to_string(den); 
    }
    
    
    
    
    /*    Operators     */
    //Assignment
    Fraction& operator=(const Fraction& f) {
        num = f.num;
        den = f.den;    //reduction has been done in 'f' 
        return *this;
    }  
    
    //Compound Assignment
    //Fraction + Fraction
    Fraction& operator+=(const Fraction& f){
        int newden=lcm(den , f.den);
        int newnum=num*(newden/den) + f.num*(newden/f.den);
        den=newden; num=newnum;
        reduction();
        return *this;
    }
    Fraction& operator-=(const Fraction& f){
        int newden=lcm(den , f.den);
        int newnum=num*(newden/den) - f.num*(newden/f.den);
        den=newden; num=newnum;
        reduction();
        return *this;
    }
    Fraction& operator*=(const Fraction& f){
        num  *= f.num;
        den  *= f.den;
        reduction();
        return *this;
    }
    Fraction& operator/=(const Fraction& f){
        num  *= f.den;
        den  *= f.num;
        if(den<0){ den*=-1; num*=-1; }
        reduction();
        return *this;
    }
    //Fraction + Integer
    Fraction& operator+=(const int& i){
        num+= i*den;
        reduction();
        return *this;
    }
    Fraction& operator-=(const int& i){
        num-= i*den;
        reduction();
        return *this;
    }
    Fraction& operator*=(const int& i){
        num *= i;
        reduction();
        return *this;
    }
    Fraction& operator/=(const int& i){
        den *= i;
        if(den<0){ den*=-1; num*=-1; }
        reduction();
        return *this;
    }
    

    //Unary Negation/Plus
    Fraction operator+() const { Fraction f(+num,den); return f; }
    Fraction operator-() const { Fraction f(-num,den); return f; }
    
    
    //friend functions
    friend bool operator<( const Fraction& f1,  const Fraction& f2);
    friend bool operator==( const Fraction& f1,  const Fraction& f2);
    friend Fraction abs(Fraction f);

};




/*####################################################################*/
/*    Operators     */

//Arithmetic Operators
//Fraction + Fraction
Fraction operator+( const Fraction& f1, const Fraction& f2){
    return Fraction(f1)+=f2;
}
Fraction operator-( const Fraction& f1,  const Fraction& f2){
    return Fraction(f1)-=f2;
}
Fraction operator*( const Fraction& f1,  const Fraction& f2){
    return Fraction(f1)*=f2;
}
Fraction operator/( const Fraction& f1,  const Fraction& f2){
    return Fraction(f1)/=f2;
}
//Fraction + Integer
Fraction operator+( const Fraction& f1,  const int i){
    return Fraction(f1)+=i;
}
Fraction operator-( const Fraction& f1,  const int i){
    return Fraction(f1)-=i;
}
Fraction operator*( const Fraction& f1,  const int i){
    return Fraction(f1)*=i;
}
Fraction operator/( const Fraction& f1,  const int i){
    return Fraction(f1)/=i;
}


//Comparison Operators
bool operator<( const Fraction& f1,  const Fraction& f2){
    int newden=lcm(f1.den , f2.den);
    int n1=f1.num*(newden/f1.den);
    int n2=f2.num*(newden/f2.den);
    return n1 < n2;
}
bool operator>( const Fraction& f1, const Fraction& f2){
    return f2 < f1;
}
bool operator<=( const Fraction& f1,  const Fraction& f2){
    return !(f1>f2);
}
bool operator>=( const Fraction& f1,  const Fraction& f2){
    return !(f1<f2);
}
bool operator==( const Fraction& f1,  const Fraction& f2){
    return (f1.den==f2.den && f1.num==f2.num);
}
bool operator!=( const Fraction& f1,  const Fraction& f2){
    return !(f1==f2);
}



//ostream Operator
ostream& operator<<(ostream& os, Fraction f){
    os << f.toString();
    return os;
}


/*####################################################################*/
/*       Functions        */
Fraction abs(Fraction f){
    Fraction tmp( abs(f.num) , f.den );
    return tmp;
}






/*####################################################################*/





#ifdef DEBUG_FRACTION

int main()
{
    Fraction a(1,100);
    Fraction b(-1,200); 
    
    cout << "Before: " << a << " , " << b << endl;

    cout << "a+b = " << a+b << endl;
    cout << "a-b = " << a-b << endl;
    cout << "a*b = " << a*b << endl;
    cout << "a/b = " << a/b << endl;
    cout << "a+3 = " << a+3 << endl;
    return 0;
}

#endif










