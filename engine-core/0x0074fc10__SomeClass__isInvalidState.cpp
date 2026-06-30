// FUNC_NAME: SomeClass::isInvalidState
// Function at 0x0074fc10: Checks if the object has its PARTIALLY_ACTIVE flag set and either has no child or the child's data pointer is null.

class SomeClass; // forward declaration

class SomeClass {
public:
    // Offsets:
    // +0x04: uint32 m_flags
    // +0x0C: SomeClass* m_pChild

    bool isInvalidState() const {
        // Check if the PARTIALLY_ACTIVE flag (0x10000000) is set
        if (!(m_flags & 0x10000000))
            return false;

        // If child is null or child's data pointer (at +0x04 of child) is null, return true
        if (m_pChild == nullptr || m_pChild->m_flags == 0) // Note: using child's m_flags as a proxy for "data pointer"
            return true;

        return false;
    }

private:
    uint32 m_flags;       // +0x04
    SomeClass* m_pChild;   // +0x0C
};