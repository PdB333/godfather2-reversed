// FUNC_NAME: EARSObject::EARSObject (constructor, size 0x2A0)
// Function address: 0x006b7210
// Role: Constructor for an EARS engine object of size 0x2A0 (672 bytes).
// Calls base constructor then conditionally performs size-dependent initialization/deallocation based on flag.
// The flag parameter may indicate allocation type (e.g., from pool vs. dynamic), with bit0 controlling additional setup.

#include <cstdint>

class EARSObjectBase {
public:
    // Base constructor at FUN_006b7030
    void __thiscall constructor();
};

// External function at 0x0043b960 – likely a size-aware placement operator delete or cleanup.
// In this context, called after base construction when the flag's lowest bit is set.
// The size 0x2A0 corresponds to the class's object size.
extern void __thiscall earsObjectCleanup(void* obj, std::size_t size);

class EARSObject : public EARSObjectBase {
public:
    // Constructor: param_2 is a flag (byte) controlling post-base initialization.
    // If (param_2 & 1) != 0, perform additional cleanup or registration.
    void* __thiscall constructor(uint8_t flag) {
        // Call base class constructor (EARSObjectBase::constructor at 0x006b7030)
        this->EARSObjectBase::constructor();

        // Conditionally invoke cleanup/registration helper
        if (flag & 1) {
            earsObjectCleanup(this, 0x2A0); // size of EARSObject
        }

        // Return this pointer (standard for __thiscall constructors)
        return this;
    }
};