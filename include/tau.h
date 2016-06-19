#ifndef TAU_H
#define TAU_H

class var;
typedef double (*funDouble)(double);

class tau
{
    public:
        tau();
        tau(funDouble mapping, funDouble primitive);
        ~tau();
        var operator()(const var&v);
    private:
        funDouble primitive;
        funDouble mapping;
};

#endif // TAU_H
