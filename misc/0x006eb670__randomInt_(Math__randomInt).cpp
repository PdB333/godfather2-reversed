// FUNC_NAME: randomInt (Math::randomInt)
// Function address: 0x006eb670
// Role: Returns a random integer in the range [0, maxValue), using a linear scaling of rand().
// Uses floating-point arithmetic for precision, then rounds to int.
// Assumes global constants: kNegativeOffset, kSubtract, kScale.

// Constants (likely defined elsewhere in data section)
static const float kNegativeOffset = DAT_00e44578;  // added when input is negative
static const float kSubtract = DAT_00e445cc;        // subtracted from adjusted input
static const float kScale = DAT_00e44590;            // multiplier applied after rand

int randomInt(int maxValue) // __cdecl
{
    float adjustedMax = static_cast<float>(maxValue);
    if (maxValue < 0) {
        adjustedMax += kNegativeOffset;
    }

    // Generate random floating-point value in [0, 1) scaled by (adjustedMax - kSubtract) * kScale
    float randFloat = static_cast<float>(rand()); // Note: rand() returns int in [0, RAND_MAX]
    float scaled = (adjustedMax - kSubtract) * randFloat * kScale;

    // Round to nearest integer and return
    return static_cast<int>(roundf(scaled));
}