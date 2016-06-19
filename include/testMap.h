#ifndef TESTMAP_H
#define TESTMAP_H

typedef double (*func)(double);

class testMap
{
    public:
        testMap();
        testMap(func a, func b);
        virtual ~testMap();
    protected:
    private:
        func mapping;
        func primitive;

};

#endif // TESTMAP_H
