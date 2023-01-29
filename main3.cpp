#include <iostream>

using namespace std;

// Rational Class declaration
class Rational {
   private:
      int numerator;
      int denominator; 
   public:
      Rational();
      explicit Rational(int n); 
      Rational(int n, int d); 
      Rational add(const Rational &a) const; 
      Rational subtract(const Rational &s) const; 
      Rational multiply(const Rational &m) const; 
      Rational divide(const Rational &d) const;
      void simplify();
      void display() const;
   private:
      int gcd(int n, int d) const;
};

// Implement Rational class member functions here
Rational::Rational() {
   numerator = 0;
   denominator = 1; 
}

Rational::Rational(int n) {
   numerator = n;
   denominator = 1;
}

Rational::Rational(int n, int d) {

    Rational Result;

    numerator = n;
    denominator = d;

    Result.numerator = n;
    Result.denominator = d;
}

Rational Rational::add(const Rational &a) const {
    Rational Result;

    Result.numerator = (a.numerator * denominator) + (a.denominator * numerator);
    Result.denominator = a.denominator * denominator;

    if (denominator != 0) {
      Result.simplify();
    }
    return Result;
}

Rational Rational::subtract(const Rational &s) const {
    Rational Result;

    Result.numerator = (s.denominator * numerator) - (s.numerator * denominator);
    Result.denominator = s.denominator * denominator;

    if (denominator != 0) {
        Result.simplify();
    }
    return Result;
}

Rational Rational::multiply(const Rational &m) const {
    Rational Result;

    Result.numerator = m.numerator * numerator;
    Result.denominator = m.denominator * denominator;

    if (denominator != 0) {
        Result.simplify();
    }
    return Result;
}

Rational Rational::divide(const Rational &d) const {
    Rational Result;

    Result.numerator = d.denominator * numerator; //To divide multiply by reciprocal
    Result.denominator = d.numerator * denominator;

    if (denominator != 0) {
        Result.simplify();
    }
    return Result;
}

int Rational::gcd(int n, int d) const {
   if (d == 0) {
      return n;
   }
   return gcd(d, n % d);
}

void Rational::simplify() {
   int result = gcd(numerator, denominator);
   
   numerator /= result;
   denominator /= result;
}

void Rational::display() const {

   cout << numerator << " / " << denominator;
}

// Do not change any of the code below this line!!

Rational getRational();
void displayResult(const string &, const Rational &, const Rational&, const Rational&);

int main() {
   Rational A, B, result;
   char choice;
   
   cout << "Enter Rational A:" << endl;
   A = getRational();
   cout << endl;
   
   cout << "Enter Rational B:" << endl;
   B = getRational();
   cout << endl;
   
   cout << "Enter Operation:" << endl
      << "a - Addition (A + B)" << endl
      << "s - Subtraction (A - B)" << endl
      << "m - Multiplication (A * B)" << endl
      << "d - Division (A / B)" << endl
      << "y - Simplify A" << endl;
   cin >> choice;
   cout << endl;
   
   if (choice == 'a') {
      result = A.add(B);
      displayResult("+", A, B, result);
   } else if (choice == 's') {
      result = A.subtract(B);
      displayResult("-", A, B, result);
   } else if (choice == 'm') {
      result = A.multiply(B);
      displayResult("*", A, B, result);
   } else if (choice == 'd') {
      result = A.divide(B);
      displayResult("/", A, B, result);
   } else if (choice == 'y') {
      A.simplify();
      A.display();
   } else {
      cout << "Unknown Operation";
   }
   cout << endl;
   
   return 0;
}


Rational getRational() {
   int choice;
   int numer, denom;
   
   cout << "Which Rational constructor? (Enter 2, 1, or 0)" << endl
      << "2 - 2 parameters (numerator & denominator)" << endl
      << "1 - 1 parameter (numerator)" << endl
      << "0 - 0 parameters (default)" << endl;
   cin >> choice;
   cout << endl;
   
   if (choice == 2) {
      cout << "numerator? ";
      cin >> numer;
      cout << endl;
      cout << "denominator? ";
      cin >> denom;
      cout << endl;
      return Rational(numer, denom);
   } else if (choice == 1) {
      cout << "numerator? ";
      cin >> numer;
      cout << endl;
      return Rational(numer);
   } else {
      return Rational();
   }
}

void displayResult(const string &op, const Rational &lhs, const Rational&rhs, const Rational &result) {
   cout << "(";
   lhs.display();
   cout << ") " << op << " (";
   rhs.display();
   cout << ") = (";
   result.display();
   cout << ")";
}

