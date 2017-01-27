#ifndef VAR_H
#define VAR_H

#include <memory>
#include <map>

class var
{
    public:
    	int order;
        double id;
        std::shared_ptr<std::map<var*, var> > dTau;

        var();
        var(double id);
        var(const var& other);
        ~var();
        var& operator=(const var& v);
        var reduce() const;
        void init(int order);
        void initPlaceHolder(int order);
        var d(var*dvar);
        void print() const;
        //declerations of algebraic operations
        var operator+(double n)const;
        var operator*(double n)const;
        var operator-(double n)const;
        var operator/(double n)const;
        var operator^(double n) const;
        var& operator+=(double n);
        var& operator*=(double n);
        var& operator-=(double n);
        var& operator/=(double n);
        var& operator^=(double n);
        var operator+(const var& v)const;
        var operator*(const var& v)const;
        var operator-(const var& v)const;
        var operator/(const var& v)const;
        var operator^(const var& v)const;
        var& operator+=(const var& v);
        var& operator*=(const var& v);
        var& operator-=(const var& v);
        var& operator/=(const var& v);
        var& operator^=(const var& v);
        //order logic
        bool operator==(const var& v)const;
        bool operator!=(const var& v)const;
        bool operator<(const var& v)const;
        bool operator<=(const var& v)const;
        bool operator>(const var& v)const;
        bool operator>=(const var& v)const;
};

#endif // VAR_H
