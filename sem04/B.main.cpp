#include <vector>
#include <iostream>
extern "C" int scan(const char *fmt, ...);

template<typename T>
std::ostream& operator<<(std::ostream& o, const std::vector<T> &v)
{
    for (auto &el : v)
        o << el << " ";
    return o;
}

int main() {
    std::vector<int> v(3);
    auto i = scan("ddd", &v[0], &v[1], &v[2]);

    std::cout << i << " -> " << v << std::endl;
    return 0;
}