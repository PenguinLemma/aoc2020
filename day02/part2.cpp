#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

bool IsPasswordCorrect(int lower,
                       int upper,
                       char target,
                       std::string&& pw) noexcept {
    const int num_matches = static_cast<int>(pw[lower] == target) +
                            static_cast<int>(pw[upper] == target);
    return num_matches == 1;
}

int main() {
    std::cout << std::count_if(std::istream_iterator<int>(std::cin),
                               std::istream_iterator<int>(),
                               [](int lower_index) {
                                   std::cin.ignore(1, '-');
                                   int upper_index;
                                   std::cin >> upper_index;
                                   std::cin.ignore(1, ' ');
                                   char target_letter;
                                   std::cin >> target_letter;
                                   std::cin.ignore(2, ' ');
                                   std::string pass;
                                   std::cin >> pass;
                                   return IsPasswordCorrect(lower_index - 1,
                                                            upper_index - 1,
                                                            target_letter,
                                                            std::move(pass));
                               })
              << std::endl;
}
