#include <array>
#include <iostream>
#include <optional>
#include <unordered_set>

template <std::size_t Capacity>
class RingBuffer {
  public:
    std::optional<unsigned long long> AddAndBounceIfFound(
        unsigned long long num) {
        if (size_ == Capacity) {
            if (Check(num))
                return num;
            nums_.erase(buffer_[oldest_]);
            oldest_ = (oldest_ + 1) % Capacity;
        }
        else {
            ++size_;
        }

        buffer_[next_] = num;
        next_ = (next_ + 1) % Capacity;
        nums_.insert(num);
        return std::nullopt;
    }

  private:
    std::array<unsigned long long, Capacity> buffer_{0};
    std::unordered_set<unsigned long long> nums_{};
    std::size_t next_{0};
    std::size_t oldest_{0};
    std::size_t size_{0};

    bool Check(unsigned long long num) const {
        for (auto prev : nums_) {
            if (num > prev and nums_.contains(num - prev) and
                prev != num - prev) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    unsigned long long i;
    RingBuffer<25> buffer{};
    while (std::cin >> i) {
        auto const found = buffer.AddAndBounceIfFound(i);
        if (found) {
            std::cout << *found << std::endl;
            return 0;
        }
    }
    std::cout << "no match found" << std::endl;
    return 0;
}
