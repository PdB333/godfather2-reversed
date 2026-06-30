// FUNC_NAME: RangeValidator::readMinMaxValues
// Function at 0x00592370: Parses two values from token pair (min and max) and validates that min <= max.
// Returns 1 on success, 0 on failure. On success, sets output[3] to this pointer.

#include <cstdint>

// Represents a variant token: either a literal float or an index into a function table.
struct VariantToken {
    char type;          // +0x0: '\n' means index, else literal
    int16_t index;      // +0x2: short index used when type == '\n'
    float value;        // +0x4: float value when type != '\n'
};

// Holds pointers to the two tokens of a line.
struct TokenLine {
    VariantToken* first;   // +0x0
    VariantToken* second;  // +0x4
};

// Global function table for resolving indexed values.
// DAT_01205570 points to an array of function pointers (size DAT_01205574).
extern "C" {
    extern uint32_t DAT_01205574;   // maximum valid index
    extern void** DAT_01205570;     // array of function pointers
}

class RangeValidator {
private:
    // +0x8: pointer to a TokenLine (which holds two token pointers)
    TokenLine* m_tokenLine;

public:
    // Reads min and max values from the current line and validates min <= max.
    // On success, stores this pointer into output[3] and returns 1.
    // On failure (min > max), returns 0.
    int readMinMaxValues(float* output) {
        // Read first token → min value
        float minVal;
        VariantToken* token1 = m_tokenLine->first;
        if (token1->type == '\n') {
            int16_t idx = token1->index;
            if (idx >= 0 && idx < DAT_01205574) {
                void* func = DAT_01205570[4 + idx * 0xc]; // function pointer
                if (func != nullptr) {
                    // The function writes a float result (likely into output array)
                    ((void(*)(float, int, float*))func)(*output, idx, &minVal);
                }
            }
        } else {
            minVal = token1->value;
        }

        // Read second token → max value
        float maxVal;
        VariantToken* token2 = m_tokenLine->second;
        if (token2->type == '\n') {
            int16_t idx = token2->index;
            if (idx >= 0 && idx < DAT_01205574) {
                void* func = DAT_01205570[4 + idx * 0xc];
                if (func != nullptr) {
                    ((void(*)(float, int, float*))func)(*output, idx, &maxVal);
                }
            }
        } else {
            maxVal = token2->value;
        }

        // Validate min <= max
        if (maxVal < minVal) {
            return 0; // invalid range
        }

        // Return this pointer to caller (e.g., for further processing)
        output[3] = reinterpret_cast<float>(this); // store as float (uintptr_t cast)
        return 1;
    }
};