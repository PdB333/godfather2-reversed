// FUNC_NAME: ComparisonKey::Compare
// Address: 0x00693be0
// Role: Compares two ComparisonKey objects by their type and value fields. Returns a 32-bit value where the upper 24 bits come from the high 24 bits of this->m_value, and the low byte is 1 if the full m_value fields are equal, else 0. If the type fields are mismatched or zero, an assertion failure is triggered.

class ComparisonKey {
public:
    int m_type;   // +0x00
    int m_value;  // +0x04

    // __thiscall
    int Compare(const ComparisonKey& other) const {
        // Assert that this->m_type is non-zero and equal to other.m_type
        if (m_type == 0 || m_type != other.m_type) {
            FUN_00b97aea();  // likely DebugAssert or similar failure handler
        }

        // Build result: high 24 bits = m_value >> 8, low byte = (m_value == other.m_value)
        return (m_value & 0xFFFFFF00) | (m_value == other.m_value);
    }
};