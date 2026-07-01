// FUNC_NAME: updateMovingAverage
// 0x008d5f20 - Updates a moving average/variance statistics structure given a new value and the value being removed.
// Computes mean, variance, and standard deviation from a sliding window.
// param_1: Pointer to output RunningStats struct (contains count, sum, mean, sumSquares, variance, stddev)
// param_2: Pointer to input RunningStats struct (contains previous count, sum, sumSquares at offsets +4 and +0x10)
// param_3: Unused (0x4 bytes, ignored)
// param_4: New data value to add to the window
// param_5: Old data value to remove from the window
// param_6: Window size (count of samples)

#include <cmath>

// Structure representing the running statistics for a sliding window.
// Offsets correspond to int32 fields:
// +0x00: count (window size)
// +0x04: sum of values
// +0x08: mean of values
// +0x0C: sum of squares of values (square of sum, intermediate)
// +0x10: sum of squared values
// +0x14: variance (population or sample)
// +0x18: standard deviation
struct RunningStats {
    int32_t count;       // +0x00
    int32_t sum;         // +0x04
    int32_t mean;        // +0x08
    int32_t sumSq;       // +0x0C
    int32_t sumSquares;  // +0x10
    int32_t variance;    // +0x14
    int32_t stdDev;      // +0x18
};

void updateMovingAverage(RunningStats* outStats,
                         RunningStats* inStats,
                         int32_t unused,      // param_3, not used
                         float newValue,
                         float oldValue,
                         int32_t windowSize)
{
    // Store the window size (count) into output
    outStats->count = windowSize;

    // Update sum: (incoming sum - oldValue) + newValue
    // inStats->sum is stored as int32 but at offset +4 it's actually float in memory?
    // The code reads *(float*)(param_2 + 4) so the field is stored as float but the decompiler shows int*.
    // We keep the cast as float to match.
    float prevSum = *reinterpret_cast<float*>(&inStats->sum); // offset +0x04
    outStats->sum = static_cast<int32_t>((prevSum - oldValue) + newValue);

    // Update sum of squares: (incoming sumSquares - oldValue^2) + newValue^2
    float prevSumSquares = *reinterpret_cast<float*>(&inStats->sumSquares); // offset +0x10
    outStats->sumSquares = static_cast<int32_t>((prevSumSquares - oldValue * oldValue) + newValue * newValue);

    // Cast the computed sum to float for mean calculation
    float sumFloat = static_cast<float>(outStats->sum);

    // Compute square of sum for variance calculation
    outStats->sumSq = static_cast<int32_t>(sumFloat * sumFloat); // offset +0x0C

    // Compute mean = sum / windowSize
    float countFloat = static_cast<float>(windowSize);
    // Handle potential negative count (though unlikely)
    if (windowSize < 0) {
        // This line in the original code adjusts for negative values using a large constant.
        // Likely a safeguard; we keep the logic.
        constexpr float kAdjustConstant = 4294967296.0f; // DAT_00e44578 (2^32)
        countFloat += kAdjustConstant;
    }
    outStats->mean = static_cast<int32_t>((1.0f / countFloat) * sumFloat); // offset +0x08

    // Compute variance = (sumSquares - (sum^2)/count) / (count - 1)
    float countMinusOne = static_cast<float>(windowSize - 1);
    if (windowSize - 1 < 0) {
        constexpr float kAdjustConstant = 4294967296.0f;
        countMinusOne += kAdjustConstant;
    }

    float sumSquaresFloat = static_cast<float>(outStats->sumSquares);
    float variance = (sumSquaresFloat - (1.0f / countFloat) * sumFloat * sumFloat) / countMinusOne;
    outStats->variance = static_cast<int32_t>(variance);

    // Standard deviation = sqrt(variance)
    outStats->stdDev = static_cast<int32_t>(sqrt(variance)); // uses SQRT intrinsic
}