#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

struct Passport {
    std::unordered_map<std::string, std::string> fields{};

    void AddFromLine(std::string const& line) {
        if (line.empty())
            return;
        std::istringstream iss{line};
        std::string key;
        std::string val;
        while (std::getline(iss, key, ':')) {
            iss >> val;
            fields[key] = val;
            iss.ignore(1, ' ');
        }
    }

    friend std::istream& operator>>(std::istream& in, Passport& p) {
        p.fields.clear();
        std::string line{};

        while (in and std::getline(in, line) and not line.empty()) {
            p.AddFromLine(line);
        }
        p.AddFromLine(line);
        return in;
    }
};

struct FieldDescription {
    using ValidatorT = std::function<bool(std::string const& value)>;
    std::string key{};
    ValidatorT validator;
    explicit FieldDescription(
        std::string const& k,
        ValidatorT op = [](std::string const&) { return true; }) noexcept
        : key{k}, validator{op} {}
};

template <std::size_t NumFields>
struct PassportChecker {
    std::array<FieldDescription, NumFields> field_descriptions;
    explicit PassportChecker(
        std::array<FieldDescription, NumFields> const& descriptions) noexcept
        : field_descriptions{descriptions} {}
    bool IsValid(Passport const& p) const {
        return std::all_of(std::begin(field_descriptions),
                           std::end(field_descriptions),
                           [&p](auto description) {
                               auto it = p.fields.find(description.key);
                               return it != p.fields.end() and
                                      description.validator(it->second);
                           });
    }
};
