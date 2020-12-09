#include <algorithm>
#include <iostream>
#include <optional>
#include <vector>

template <unsigned long long Target>
struct WindowSumUpTo {
    std::vector<unsigned long long> window{};
    std::size_t from{0};
    unsigned long long current_sum{0};

    std::optional<unsigned long long> AddAndBounceIfFound(
        unsigned long long num) {
        window.push_back(num);
        current_sum += num;
        while (from < window.size() and current_sum > Target) {
            current_sum -= window[from];
            ++from;
        }
        if (from < window.size() and current_sum == Target) {
            auto const it_to_min =
                std::min_element(std::begin(window) + from, std::end(window));
            auto const it_to_max =
                std::max_element(std::begin(window) + from, std::end(window));
            return *it_to_min + *it_to_max;
        }
        return std::nullopt;
    }
};

int main() {
    unsigned long long i;
    WindowSumUpTo<2089807806> buffer{};
    while (std::cin >> i) {
        auto const found = buffer.AddAndBounceIfFound(i);
        if (found) {
            std::cout << *found << std::endl;
            return 0;
        }
    }
    std::cout << "no match found" << std::endl;
    return 0;
}
