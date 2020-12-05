#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <tuple>

int main() {
    auto const [sum, min_el, max_el] = std::transform_reduce(
        std::istream_iterator<std::string>(std::cin),
        std::istream_iterator<std::string>(),
        std::make_tuple<std::size_t, std::size_t, std::size_t>(0, 1023, 1),
        [](std::tuple<std::size_t, std::size_t, std::size_t> accum,
           std::size_t next) {
            auto& [sum, min_el, max_el] = accum;
            sum += next;
            min_el = std::min(min_el, next);
            max_el = std::max(max_el, next);
            return accum;
        },
        [](std::string const& s) {
            return std::accumulate(
                std::begin(s),
                std::end(s),
                static_cast<std::size_t>(0),
                [](std::size_t accum, char c) {
                    return (accum << 1) |
                           static_cast<std::size_t>(c == 'B' or c == 'R');
                });
        });
    auto const expected_sum = ((max_el + min_el) * (max_el - min_el + 1)) / 2;
    std::cout << expected_sum - sum << std::endl;
}
