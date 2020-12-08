#include <algorithm>
#include <iostream>
#include <iterator>
#include <optional>
#include <unordered_set>

struct Command {
    enum class Type { acc, jmp, nop };
    int value{0};
    Type type;

    friend std::istream& operator>>(std::istream& in, Command& cmd) {
        std::string type;
        if (in >> type) {
            int num;
            in >> num;
            cmd.value = num;
            switch (type[0]) {
                case 'a':
                    cmd.type = Command::Type::acc;
                    break;
                case 'j':
                    cmd.type = Command::Type::jmp;
                    break;
                default:
                    cmd.type = Command::Type::nop;
            }
        }
        return in;
    }
};

int ShouldJump(Command::Type type, bool switch_cases) {
    return (switch_cases and type == Command::Type::nop) or
           (not switch_cases and type == Command::Type::jmp);
}

std::optional<int> ComputeSwitching(std::vector<Command> const& cmds,
                                    int nth_jmp_or_nop_to_switch) {
    int accum = 0;
    std::unordered_set<std::size_t> executed{};
    int pos = 0;
    int num_jmp_or_nop = 0;
    while (pos < static_cast<int>(cmds.size())) {
        if (executed.contains(pos))
            return std::nullopt;
        executed.insert(pos);
        if (cmds[pos].type == Command::Type::acc) {
            accum += cmds[pos].value;
            ++pos;
        }
        else {
            pos += ShouldJump(cmds[pos].type,
                              num_jmp_or_nop == nth_jmp_or_nop_to_switch)
                       ? cmds[pos].value
                       : 1;
            ++num_jmp_or_nop;
        }
    }
    return accum;
}

int main() {
    std::vector<Command> cmds;
    std::copy(std::istream_iterator<Command>(std::cin),
              std::istream_iterator<Command>(),
              std::back_inserter(cmds));

    int jmp_or_nop_to_change = 0;  // the 0th {jmp, nop} found will be switched
    std::optional<int> result = std::nullopt;
    while (not result) {
        result = ComputeSwitching(cmds, jmp_or_nop_to_change++);
    }
    std::cout << result.value() << std::endl;
}
