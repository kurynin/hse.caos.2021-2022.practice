#include <iostream>
#include <vector>

typedef void (*modifier)(int *);
extern "C" void foreach(int *arr, unsigned size, modifier p);

template<typename T>
std::ostream& operator<<(std::ostream& o, const std::vector<T> &v)
{
    for (auto &el : v)
        o << el << " ";
    return o;
}

void neg(int *p)
{
    *p = -*p;
}


int main()
{
    std::vector<int> v {1, 2, 3, 4, 5};
    auto size = static_cast<unsigned>(v.size());

    std::cout << v << std::endl;

    neg(&v[4]);
    std::cout << v << std::endl;

    foreach(&v[0], size, neg);
    std::cout << v << std::endl;

    return 0;
}
