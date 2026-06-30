// FUNC_NAME: getMaximumSampleValue
// Address: 0x005906a0
// Role: Computes the maximum value from repeated calls to a sample generator, or returns 1.0 if count is zero.
// Uses a sample count stored at offset +1 of a data structure.
// The first parameter (unused) may be a this pointer for __thiscall, but appears not used.

float getMaximumSampleValue(void* unused, void* data) {
    int count = *(char*)((char*)data + 1); // signed char, count at offset 0x01
    float maxValue = 0.0f;
    float currentValue = 0.0f;

    if (count != 0) {
        if (count > 0) {
            do {
                currentValue = getSampleValue(); // returns a float from an external function
                if (maxValue < currentValue) {
                    maxValue = currentValue;
                }
                count--;
            } while (count != 0);
        }
        return maxValue;
    }
    return 1.0f; // default value when no samples
}