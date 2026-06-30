// FUNC_NAME: Transform::isApproximatelyEqualTo
// Function address: 0x00517040
// Compares two 18-float transform structures (likely rotation quaternion + matrix + translation) with per-component tolerance.
// Components at indices 0-3, 8-15 are compared using absolute bitwise difference (sign bit masked out) <= epsilon.
// Components at indices 16 and 17 are compared for exact equality (likely flags or special markers).
// Constants: s_absMask clears the sign bit of a float's IEEE 754 representation; s_epsilon is the tolerance threshold.

#include <cstdint>
#include <cstring>

// Constants inferred from global read-only data
static const uint32_t s_absMask = 0x7FFFFFFF;             // DAT_00e44680
static const float s_epsilon   = *reinterpret_cast<const float*>(0x00e2e780); // DAT_00e2e780

// Helper: compute the bitwise absolute difference of two floats (clears sign bit of the difference's IEEE representation)
static inline float absDiffFloat(float a, float b) {
    uint32_t diffBits;
    std::memcpy(&diffBits, &(float)(a - b), sizeof(diffBits));
    diffBits &= s_absMask;
    float result;
    std::memcpy(&result, &diffBits, sizeof(result));
    return result;
}

class Transform {
public:
    // Assumes this->m_data contains an 18-float array (offsets: [0-3], [8-15], [16-17])
    // Checks if another Transform's data matches within tolerance.
    bool isApproximatelyEqualTo(const float* otherData) const {
        // Group 1: indices 8,9,10 (rotation/matrix part)
        if (!(absDiffFloat(m_data[8], otherData[8]) <= s_epsilon &&
              absDiffFloat(m_data[9], otherData[9]) <= s_epsilon &&
              absDiffFloat(m_data[10], otherData[10]) <= s_epsilon))
            return false;

        // Group 2: indices 0,1,2,3 and 11 (quaternion + one element from matrix)
        if (!(absDiffFloat(m_data[0], otherData[0]) <= s_epsilon &&
              absDiffFloat(m_data[1], otherData[1]) <= s_epsilon &&
              absDiffFloat(m_data[2], otherData[2]) <= s_epsilon &&
              absDiffFloat(m_data[3], otherData[3]) <= s_epsilon &&
              absDiffFloat(m_data[11], otherData[11]) <= s_epsilon))
            return false;

        // Group 3: exact equality at index 16 (likely a flag)
        if (!(m_data[16] == otherData[16]))
            return false;

        // Group 4: exact equality at index 17, then indices 12-15 with tolerance
        if (!(m_data[17] == otherData[17] &&
              absDiffFloat(m_data[12], otherData[12]) <= s_epsilon &&
              absDiffFloat(m_data[13], otherData[13]) <= s_epsilon &&
              absDiffFloat(m_data[14], otherData[14]) <= s_epsilon &&
              absDiffFloat(m_data[15], otherData[15]) <= s_epsilon))
            return false;

        return true;
    }

private:
    float m_data[18]; // +0x00: indices 0-3 (quaternion?)
                      // +0x20: indices 8-15 (matrix/scale?)
                      // +0x40: indices 16-17 (translation?)
                      // Note: indices 4-7 are not used in comparison.
};
```