#include <thread>
#include <cmath>
#include <iostream>
#include <vector>
#include <future>


bool is_prime(int val) {
    if (val == 1) {
        return false;
    }
    if (val == 2) {
        return true;
    }
    int val_sqrt = sqrt(val) + 1;
    for (int i = 2; i <= val_sqrt; ++i) {
        if (val % i == 0) {
            return false;
        }
    }
    return true;
}

void work(int start, int end, std::vector<std::promise<int>> &p) {
    size_t index = 0;

    for (int i = start; i < end; i++) {
        if (is_prime(i)) {
            p[index++].set_value(i);
            if (index == p.size()) {
                return;
            }
        }
    }

    try {
        throw end;
    } catch (...) {
        p[index].set_exception(std::current_exception());
    }
}


int main() {
    int start, end, n;
    std::cin >> start >> end >> n;

    std::vector<std::promise<int>> promises(n);

    std::thread t(work, start, end, std::ref(promises));

    for (auto &t: promises) {
        try {
            std::cout << t.get_future().get() << std::endl;
        } catch (int e) {
            std::cout << e << " - final" << std::endl;
            break;
        }
    }

    t.join();
}
