#ifndef TAU_H
#define TAU_H

#include<var.h>
namespace dCpp{
    typedef var (*dTau)(const var&);
    typedef double(*mapping)(double);
    class tau
    {
        public:
            tau();
            tau(mapping func, dTau primitive);
            ~tau();
            var operator()(const var& v);
        private:
            dTau primitive;
            mapping func;
    };
}

#endif // TAU_H
