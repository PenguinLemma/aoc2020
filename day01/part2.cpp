#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>

template <int target>
int Result(std::vector<int> const& v) noexcept {
    for (std::size_t pos1 = 0; pos1 < v.size(); ++pos1) {
        std::array<bool, target> was_sum_found{false};
        int const current_target = target - v[pos1];
        for (std::size_t pos2 = 0; pos2 < pos1; ++pos2) {
            if (v[pos2] < current_target) {
                if (was_sum_found[current_target - v[pos2]]) {
                    return v[pos1] * v[pos2] * (current_target - v[pos2]);
                }
                was_sum_found[v[pos2]] = true;
            }
        }
    }
    return -1;  // Reaching this poing would mean there is no such trio
}

int main() {
    int constexpr target = 2020;
    std::vector<int> nums;
    std::copy(std::istream_iterator<int>(std::cin),
              std::istream_iterator<int>(),
              std::back_inserter(nums));

    std::cout << Result<target>(nums) << std::endl;
    return 0;
}