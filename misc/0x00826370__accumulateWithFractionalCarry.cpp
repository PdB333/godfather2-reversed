// FUNC_NAME: accumulateWithFractionalCarry
// Address: 0x00826370
// Role: Accumulates a scaled input value into an integer accumulator and a fractional accumulator,
// handling carry propagation. Used for fixed-point time or physics step accumulation.

extern float g_timeScaleFactor; // DAT_00e44638 - scale factor for input

void accumulateWithFractionalCarry(float input, int* integerAccum, float* fractionalAccum)
{
    // Scale input by global factor
    float scaled = input * g_timeScaleFactor;

    // Round scaled value to nearest integer and add to integer accumulator
    int roundedInt = static_cast<int>(std::round(scaled));
    *integerAccum += roundedInt;

    // Compute fractional part (scaled - truncated scaled) and add to existing fractional accumulator
    float fractionalPart = (scaled - static_cast<float>(static_cast<int>(scaled))) + *fractionalAccum;
    *fractionalAccum = fractionalPart;

    // Round the new fractional accumulator to get another carry, add to integer accumulator
    int carry = static_cast<int>(std::round(fractionalPart));
    *integerAccum += carry;

    // Normalize fractional accumulator by subtracting its integer part (truncation)
    *fractionalAccum = fractionalPart - static_cast<float>(static_cast<int>(fractionalPart));
}