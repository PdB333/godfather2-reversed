// FUNC_NAME: UnknownClass::UnknownClass
// Address: 0x00764980
// Constructor for an unknown class.
// Sets vtable pointer to PTR_LAB_00d655f8, calls base class initialization (FUN_004ac1e0),
// then optionally calls a cleanup/destructor function (FUN_00624da0) if param_2's bit 0 is set.
// This pattern is common in EA's engine for constructors that handle heap/stack allocation.

#include <cstdint>

// Forward declarations for external functions called by the constructor
void baseConstructor_004ac1e0(void);             // likely base class constructor or shared initialization
void destructorOrCleanup_00624da0(void* pThis); // appears to be destructor/cleanup (called when flag & 1)

// Vtable pointer address (externally defined, typically in a read-only data section)
extern void* vtable_00d655f8[];

class UnknownClass {
public:
    // Offset +0x00: vtable pointer (must be first member)
    void** vtable;

    // Constructor (__thiscall with this in ecx)
    // param_2: byte flag; if bit 0 is set, calls cleanup (heap allocation case)
    static UnknownClass* __thiscall constructor(UnknownClass* pThis, uint8_t allocationFlag) {
        pThis->vtable = (void**)&vtable_00d655f8;
        baseConstructor_004ac1e0();
        if (allocationFlag & 1) {
            destructorOrCleanup_00624da0(pThis);
        }
        return pThis;
    }
};