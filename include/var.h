#ifndef VAR_H
#define VAR_H

#include <memory>
#include <map>

namespace dCpp
{

class var
{
    public:
        int order;
        double id;
        std::shared_ptr<std::map<var*, var> > dTau;

        var();
        var(double id);
        var(const var& other);
        var(var&& other);
        ~var();
        var& operator=(const var& v);
        var& operator=(var&& other);
        var reduce() const;
        void init(int order);
        var& to_lvalue();
        var d(var*dvar) const;
        void print() const;
        friend std::ostream& operator<<(std::ostream& os, const var& v);
        //declerations of algebraic operations
        var operator+(double n)const &;
        var operator+(double n) &&;
        var operator*(double n)const &;
        var operator*(double n) &&;
        var operator-(double n)const &;
        var operator-(double n) &&;
        var operator/(double n)const &;
        var operator/(double n) &&;
        var operator^(double n) const &;
        var operator^(double n) &&;
        var& operator+=(double n);
        var& operator*=(double n);
        var& operator-=(double n);
        var& operator/=(double n);
        var& operator^=(double n);
        var operator+(const var& v)const &;
        var operator+(const var& v) &&;
        var operator+(var&& v)const &;
        var operator+(var&& v) &&;
        var operator*(const var& v)const &;
        var operator*(const var& v) &&;
        var operator*(var&& v) &&;
        var operator*(var&& v)const &;
        var operator-(const var& v)const &;
        var operator-(const var& v) &&;
        var operator-(var&& v) &&;
        var operator-(var&& v)const &;
        var operator/(const var& v)const;
        var operator/(var&& v)const;
        var operator^(const var& v)const &;
        var operator^(const var& v) &&;
        var& operator+=(const var& v);
        var& operator+=(var&& v);
        var& operator*=(const var& v);
        var& operator-=(const var& v);
        var& operator-=(var&& v);
        var& operator/=(const var& v);
        var& operator/=(var&& v);
        var& operator^=(const var& v);
        //order logic
        bool operator==(const var& v)const;
        bool operator!=(const var& v)const;
        bool operator<(const var& v)const;
        bool operator<=(const var& v)const;
        bool operator>(const var& v)const;
        bool operator>=(const var& v)const;
};
}

#endif // VAR_H
