#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <string>

#include "passport.hpp"

int main() {
    std::array<FieldDescription, 7> field_descriptions = {
        FieldDescription{"byr"},
        FieldDescription{"iyr"},
        FieldDescription{"eyr"},
        FieldDescription{"hgt"},
        FieldDescription{"hcl"},
        FieldDescription{"ecl"},
        FieldDescription{"pid"}};

    PassportChecker const checker{field_descriptions};

    std::cout << std::count_if(std::istream_iterator<Passport>(std::cin),
                               std::istream_iterator<Passport>(),
                               [&checker](Passport const& p) {
                                   return checker.IsValid(p);
                               })
              << std::endl;
}
