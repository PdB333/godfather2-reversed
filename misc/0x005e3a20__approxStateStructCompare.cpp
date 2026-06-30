// FUNC_NAME: approxStateStructCompare
// Address: 0x005e3a20
// Compares two state structures (int id + 4 floats) for approximate equality using integer ULP comparison.
// Parameters: param1 in ECX, param2 in EDX (__fastcall)
// Returns 1 if equal, 0 otherwise.

#define SIGN_BIT_MASK 0x7FFFFFFF   // clear sign bit for integer float comparison
#define ULP_THRESHOLD 0x12345678   // replace with actual threshold from DAT_00e44598

struct StateStruct {
    int id;          // +0x00
    float values[4]; // +0x04 (4 floats)
};

__fastcall int approxStateStructCompare(const StateStruct* a, const StateStruct* b) {
    // First compare the ID
    if (a->id != b->id)
        return 0;

    // Compare each float using integer representation with sign bit cleared and ULP threshold
    for (int i = 0; i < 4; ++i) {
        // Compute difference of integer representations, mask away sign bit
        unsigned int diff = (reinterpret_cast<const unsigned int&>(a->values[i]) -
                             reinterpret_cast<const unsigned int&>(b->values[i])) & SIGN_BIT_MASK;
        if (diff >= ULP_THRESHOLD)
            return 0;
    }
    return 1;
}