// FUNC_NAME: SomeClass::constructor
// Address: 0x008d70b0
// Role: Constructor for a class with multiple inheritance (vtable at +0x00, +0x3C, +0x48) and a sub-object pointer at +0x50.
// The class size is 0x90 bytes. If allocFlag bit 0 is set, memory is allocated via operator delete? (FUN_0043b960).

#include <cstdint>

// Forward declarations of called functions (assumed to be member functions or globals)
void subObjectRelease(void* obj);   // FUN_004086d0
void subObjectDestroy(void* obj);   // FUN_00408310
void globalInit();                  // FUN_0046c640
void operatorDelete(void* ptr, uint32_t size); // FUN_0043b960

class SomeClass {
public:
    // Vtable pointers (set by constructor)
    void* vtable0;          // +0x00
    // ... other members ...
    void* vtable3C;         // +0x3C (second base class vtable)
    void* vtable48;         // +0x48 (third base class vtable)
    void* subObject;        // +0x50 (pointer to a sub-object that may need cleanup)
    // ... remaining members up to 0x90 ...

    // Constructor
    // allocFlag: bit 0 set means allocate memory (size 0x90) before constructing?
    static SomeClass* __thiscall constructor(SomeClass* thisPtr, uint8_t allocFlag) {
        // Set vtable pointers
        thisPtr->vtable0 = (void*)0x00d7d6bc;
        thisPtr->vtable3C = (void*)0x00d7d6ac;
        thisPtr->vtable48 = (void*)0x00d7d6a8;

        // If sub-object pointer is non-null, release and destroy it
        if (thisPtr->subObject != nullptr) {
            subObjectRelease(thisPtr->subObject);
            subObjectDestroy(thisPtr->subObject);
        }

        // Global initialization call
        globalInit();

        // If allocation flag is set, deallocate the entire object? (operator delete with size 0x90)
        // Note: This is unusual for a constructor; might be a placement new or a custom allocator.
        if (allocFlag & 1) {
            operatorDelete(thisPtr, 0x90);
        }

        return thisPtr;
    }
};