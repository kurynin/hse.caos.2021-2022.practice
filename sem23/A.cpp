// ### A

// В аргументах командной строки передается N >= 1.

// Следует породить N нитей, каждая из которых считывает со стандартного входа
// натуральное число Ki и находит Ki простое число, печатает его, и цикл повторяется.
// Если на стандартном потоке данных нет, то нити должны завершить свое выполнение.

#include <thread>
#include <utility>
#include <iostream>
#include <cmath>
#include <vector>
#include <mutex>


bool is_prime(int val) {
    if (val == 1) {
        return false;
    }
    if (val == 2) {
        return true;
    }
    int val_sqrt = std::sqrt(val) + 1;
    for (int i = 2; i <= val_sqrt; ++i) {
        if (val % i == 0) {
            return false;
        }
    }
    return true;
}


void work(std::mutex &m) {
    int val;
    auto f = [&m, &val]() -> bool {
        std::lock_guard<decltype(m)> lock(m); // Так под c++11 & 14
        //std::lock_guard lock(m);// Так можно под c++17
        return static_cast<bool>(std::cin >> val);
    };
    while (f()) {
        int count = 0;
        int cur = 1;
        while (count != val) {
            if (is_prime(cur)) {
                ++count;
            }
            ++cur;
        }
        std::lock_guard<std::mutex> lock(m);
        std::cout <<  cur - 1 << std::endl;
    }
}

int main(int argc, char** argv) {
    size_t n = atoi(argv[1]);
    std::mutex m;

    std::vector<std::thread> threads{n};

    for (auto &t : threads) {
        t = std::thread(work, std::ref(m));
    }

    for (auto &t : threads) {
        t.join();
    }

}
