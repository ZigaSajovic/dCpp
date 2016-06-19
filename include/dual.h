#ifndef DUAL_H
#define DUAL_H
#include <map>
#include <iterator>

using namespace std;

class dual
{
    public:
        dual();
        dual(map<int, double> v);
        virtual ~dual();
        map<int, double>getVec();
    protected:
    private:
        map<int, double> vec;
};

#endif // DUAL_H
