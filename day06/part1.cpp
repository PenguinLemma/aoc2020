#include <iostream>
#include <iterator>
#include <numeric>

#include "group_answers.hpp"

int main() {
    std::cout << std::accumulate(
                     std::istream_iterator<GroupAnswers>(std::cin),
                     std::istream_iterator<GroupAnswers>(),
                     0ul,
                     [](unsigned long accum, GroupAnswers const& answers) {
                         return accum + answers.NumberOfYesesUnion();
                     })
              << std::endl;
}
