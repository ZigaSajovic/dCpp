#ifndef TAU_H
#define TAU_H

#include<var.h>
namespace dCpp
{
namespace internal
{
    typedef var (*dTau)(const var&);
    typedef double(*mapping)(double);
}

class tau
{
public:
    tau();
    tau(internal::mapping func, internal::dTau primitive);
    ~tau();
    var operator()(const var& v);
private:
    internal::dTau primitive;
    internal::mapping func;
};
}

#endif // TAU_H
