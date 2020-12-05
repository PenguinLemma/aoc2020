#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>

int main() {
    std::cout << std::transform_reduce(
                     std::istream_iterator<std::string>(std::cin),
                     std::istream_iterator<std::string>(),
                     static_cast<std::size_t>(0),
                     [](std::size_t first, std::size_t second) {
                         return std::max(first, second);
                     },
                     [](std::string const& s) {
                         return std::accumulate(
                             std::begin(s),
                             std::end(s),
                             static_cast<std::size_t>(0),
                             [](std::size_t accum, char c) {
                                 return (accum << 1) |
                                        static_cast<std::size_t>(c == 'B' or
                                                                 c == 'R');
                             });
                     })
              << std::endl;
}
