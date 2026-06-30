// FUNC_NAME: TimerManager::calculateJitteredDelay
// Address: 0x006b3390
// This function computes a random delay by subtracting a random value (based on a range defined by fields at +0x68 and +0x6C) from a base value (+0xCC + +0xC8).
// It seeds the RNG with the pointer at +0x40 and obtains a random float from an external function.

#include <cmath> // for floor, ceil if needed (but we replicate the original logic)

// External functions identified from callee addresses
extern "C" void randomizeRNG(unsigned int seed); // FUN_008c74d0
extern "C" float getRandomFloat(); // FUN_008bd4b0

class TimerManager {
public:
    // Fields used:
    // +0x40: pointer/seed for randomizeRNG (likely a context or seed value)
    // +0x68: upper bound (unsigned int)
    // +0x6C: lower bound (unsigned int)
    // +0xC8: first base component (signed int) — offset 200 decimal
    // +0xCC: second base component (signed int)

    int calculateJitteredDelay() __thiscall {
        // Base value: addition of two fields
        int base = *(int*)((char*)this + 0xCC) + *(int*)((char*)this + 200); // +0xC8
        // Seed the RNG with the field at +0x40
        randomizeRNG(*(unsigned int*)((char*)this + 0x40));

        unsigned int upper = *(unsigned int*)((char*)this + 0x68);
        unsigned int lower = *(unsigned int*)((char*)this + 0x6C);
        unsigned int rangeSize;
        if (lower < upper) {
            rangeSize = upper - lower;
        } else {
            rangeSize = 0;
        }

        float random = getRandomFloat(); // returns value in [0.0f, 1.0f) or similar
        // The original uses x87 float10, we approximate with float/double.
        // The logic: subtract ceil(rangeSize * random)
        double product = (double)rangeSize * (double)random;
        // Implementation matching assembly:
        // fVar3 = -product (negative)
        // (int)fVar3 truncates toward zero => -(int)product
        // if product not integer, adjust to floor (i.e., subtract 1)
        int intProduct = (int)product; // truncates toward zero
        // Since product is non-negative, intProduct = floor(product) for non-integer? Actually floor(product) = intProduct for non-integer? e.g., 1.2 => intProduct=1, floor=1. But we need ceil: for non-integer, ceil = intProduct+1.
        // The original subtracts (intProduct+1) when product non-integer.
        int subtractionAmount;
        if (product == (double)intProduct) {
            subtractionAmount = intProduct; // product is integer
        } else {
            subtractionAmount = intProduct + 1; // ceil(product)
        }

        // Apply: result = base - subtractionAmount
        return base - subtractionAmount;
    }
};