// FUNC_NAME: SomeObject::SomeObject(int, int)
// Address: 0x008a6510
// Role: Constructor for a reference-counted object with two integer parameters.
// The object size is 0x28 (40 bytes). It uses a custom allocator and reference counting.
// Vtable pointers are set at offsets 0x00, 0x18 (piVar2[6]), and 0x1C (piVar2[7]).
// The reference count is at offset 0x08 (piVar2[2]).
// Parameters param_1 and param_2 are stored at offsets 0x20 (piVar2[8]) and 0x24 (piVar2[9]).

#include <cstddef>

// Forward declarations for external functions
void* __cdecl customAlloc(size_t size);           // FUN_009c8e50
void __cdecl refCountIncrement(int a, int b);     // FUN_004b1da0
void __cdecl refCountDecrement();                 // FUN_004b1e60

// Vtable symbols (external)
extern void* PTR_LAB_00d79a04;   // Primary vtable
extern void* PTR_LAB_00d799ec;   // Secondary vtable
extern void  LAB_008a6050;       // Function pointer or code label

class SomeObject {
public:
    // Vtable pointer (offset 0x00)
    void** vtable;

    // Unknown fields (offsets 0x04, 0x08, 0x0C, 0x10, 0x14, 0x18, 0x1C, 0x20, 0x24)
    // Based on decompiled offsets:
    // piVar2[1] = offset 0x04
    // piVar2[2] = offset 0x08 (reference count)
    // piVar2[3] = offset 0x0C
    // piVar2[4] = offset 0x10
    // piVar2[5] = offset 0x14 (pointer to secondary vtable)
    // piVar2[6] = offset 0x18 (secondary vtable pointer)
    // piVar2[7] = offset 0x1C (function pointer to LAB_008a6050)
    // piVar2[8] = offset 0x20 (param_1)
    // piVar2[9] = offset 0x24 (param_2)

    int field_0x04;
    int refCount;          // +0x08
    int field_0x0C;
    int field_0x10;
    void* secondaryVtablePtr; // +0x14 (points to +0x18)
    void* secondaryVtable;   // +0x18
    void* funcPtr;           // +0x1C (points to LAB_008a6050)
    int storedParam1;        // +0x20
    int storedParam2;        // +0x24

    // Constructor
    SomeObject(int param1, int param2);
    // Destructor (called via vtable offset 8)
    ~SomeObject();
};

// Constructor implementation
SomeObject::SomeObject(int param1, int param2) {
    // Allocate memory for the object (size 0x28 = 40 bytes)
    SomeObject* obj = static_cast<SomeObject*>(customAlloc(0x28));
    if (obj != nullptr) {
        // Initialize reference counting (first call)
        refCountIncrement(1, 1);

        // Set vtable pointers
        obj->vtable = &PTR_LAB_00d79a04;          // Primary vtable
        obj->secondaryVtable = &PTR_LAB_00d799ec; // Secondary vtable
        obj->funcPtr = &LAB_008a6050;             // Function pointer
        obj->secondaryVtablePtr = &obj->secondaryVtable; // Points to secondary vtable

        // Increment reference count (second increment)
        obj->refCount++;

        // Store parameters
        obj->storedParam2 = param2;
        obj->storedParam1 = param1;

        // Decrement reference count (balance)
        refCountDecrement();

        // If reference count becomes zero after decrement, destroy the object
        if (obj->refCount == 0) {
            // Call destructor via vtable (offset 8)
            (*(void (**)(SomeObject*))(obj->vtable[2]))(obj);
        }
    }
}