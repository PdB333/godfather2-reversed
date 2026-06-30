// FUNC_NAME: SomeClass::compareTo
// Address: 0x00693bb0
// Role: Compares two objects of a class with two integer fields (m_typeId and m_value).
// Returns a combined value: high 24 bits = high 24 bits of this->m_value, low 8 bits = equality flag (1 if different, 0 if equal).
// Calls an assertion if m_typeId is zero or not equal to other.m_typeId.

class SomeClass {
public:
    int m_typeId;   // +0x00
    int m_value;    // +0x04

    // __thiscall
    int compareTo(const SomeClass* other) const {
        // Assert that this->m_typeId is non-zero and equals other->m_typeId.
        if ((m_typeId == 0) || (m_typeId != other->m_typeId)) {
            debugAssert(); // FUN_00b97aea – likely assertion failure handler
        }
        // Build result: (m_value >> 8) << 8 | (m_value != other->m_value)
        // Equivalent to: (m_value & 0xFFFFFF00) | (m_value != other->m_value ? 1 : 0)
        return ((m_value >> 8) << 8) | (m_value != other->m_value);
    }

private:
    void debugAssert(); // FUN_00b97aea – implementation not shown
};