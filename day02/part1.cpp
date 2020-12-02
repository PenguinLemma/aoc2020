#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

bool IsPasswordCorrect(int lower,
                       int upper,
                       char target,
                       std::string&& pw) noexcept {
    int const freq = std::count(std::begin(pw), std::end(pw), target);
    return lower <= freq and freq <= upper;
}

int main() {
    std::cout << std::count_if(std::istream_iterator<int>(std::cin),
                               std::istream_iterator<int>(),
                               [](int lower_count) {
                                   std::cin.ignore(1, '-');
                                   int upper_count;
                                   std::cin >> upper_count;
                                   std::cin.ignore(1, ' ');
                                   char target_letter;
                                   std::cin >> target_letter;
                                   std::cin.ignore(2, ' ');
                                   std::string pass;
                                   std::cin >> pass;
                                   return IsPasswordCorrect(lower_count,
                                                            upper_count,
                                                            target_letter,
                                                            std::move(pass));
                               })
              << std::endl;
}
