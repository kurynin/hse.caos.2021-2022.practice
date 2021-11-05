#include <vector>
#include <iostream>

struct point
{
    int x, y, sum;
};

extern int sz;
extern point *arr;

extern "C"
void make_sum();

int main()
{
    int x, y;
    std::vector<point> vec;
    while (std::cin >> x >> y)
    {
        vec.push_back({x, y, 0});
    }

    sz = (int)vec.size();
    arr = &vec[0];
    make_sum(); // call make_sum

    for(auto & p: vec)
    {
        std::cout << "{ " << p.x << "; " << p.y << "; " << p.sum << " }" << std::endl;
    }

}