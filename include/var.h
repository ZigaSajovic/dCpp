#ifndef VAR_H
#define VAR_H
#include <map>
class var
{
    public:
        double real;
        std::map<int,double>* dual;

        var();
        var(const var& other);
        ~var();
        var(double n);
        void init();
        var operator*(double n)const;
        var operator+(double n)const;
        var operator-(double n)const;
        var operator/(double n)const;
        var operator*(const var& v)const;
        var operator/(const var& v)const;
        var operator+(const var& v)const;
        var operator-(const var& v)const;
        var operator^(double n) const;
        var operator-()const;
        var& operator=(const var& v);
        var& operator=(double n);
        var& operator+=(const var& v);
        var& operator-=(const var& v);
        var& operator*=(const var& v);
        var& operator/=(const var& v);
        var& operator*=(double n);
        var& operator/=(double n);
        var& operator+=(double n);
        var& operator-=(double n);
};
#endif // VAR_H
