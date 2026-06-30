// FUNC_NAME: DerivedClass::~DerivedClass (destructor at 0x0073d940)
// Role: Destructor that sets vtable to base class, deletes two owned sub-objects (offsets 0x5C, 0x64), then calls a global base cleanup function.

#include <cstddef> // for nullptr

// VTable pointer (base class vtable for this class)
extern void* PTR_LAB_00d63778;

// Global base destructor or memory deallocation function (from FUN_0080ea60)
void __cdecl baseDestructor(void);

// Helper to delete a sub-object (from FUN_004daf90, likely destructor or operator delete)
void __fastcall destroySubObject(void* ptr);

// This function implements the destructor for a derived class.
// The object has the following layout:
// +0x00: vtable pointer
// +0x5C: m_pSubObject1 (void*) - first owned sub-object
// +0x64: m_pSubObject2 (void*) - second owned sub-object
void __fastcall DerivedClass_Destructor(void* param_1) {
    // Set vtable to base class's vtable to prevent calls to derived virtual functions
    *(void**)param_1 = &PTR_LAB_00d63778;

    // Destroy sub-object 1 (if allocated)
    if (*(void**)((char*)param_1 + 0x5C) != nullptr) {
        destroySubObject(*(void**)((char*)param_1 + 0x5C));
    }

    // Destroy sub-object 2 (if allocated)
    if (*(void**)((char*)param_1 + 0x64) != nullptr) {
        destroySubObject(*(void**)((char*)param_1 + 0x64));
    }

    // Call global base destructor/cleanup
    baseDestructor();
}