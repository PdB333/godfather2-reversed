// FUNC_NAME: AIBehavior::constructor
// Address: 0x009053a0
// Role: Constructor for an AIBehavior component. Initializes three pointer fields to null after calling base class constructor.

#include <cstdint>

class AIBehavior : public EARSObject {
public:
    // Constructor at 0x009053a0
    AIBehavior() : EARSObject() {
        // Base constructor (FUN_004c26c0) called implicitly via initializer list
        // Explicit vtable overwrite to this class's vtable (at 0x00e36260)
        // (compiler typically sets this automatically, but assembly shows explicit write)
        *reinterpret_cast<void**>(this) = reinterpret_cast<void*>(0x00e36260);

        // Initialize three fields at offsets 0x208, 0x20C, 0x210 to null
        // These are likely pointers or handles, deliberately zeroed
        m_pEntry1 = nullptr;  // +0x208
        m_pEntry2 = nullptr;  // +0x20C
        m_pEntry3 = nullptr;  // +0x210
    }

private:
    // VTable pointer is inherited from EARSObject (first member)
    // The following members appear at large offsets relative to object start.
    // Actual class layout between base and these fields is unknown.
    uint32_t m_pEntry1; // +0x208 (void* or int)
    uint32_t m_pEntry2; // +0x20C
    uint32_t m_pEntry3; // +0x210
};