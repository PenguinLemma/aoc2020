#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "color_constrain.hpp"

using Contents = std::unordered_map<std::string, int>;
using Graph = std::unordered_map<std::string, Contents>;

int BagsInside(Graph const& g,
               std::string const& current,
               Contents& already_computed) {
    auto it_already_computed = already_computed.find(current);
    if (it_already_computed != already_computed.end())
        return it_already_computed->second;

    auto it = g.find(current);
    if (it == g.end())
        return 0;

    int bags_inside = std::accumulate(
        std::begin(it->second),
        std::end(it->second),
        0,
        [&](int accum, auto color_amount_pair) {
            auto [color, num_bags] = color_amount_pair;
            return accum +
                   num_bags * (BagsInside(g, color, already_computed) + 1);
        });
    already_computed[current] = bags_inside;
    return bags_inside;
}

int BagsInside(Graph const& g) {
    Contents already_computed{};
    return BagsInside(g, "shiny gold", already_computed);
}

int main() {
    Graph contains{};
    ColorConstrain cc;
    while (std::cin >> cc) {
        for (std::size_t i = 0; i < cc.contains.size(); ++i) {
            contains[cc.color_name][cc.contains[i]] = cc.bags_per_color[i];
        }
    }
    std::cout << BagsInside(contains) << std::endl;
}
