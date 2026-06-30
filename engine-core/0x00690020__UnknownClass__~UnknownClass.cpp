// FUNC_NAME: UnknownClass::~UnknownClass

#include <cstdint>

// Function pointer types for the callees
typedef void (__cdecl *OperatorDeleteFunc)(void* ptr);
typedef void (__cdecl *OperatorDeleteWithFlagFunc)(void* ptr);

// Assume these are defined elsewhere
extern OperatorDeleteFunc operatorDelete;          // FUN_009c8f10
extern OperatorDeleteWithFlagFunc operatorDeleteIfFlag; // FUN_009c8eb0

// Global variable, likely a singleton counter or pointer
static int g_someGlobalFlag = 0; // DAT_01129bb4

// Class with unknown identity, but has members at offsets:
// 0x00: vtable pointer
// 0x04: pointer member (param_1[1])
// 0x10: pointer member (param_1[4])
class UnknownClass {
public:
    void* vftable;       // +0x00
    void* memberAt04;    // +0x04 (freed first in destructor)
    // padding/other members between +0x08 and +0x0F
    void* memberAt10;    // +0x10 (freed second in destructor)
    // possibly more members

    // Destructor with optional memory deallocation
    // param_2: low bit indicates whether to free 'this' memory
    __thiscall void* destroy(byte param_2);
};

// Destructor implementation
__thiscall void* UnknownClass::destroy(byte param_2) {
    // Free member at +0x10 if non-null
    if (this->memberAt10 != nullptr) {
        operatorDelete(this->memberAt10);
    }
    // Free member at +0x04 if non-null
    if (this->memberAt04 != nullptr) {
        operatorDelete(this->memberAt04);
    }
    // Reset vtable to a static table (likely base class vtable or null)
    this->vftable = &PTR_LAB_00d5c85c; // Placeholder for global vtable address
    // Clear global singleton flag
    g_someGlobalFlag = 0;

    // If the low bit is set, also free the object itself
    if (param_2 & 1) {
        operatorDeleteIfFlag(this);
    }
    return this;
}