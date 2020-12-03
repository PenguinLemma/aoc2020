#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

long NumberOfTrees(std::vector<std::string> const& map,
                   std::size_t hmove,
                   std::size_t vmove) {
    std::size_t hpos = 0;
    long count = 0;
    std::size_t width = map[0].size();
    for (std::size_t vpos = 0; vpos < map.size(); vpos += vmove) {
        if (map[vpos][hpos] == '#')
            ++count;
        hpos = (hpos + hmove) % width;
    }
    return count;
}

int main() {
    std::vector<std::string> map;
    std::copy(std::istream_iterator<std::string>(std::cin),
              std::istream_iterator<std::string>(),
              std::back_inserter(map));

    std::cout << NumberOfTrees(map, 1, 1) * NumberOfTrees(map, 3, 1) *
                     NumberOfTrees(map, 5, 1) * NumberOfTrees(map, 7, 1) *
                     NumberOfTrees(map, 1, 2)
              << std::endl;
}
