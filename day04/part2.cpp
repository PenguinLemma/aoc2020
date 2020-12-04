#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <string>

#include "passport.hpp"

int main() {
    std::array<FieldDescription, 7> field_descriptions = {
        FieldDescription{"byr",
                         [](std::string const& value) {
                             if (value.size() != 4 or
                                 not std::isdigit(value[0]))
                                 return false;
                             int val = std::stoi(value);
                             return 1920 <= val and val <= 2002;
                         }},
        FieldDescription{"iyr",
                         [](std::string const& value) {
                             if (value.size() != 4 or
                                 not std::isdigit(value[0])) {
                                 return false;
                             }
                             int val = std::stoi(value);
                             return 2010 <= val and val <= 2020;
                         }},
        FieldDescription{"eyr",
                         [](std::string const& value) {
                             int val = std::stoi(value);
                             return 2020 <= val and val <= 2030;
                         }},
        FieldDescription{
            "hgt",
            [](std::string const& value) {
                if (value.size() < 4 and not std::isdigit(value[0])) {
                    return false;
                }
                std::size_t first_after_number;
                int val = std::stoi(value, &first_after_number);
                if (first_after_number != value.size() - 2)
                    return false;
                if (value.ends_with("cm"))
                    return 150 <= val and val <= 193;
                if (value.ends_with("in"))
                    return 59 <= val and val <= 76;
                return false;
            }},
        FieldDescription{
            "hcl",
            [](std::string const& value) {
                if (value.size() != 7 or value[0] != '#')
                    return false;
                return std::all_of(
                    std::begin(value) + 1, std::end(value), [](char c) {
                        return ('a' <= c and c <= 'f') or std::isdigit(c);
                    });
            }},
        FieldDescription{"ecl",
                         [](std::string const& value) {
                             return value == "amb" or value == "blu" or
                                    value == "brn" or value == "gry" or
                                    value == "grn" or value == "hzl" or
                                    value == "oth";
                         }},
        FieldDescription{"pid", [](std::string const& value) {
                             return value.size() == 9 and
                                    std::all_of(
                                        std::begin(value),
                                        std::end(value),
                                        [](char c) { return std::isdigit(c); });
                         }}};

    PassportChecker const checker{field_descriptions};

    std::cout << std::count_if(std::istream_iterator<Passport>(std::cin),
                               std::istream_iterator<Passport>(),
                               [&checker](Passport const& p) {
                                   return checker.IsValid(p);
                               })
              << std::endl;
}
