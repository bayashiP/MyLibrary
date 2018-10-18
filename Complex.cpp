/********************************************************

 ********************************************************/
#include <string>
#include <cmath>
#include <iostream>
#include <sstream>
using namespace std;



/*####################################################################*/
/*    Class Definition    */

class Complex{
private:
  double _r,_i;  // _r = real part,  _i = imaginary part

public:
  Complex(double real, double img){ _r = real; _i = img; }
  Complex(const Complex& c)       { _r = c._r; _i = c._i; }


  /*    Functions    */

  //@function toString()
  string toString(){
    stringstream ss;
    // Add real part to string
    if( _r != 0 ){ ss << noshowpoint << _r; }

    //Add imaginary part to string
    if( _i != 0 ){
      if( _i > 0 && _r!=0 )ss << "+";
      ss << noshowpoint << _i << "i";
    }
    
    return ss.str();
  }
  //@end toString()

  double real()     { return _r; }
  double imaginary(){ return _i; }

  
  /*    Member Operators    */
  //Unary Complement/Plus/Negation
  Complex operator~() const { Complex c(_r,-_i); return c; }
  Complex operator+() const { Complex c(_r, _i); return c; }
  Complex operator-() const { Complex c(-_r,-_i);return c; }


  //Assignment
  Complex& operator=(const Complex& c){
    _r = c._r;
    _i = c._i;
    return *this;
  }

  
  //Compound Assignment
  Complex& operator+=(const Complex& c){
    _r += c._r;
    _i += c._i;
    return *this;
  }
  Complex& operator-=(const Complex& c){
    _r -= c._r;
    _i -= c._i;
    return *this;
  }
  Complex operator*=(const Complex& c){
    //(a+bi)*(c+di) = (ac-bd)+(ad+bc)i
    _r = (_r*c._r - _i*c._i);
    _i = (_r*c._i + _i*c._r);
    return *this;
  }
  Complex operator/=(const Complex& c){
    _r = (_r*c._r + _i*c._i) / (c._r*c._r + c._i*c._i);
    _i = (c._r*_i - _r*c._i) / (c._r*c._r + c._i*c._i);
    return *this;
  }


  /*    friend functions    */
  friend bool operator==( const Complex& c1,  const Complex& c2);
  
};
//@end class Complex





/*####################################################################*/
/*    Operators    */
//Arithmetic Operators
Complex operator+(const Complex& c1, const Complex& c2){
  return Complex(c1) += c2;
}
Complex operator-(const Complex& c1, const Complex& c2){
  return Complex(c1) -= c2;
}
Complex operator*(const Complex& c1, const Complex& c2){
  return Complex(c1) *= c2;
}
Complex operator/(const Complex& c1, const Complex& c2){
  return Complex(c1) /= c2;
}

//Comparison Operators
bool operator==(const Complex& c1, const Complex& c2){
  return (c1._r == c2._r) && (c1._i == c2._i);
}
bool operator!=(const Complex& c1, const Complex& c2){
  return !(c1==c2);
}



//ostream operator
ostream& operator<<(ostream& os, Complex c){
  os  << c.toString();
  return os;
}





/*####################################################################*/
/*    Other Functions    */
double abs(Complex c){
  return sqrt(c.real()*c.real() + c.imaginary()*c.imaginary());
}

/*####################################################################*/
/*    main() for test    */


#ifdef DEBUG_COMPLEX

int main(){

  const string separator="#######################################";
  
  Complex a(4,3), b(4,2);
  
  cout << "Original:" << endl;
  cout << "a = " << a << endl;
  cout << "b = " << b << endl;
  cout << separator << endl;
  cout << "a+b = " << a+b << endl;
  cout << "a-b = " << a-b << endl;
  cout << "a*b = " << a*b << endl;
  cout << "a/b = " << a/b << endl;
  cout << separator << endl;
  cout << "-a = " << -a << endl;
  cout << "~a = " << ~a << endl;
  cout << "|a|= " << abs(a) << endl;
  cout << separator << endl; 
  cout << a<<"=="<<b<<" ? : " << (a==b) << endl;
  a = b;
  cout << a<<"=="<<b<<" ? : " << (a==b) << endl;
  
  return 0;
}

#endif
