#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "color_constrain.hpp"

using AdjacencySet = std::unordered_set<std::string>;
using Graph = std::unordered_map<std::string, AdjacencySet>;

void FillInDescendants(Graph const& g,
                       std::string const& current,
                       std::unordered_set<std::string>& descendants) {
    if (descendants.contains(current))
        return;
    descendants.insert(current);
    auto it = g.find(current);
    if (it == g.end())
        return;
    for (auto descendant : it->second) {
        FillInDescendants(g, descendant, descendants);
    }
}

int CountDescendantsOfShinnyGold(Graph const& g) {
    std::unordered_set<std::string> descendants{};
    FillInDescendants(g, "shiny gold", descendants);
    return static_cast<int>(descendants.size() - 1);
}

int main() {
    Graph can_be_contained_in{};
    ColorConstrain cc;
    while (std::cin >> cc) {
        for (auto color : cc.contains) {
            can_be_contained_in[color].insert(cc.color_name);
        }
    }
    std::cout << CountDescendantsOfShinnyGold(can_be_contained_in) << std::endl;
}
