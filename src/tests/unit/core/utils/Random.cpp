#include "core/utils/Random.h"

#include "lest.hpp"

#include <array>
#include <cstdint>

template<uint64_t Range, uint64_t Bins>
struct Histogram {
    std::array<uint64_t, Bins> counts;

    Histogram() { counts.fill(0); }

    void push(uint64_t value) {
        uint64_t bin = value / (Range / Bins);
        ++counts[bin];
    }
};

const lest::test specification[] = {

    CASE("next() returns uniform distribution") {
        Random rng;
        Histogram<0x100000000, 100> histogram;
        for (size_t i = 0; i < 10000000; ++i) {
            histogram.push(rng.next());
        }
        for (const auto &count : histogram.counts) {
            EXPECT(std::abs(100000 - int(count)) < 1000);
        }
    },

    CASE("nextBinary() returns uniform distribution") {
        Random rng;
        Histogram<2, 2> histogram;
        for (size_t i = 0; i < 200000; ++i) {
            histogram.push(rng.nextBinary());
        }
        for (const auto &count : histogram.counts) {
            EXPECT(std::abs(100000 - int(count)) < 1000);
        }
    },

    CASE("nextRange() returns uniform distribution") {
        Random rng;
        Histogram<16, 16> histogram;
        for (size_t i = 0; i < 1600000; ++i) {
            histogram.push(rng.nextRange(16));
        }
        for (const auto &count : histogram.counts) {
            EXPECT(std::abs(100000 - int(count)) < 1000);
        }
    },

};

int main(int argc, char *argv[]) {
    return lest::run(specification, argc, argv);
}
