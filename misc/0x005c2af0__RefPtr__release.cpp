// FUNC_NAME: RefPtr::release

// Address: 0x005c2af0
// Role: Releases the owned pointer and resets internal fields
// Likely a smart pointer or reference counted wrapper
// Structure:
//   +0x00: void* mPtr (owned object)
//   +0x04: int mField1 (unknown, zeroed)
//   +0x08: int mField2 (unknown, zeroed)

#include <cstdint>

// Global used to locate the vtable of the owned object's class
extern void* DAT_012234ec;

class RefPtr {
public:
    void* mPtr;        // +0x00
    int mField1;       // +0x04
    int mField2;       // +0x08

    void __thiscall release();
};

void __thiscall RefPtr::release() {
    // Zero out internal fields
    mField2 = 0;
    mField1 = 0;

    // If the owned pointer is non-null, release it via vtable call
    if (mPtr != nullptr) {
        // Obtain the vtable from the global structure
        // DAT_012234ec + 4 points to a vtable pointer
        // Then + 4 is the offset to the Release method (index 1)
        auto vtablePtr = *reinterpret_cast<int**>(static_cast<char*>(DAT_012234ec) + 4);
        auto releaseFunc = reinterpret_cast<void (__thiscall*)(void*, int)>(vtablePtr[1]);
        releaseFunc(mPtr, 0);
    }

    // Clear the owned pointer
    mPtr = nullptr;
}