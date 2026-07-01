// FUNC_NAME: SomeClass::destroy
#include <cstdint>

// Represents a class with a vtable and a component pointer at offset 0x18.
class SomeClass {
public:
    // VTable layout: offset 0x00 = first virtual (maybe destructor?), offset 0x04 = releaseComponent etc.
    // We need a pointer to the vtable.
    int* vtablePtr; // +0x00

    // Member at offset 0x18 (param_1[6])
    void* componentPtr; // +0x18

    // Custom destroy function – called by operator delete? Returns this for chaining.
    // ESI holds a flag: if bit0 set, free the memory.
    // asm: __fastcall, param_1 (ECX) = this, ESI = deleteFlag
    __declspec(naked) void* __fastcall destroy(int deleteFlag) {
        // The decompiled code shows call to base destructor, then component release, then optional delete.
        // We reconstruct the logic in inline assembly style but we'll make it standard C++ with the assumption
        // that deleteFlag is passed in ESI and this in ECX.
    }
};

// Assume callees are functions with known names.
extern void baseDestructor(); // FUN_0081c980
extern void additionalCleanup(); // FUN_0081d230
extern void operatorDelete(void* ptr); // FUN_009c8eb0 -> likely operator delete

void* SomeClass::destroy(int deleteFlag) {
    baseDestructor(); // Call base class destructor

    // Release component via vtable call (offset 4 from vtable pointer)
    // vtablePtr is a pointer to the vtable; the first entry at offset 0 is something else.
    // The call: (**(code **)(*(int *)*param_1 + 4))(param_1[6], 0x2c);
    // That means vtablePtr[1] is a function pointer taking (void* component, int arg0x2c).
    // In C++: call release with parameter 0x2c (maybe a flag).
    typedef void (__thiscall *ReleaseFunc)(void* component, int flag);
    ReleaseFunc release = *reinterpret_cast<ReleaseFunc*>(vtablePtr + 1);
    release(componentPtr, 0x2c);

    // Null the component pointer after release
    componentPtr = nullptr;

    additionalCleanup(); // Additional cleanup

    // Conditionally free the object memory if bit0 of deleteFlag is set
    if (deleteFlag & 1) {
        operatorDelete(this); // FUN_009c8eb0
    }

    return this; // Return the pointer (might be used for assignment)
}