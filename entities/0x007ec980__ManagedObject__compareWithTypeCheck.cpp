// FUNC_NAME: ManagedObject::compareWithTypeCheck
// Function at 0x007ec980 performs a type-checked comparison of two ManagedObject instances.
// Checks that both objects have the same non-null type pointer (vtable or type info).
// Then returns a 32-bit value combining the high 24 bits of the second field (likely an ID)
// with a boolean indicating whether the full second fields are equal.
// If the type mismatch or null, an error handler is called (likely an assertion).

#include <cstdint>

// Forward declaration of error handler (maps to FUN_00b97aea)
extern void reportTypeMismatchError();

class ManagedObject {
public:
    // +0x00: Type info pointer (vtable or type descriptor)
    void* m_typeInfo;
    // +0x04: Identifier or packed data (e.g., 24-bit hash + 8-bit flags)
    uint32_t m_id;

    // __thiscall: this is param_1, other is param_2
    // Returns a composite value:
    //   high 24 bits = (this->m_id >> 8)  (top 24 bits of this's ID)
    //   low 8 bits   = (this->m_id != other->m_id) ? 1 : 0
    uint32_t compareWithTypeCheck(const ManagedObject& other) const {
        // Precondition: type must be valid and match
        if (!m_typeInfo || m_typeInfo != other.m_typeInfo) {
            reportTypeMismatchError();  // Debug assertion
        }

        // Shift away low 8 bits to get high 24 bits of this->m_id
        uint32_t highPart = m_id >> 8;               // 24-bit value (top bits)
        uint8_t lowPart = (m_id != other.m_id) ? 1 : 0; // Equality flag (0 if equal, 1 if not)

        // Pack into 32 bits: high 24 bits from this, low 8 bits signifying inequality
        return (highPart << 8) | lowPart;
    }
};