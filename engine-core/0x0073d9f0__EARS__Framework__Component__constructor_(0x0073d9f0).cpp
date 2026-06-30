// FUNC_NAME: EARS::Framework::Component::constructor (0x0073d9f0)
// This is a constructor for a derived class in the EARS framework.
// It calls a base class constructor, sets the vtable pointer, then computes
// an adjusted pointer from a member at offset 0x48, stores it at offset 0x58,
// initializes several integer fields to 0, and computes a random float
// (using _rand) with the formula: (rand() * fConst1 * fConst2) + fConst3.
// The constants fConst1, fConst2, fConst3 are likely global config values.

#include <cstdlib>

// Forward declarations for global constants (inferred from data refs)
extern float fConst1;  // DAT_00e44590
extern float fConst2;  // DAT_00d5f520
extern float fConst3;  // DAT_00d5f378

// External base class constructor
void EARS_Framework_BaseClass_constructor(void *arg0, void *arg1);

// This class layout (relative to this):
// +0x00: vtable pointer
// +0x48: m_pSomePointer (int/pointer)
// +0x58: m_pAdjustedPointer (int/pointer)
// +0x5C: m_field0x5C
// +0x60: m_field0x60
// +0x64: m_field0x64
// +0x68: m_field0x68
// +0x6C: m_randomValue

class EARSFrameworkComponent {
public:
    // +0x00: vtable pointer (set by constructor)
    // +0x48: m_pSomePointer (some base pointer)
    // +0x58: m_pAdjustedPointer
    // +0x5C: m_field0x5C
    // +0x60: m_field0x60
    // +0x64: m_field0x64
    // +0x68: m_field0x68
    // +0x6C: m_randomValue

    void *vtable;
    int m_field0x04[0x44/4]; // placeholder for unknown fields between +0x04 and +0x48
    int *m_pSomePointer;     // +0x48
    int m_padding[2];        // alignment?
    int *m_pAdjustedPointer; // +0x58
    int m_field0x5C;         // +0x5C
    int m_field0x60;         // +0x60
    int m_field0x64;         // +0x64
    int m_field0x68;         // +0x68
    float m_randomValue;     // +0x6C
};

void * __thiscall EARSFrameworkComponent::constructor(
    void *this,
    void *arg0,
    void *arg1
) {
    // Call base class constructor (arg0 and arg1 are passed through)
    EARS_Framework_BaseClass_constructor(arg0, arg1);

    // Set vtable pointer
    *(void **)this = (void *)0x00d63778; // vtable address, exact label unknown

    // Adjust pointer at offset 0x48
    int iVar1;
    if (*(int *)((char *)this + 0x48) == 0) {
        iVar1 = 0;
    } else {
        iVar1 = *(int *)((char *)this + 0x48) - 0x48;
    }
    // Store adjusted pointer at offset 0x58
    *(int *)((char *)this + 0x58) = iVar1;

    // Zero out four fields
    *(int *)((char *)this + 0x5C) = 0;
    *(int *)((char *)this + 0x60) = 0;
    *(int *)((char *)this + 0x64) = 0;
    *(int *)((char *)this + 0x68) = 0;

    // Initialize random value
    iVar1 = rand();
    *(float *)((char *)this + 0x6C) = (float)iVar1 * fConst1 * fConst2 + fConst3;

    return this;
}