// FUNC_NAME: SomeClass::~SomeClass
// Address: 0x00813b20, role: Destructor with memory deallocation flag

#include <cstdint>

// Forward declarations for external functions
void destroySubObjectPart1(void* obj); // FUN_004086d0
void destroySubObjectPart2(void* obj); // FUN_00408310
void globalCleanup(void);             // FUN_0046c640
void deallocate(void* ptr, uint32 size); // FUN_0043b960

// External vtable symbols (defined elsewhere)
extern void* PTR_FUN_00d730a0;
extern void* PTR_LAB_00d73090;
extern void* PTR_LAB_00d7308c;

class SomeClass {
public:
    // Offsets (32-bit)
    // +0x00: vtable pointer (set to PTR_FUN_00d730a0)
    // +0x3C: second vtable (PTR_LAB_00d73090)
    // +0x48: third vtable (PTR_LAB_00d7308c)
    // +0x50: sub-object (destroyed by destroySubObjectPart1/2)
    // +0x58: child object pointer
    // +0x64: function pointer for child deletion

    void* vtable;
    // padding or other members up to +0x3C
    void* secondVtable;
    // padding to +0x48
    void* thirdVtable;
    // padding to +0x50
    uint8 subObject[?]; // Size unknown, but passed as void*
    void* childPointer; // +0x58
    void (*childDeleter)(void*); // +0x64 function pointer

    // Internal destructor used by compiler
    SomeClass* __thiscall internalDestructor(uint8 shouldDelete);
};

SomeClass* SomeClass::internalDestructor(uint8 shouldDelete) {
    // --- Set vtables (possible multiple inheritance adjustment) ---
    this->vtable = &PTR_FUN_00d730a0;
    this->secondVtable = &PTR_LAB_00d73090;
    this->thirdVtable = &PTR_LAB_00d7308c;

    // --- Destroy sub-object at +0x50 (two steps) ---
    destroySubObjectPart1(&this->subObject); // FUN_004086d0
    destroySubObjectPart2(&this->subObject); // FUN_00408310

    // --- Delete child object if present ---
    if (this->childPointer != nullptr) {
        this->childDeleter(this->childPointer); // (*(code *)param_1[0x19])(param_1[0x16])
    }

    // --- Global cleanup ---
    globalCleanup(); // FUN_0046c640

    // --- Optionally free the object's memory ---
    if (shouldDelete & 1) {
        deallocate(this, 0x68); // FUN_0043b960 (size 0x68)
    }

    return this;
}