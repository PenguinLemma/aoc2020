#include <algorithm>
#include <iostream>
#include <iterator>

struct Command {
    int value{0};
    int movement{1};
    bool executed{false};

    void Reset() noexcept {
        value = 0;
        movement = 1;
        executed = false;
    }

    friend std::istream& operator>>(std::istream& in, Command& cmd) {
        cmd.Reset();
        std::string type;
        if (in >> type) {
            int num;
            in >> num;
            switch (type[0]) {
                case 'a':
                    cmd.value = num;
                    break;
                case 'j':
                    cmd.movement = num;
            }
        }
        return in;
    }
};

int main() {
    std::vector<Command> cmds;
    std::copy(std::istream_iterator<Command>(std::cin),
              std::istream_iterator<Command>(),
              std::back_inserter(cmds));

    int accum = 0;
    int pos = 0;
    while (not cmds[pos].executed) {
        accum += cmds[pos].value;
        cmds[pos].executed = true;
        pos += cmds[pos].movement;
    }
    std::cout << accum << std::endl;
}
