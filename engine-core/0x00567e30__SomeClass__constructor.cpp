// FUNC_NAME: SomeClass::constructor
// Function address: 0x00567e30
// Role: Constructor for an unknown class. Sets virtual table pointer, calls base class constructor (0x00ad9db0),
// and conditionally calls utility function (0x009c8eb0) based on allocation flag.
// param_2: allocFlag - bit 0 indicates whether to perform additional initialization/release (e.g., debug registration).
// Returns this pointer.

#include <cstdint>

// Forward declarations for called functions (addresses provided)
extern void __thiscall baseClassConstructor(void* thisPtr);       // 0x00ad9db0
extern void __thiscall additionalInit(void* thisPtr);            // 0x009c8eb0

// vtable pointer from global data (0x00e3a9cc)
extern void* vtable_SomeClass; // PTR_FUN_00e3a9cc

class SomeClass {
public:
    void* vtablePtr; // +0x00

    // Constructor
    SomeClass* __thiscall constructor(uint8_t allocFlag) {
        // Set vtable pointer
        this->vtablePtr = &vtable_SomeClass;

        // Call base class constructor
        baseClassConstructor(this);

        // If allocation flag has bit 0 set, perform additional initialization
        if ((allocFlag & 1) != 0) {
            additionalInit(this);
        }

        return this;
    }
};