#include <array>
#include <iostream>
#include <sstream>
#include <string>

class GroupAnswers {
    std::array<unsigned, 26> yeses_count_{0};
    unsigned number_yeses_union_ = 0;
    unsigned number_members_ = 0;

  public:
    void Reset() noexcept {
        yeses_count_ = {0};
        number_yeses_union_ = 0;
        number_members_ = 0;
    }

    [[nodiscard]] unsigned long NumberOfYesesUnion() const noexcept {
        return static_cast<unsigned long>(number_yeses_union_);
    }

    [[nodiscard]] unsigned long NumberOfYesesIntersection() const noexcept {
        return std::count_if(
            std::begin(yeses_count_),
            std::end(yeses_count_),
            [this](unsigned count) { return count == number_members_; });
    }

    void AddYesesForMember(std::string const& yeses) noexcept {
        if (yeses.empty())
            return;
        for (auto y : yeses) {
            std::size_t question_pos = y - 'a';
            number_yeses_union_ +=
                static_cast<int>(yeses_count_[question_pos] == 0);
            ++yeses_count_[question_pos];
        }
        ++number_members_;
    }

    friend std::istream& operator>>(std::istream& in, GroupAnswers& answers) {
        answers.Reset();
        std::string member_yeses{};
        while (in and std::getline(in, member_yeses) and
               not member_yeses.empty()) {
            answers.AddYesesForMember(member_yeses);
        }
        answers.AddYesesForMember(member_yeses);
        return in;
    }
};
