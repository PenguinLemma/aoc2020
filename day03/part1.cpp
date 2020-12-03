#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>

struct MapExplorer {
    bool is_there_tree{};

    friend std::istream& operator>>(std::istream& in, MapExplorer& explorer) {
        static std::size_t horizontal_position{};
        std::string s;
        if (in >> s) {
            explorer.is_there_tree = s[horizontal_position % s.size()] == '#';
            horizontal_position = (horizontal_position + 3) % s.size();
        }
        return in;
    }
};

int main() {
    std::cout << std::count_if(
                     std::istream_iterator<MapExplorer>(std::cin),
                     std::istream_iterator<MapExplorer>(),
                     [](auto position) { return position.is_there_tree; })
              << std::endl;
}
