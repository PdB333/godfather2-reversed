// FUNC_NAME: SortHelper::medianOfThree
// Address: 0x00588c50
// Purpose: Places the median of three values (this->value, *a, *b) into this->value.
// Uses external comparison function isGreaterThan (0x00587840) which returns true if first > second.

#include <cstdint>

// Forward declaration of external comparison function (returns true if a > b)
bool isGreaterThan(uint32_t a, uint32_t b);

struct SortHelper {
    uint32_t value; // The pivot value to be median-of-three

    // Parameters: pointers to two other values to compare with this->value.
    // After the call, this->value contains the median of the three.
    void medianOfThree(uint32_t* a, uint32_t* b) {
        uint32_t temp;

        // Compare this->value and *a
        temp = value;
        if (isGreaterThan(temp, *a)) {
            // Swap this->value and *a
            value = *a;
            *a = temp;
        }

        // Compare *b and this->value
        temp = *b;
        if (isGreaterThan(temp, value)) {
            // Swap *b and this->value
            *b = value;
            value = temp;
        }

        // Final comparison between this->value and *a to ensure median
        temp = value;
        if (isGreaterThan(temp, *a)) {
            // Swap this->value and *a
            value = *a;
            *a = temp;
        }
    }
};