#include <iostream>
using namespace std;
class rational
{
	int p, q;
	void reduce();
public:
	rational(int a = 0, int b = 1); //constructor - convertion int=>rational
	rational(double); // constructor - conversion double => rational
	rational operator+(rational&);
	friend rational operator-(rational&, rational&);
	rational operator*(rational&);
	friend rational operator/(rational&, rational&);
	rational operator++();
	friend rational operator--(rational&);
	int operator>(rational&);
	friend int operator<(rational&, rational&);
	operator int(); //conversion rational=>int
	operator double(); //conversion rational=>double
	friend ostream& operator<<(ostream&, rational&); // displaying a rational number
	friend istream& operator>>(istream&, rational&); // entering a rational number
};
void rational::reduce()
{
	int min, i, a, b;
	a = p > 0 ? p : -p;
	b = q > 0 ? q : -q;
	min = (a < b) ? a : b;
	for (i = 2; i <= min; i++)
		while ((a % i == 0) && (b % i == 0))
		{
			a /= i;
			b /= i;
			min /= i;
		}
	p = p > 0 ? a : -a;
	q = q > 0 ? b : -b;
}
rational::rational(int a, int b)
{
	if (b)
	{
		p = a;
		q = b;
		reduce();
	}
	else
	{
		cout << "\nIllegal value for q (q=0); 1 is given by default!";
		p = a;
		q = 1;
	}
}
rational::rational(double val)
{
	p = val * 100;
	q = 100;
	reduce();
}
rational rational::operator+(rational& r)
{
	rational aux;
	aux.p = p * r.q + q * r.p;
	aux.q = q * r.q;
	aux.reduce();
	return aux;
}
rational operator-(rational& a, rational& b)
{
	rational temp;
	temp.p = a.p * b.q - a.q * b.p;
	temp.q = a.q * b.q;
	temp.reduce();
	return temp;
}
rational rational::operator*(rational& r)
{
	rational aux;
	aux.p = p * r.p;
	aux.q = q * r.q;
	aux.reduce();
	return aux;
}
rational operator/(rational& r1, rational& r2)
{
	rational aux;
	aux.p = r1.p * r2.q;
	aux.q = r1.q * r2.p;
	aux.reduce();
	return aux;
}
rational rational::operator++()
{
	p += q;
	return *this;
}
rational operator--(rational& r)
{
	r.p -= r.q;
	return r;
}
int rational::operator>(rational& r)
{
	return (p * r.q > q * r.p);
}
int operator<(rational& r1, rational& r2)
{
	return (r1.p * r2.q < r1.q* r2.p);
}
rational::operator int()
{
	return p / q;
}
rational::operator double()
{
	return (double)p / q;
}
ostream& operator<<(ostream& str, rational& r)
{
	str << r.p << "/" << r.q;
	return str;
}
istream& operator>>(istream& str, rational& r)
{
	cout << "\np=";
	str >> r.p;
	do {
		cout << "q=";
		str >> r.q;
		if (r.q == 0) cout << "\ nIllegal value for q!";
	} while (r.q == 0);
	r.reduce();
	return str;
}
int main()
{
	rational a(15, 30), b(12, 16), c(2, 0), d;
	cout << "\na= " << a << endl;
	cout << "\nb= " << b << endl;
	cout << "\nc= " << c << endl;
	cout << "\nd= " << d << endl;
	cin.get();
	cout << "\nEnter the rational c:";
	cin >> c;
	cout << "\nc= " << c << endl;
	cin.get();
	d = a + b + c;
	cout << "d=a+b+c = " << d << endl;
	d = a - b;
	cout << "d=a-b = " << d << endl;
	d = a * b;
	cout << "d=a*b = " << d << endl;
	d = a / b;
	cout << "d=a/b = " << d << endl;
	d = ++a;
	cout << "d=++a = " << d << endl;
	d = --a;
	cout << "d=--a = " << d << endl;
	if (a > b)
		cout << "(" << a << ") > (" << b << ")";
	if (a < b)
		cout << "(" << a << ") < (" << b << ")";
	rational r = 1.5; // conversion from rational to double
	cout << "\nr= " << r << endl;
	double x = a; // conversion from double to rational
	cout << "\nx = " << x;
	cin.get();
	return 0;
}