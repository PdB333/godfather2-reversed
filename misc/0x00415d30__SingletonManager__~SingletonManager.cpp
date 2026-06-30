// FUNC_NAME: SingletonManager::~SingletonManager
// Function address: 0x00415d30
// Destructor for the singleton manager.  Sets the vtable to the current class,
// destroys a contained subobject, then sets the vtable to a base class, clears
// the global singleton flag, and optionally deallocates memory.

#include <cstdint>

// Forward declaration for the vtable pointers
extern void* PTR_FUN_00e2f7b0;   // vtable for SingletonManager (current class)
extern void* PTR_LAB_00e2f7b4; // vtable for BaseSingletonManager (base class)

// Global flag indicating if the singleton exists
extern int32_t g_singletonManagerActive; // DAT_012233c4

// Operator delete (provided by the engine)
void __fastcall operatorDelete(void* ptr); // FUN_009c8eb0

// The subobject that is managed (probably a contained class)
// Structure offset: +0x04 (pointer to a subobject)
// The subobject has its own vtable and functions at offsets +0x04 and +0x0C.
struct SubObject;
// vtable: offset +0x04 -> SubObject::destroyWithFlag(int, bool)
// vtable: offset +0x0C -> SubObject::release()

class SingletonManager {
public:
    // vtable pointer at +0x00
    void* __vfptr; // PTR_FUN_00e2f7b0 or PTR_LAB_00e2f7b4

    // +0x04: pointer to subobject (could be a contained class or base)
    SubObject* subObject;

    // +0x08: some integer parameter passed to subobject destructor
    int32_t subObjectParam;

    // Destructor – note that this is __thiscall with an implicit bool flag
    // (in EDX) indicating whether to call operator delete at the end.
    void __thiscall ~SingletonManager(bool deleteFlag);
};

void __thiscall SingletonManager::~SingletonManager(bool deleteFlag) {
    // Set vtable to current class (indicating we are in the destructor)
    this->__vfptr = &PTR_FUN_00e2f7b0;

    // Call subobject's destructor: subObject->someDestructor(subObjectParam, 0)
    // The vtable offset +0x04 points to a function that takes (int, bool)
    if (this->subObject != nullptr) {
        void* subVtable = *(void**)this->subObject; // subobject's vtable
        void (*destroyFunc)(int32_t, bool) = *(void (**)(int32_t, bool))((uint8_t*)subVtable + 4);
        destroyFunc(this->subObjectParam, false); // false = do not delete subobject yet
    }

    // If subobject still exists, call its release function (vtable offset +0x0C)
    if (this->subObject != nullptr) {
        void* subVtable = *(void**)this->subObject;
        void (*releaseFunc)() = *(void (**)())((uint8_t*)subVtable + 12);
        releaseFunc();
    }

    // Switch vtable to base class (for proper destruction order)
    this->__vfptr = &PTR_LAB_00e2f7b4;

    // Clear the global singleton flag
    g_singletonManagerActive = 0;

    // Optionally delete memory if the flag is set
    if ((deleteFlag & 1) != 0) {
        operatorDelete(this);
    }
}