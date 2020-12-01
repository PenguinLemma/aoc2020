#include <array>
#include <iostream>

int main() {
    int constexpr target = 2020;
    std::array<bool, target> was_num_found{false};
    int num;
    while (std::cin >> num) {
        if (num < target) {
            if (was_num_found[target - num]) {
                std::cout << num * (target - num) << std::endl;
                return 0;
            }
            was_num_found[num] = true;
        }
    }
}
