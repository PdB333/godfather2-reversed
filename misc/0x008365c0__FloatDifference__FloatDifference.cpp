// FUNC_NAME: FloatDifference::FloatDifference
// Address: 0x008365c0
// Role: Constructor for a class that stores the difference of two floats from other objects at offset 0x4c.

// Base class constructor called at the beginning
void* BaseClass_Constructor(void* this);

// Vtable pointer for this class (set to &PTR_LAB_00d73738)
extern void* g_vtable_FloatDifference;
// Default value for the delta field (from _DAT_00d5780c)
extern float g_defaultFloat;

// Partial structure of the object (size at least 0x50 bytes)
struct FloatDifference {
    void** vtable;      // +0x00
    // ... other unknown members ...
    float m_delta;      // +0x4c (offset 0x13 * 4)
};

// __thiscall constructor
FloatDifference* __thiscall FloatDifference::FloatDifference(FloatDifference* this, int objA, int objB) {
    // Call base class constructor
    BaseClass_Constructor(this);

    // Set vtable for this class
    this->vtable = &g_vtable_FloatDifference;

    // Initialize with default value (overwritten below)
    this->m_delta = g_defaultFloat;

    // Compute the difference of floats at offset 0x4c from objA and objB.
    // Those objects likely have a float field at +0x4c (e.g., position component, speed, etc.)
    this->m_delta = *(float*)(objA + 0x4c) - *(float*)(objB + 0x4c);

    return this;
}