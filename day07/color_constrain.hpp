#include <iostream>
#include <sstream>
#include <vector>

struct Color {
    std::string name{};

    friend std::istream& operator>>(std::istream& in, Color& color) {
        color.name.clear();
        std::string word;
        while (in >> word and not word.starts_with("bag")) {
            color.name += word + " ";
        }
        color.name.pop_back();
        return in;
    }
};

struct ColorConstrain {
    std::string color_name{};
    std::vector<std::string> contains{};
    std::vector<int> bags_per_color{};

    friend std::istream& operator>>(std::istream& in, ColorConstrain& cc) {
        cc.color_name.clear();
        cc.contains.clear();
        cc.bags_per_color.clear();

        Color col;
        if (in >> col) {
            cc.color_name = col.name;
            std::string contains{};
            in >> contains;

            std::string line{};
            std::getline(in, line);
            std::istringstream iss{line};
            int num;
            while (iss >> num) {
                iss >> col;
                cc.bags_per_color.push_back(num);
                cc.contains.push_back(col.name);
            }
        }
        return in;
    }
};
