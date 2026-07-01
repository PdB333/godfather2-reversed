// FUNC_NAME: SomeClass::SomeClass
// Address: 0x00818320 - Constructor for a large class (size 0x1E0)
// Sets up vtable pointers and calls base constructor, then conditionally deletes if heap-allocated.

#include <cstdint>

class SomeClass {
public:
    // Vtable pointers (offsets: +0x00, +0x3C? actually 15*4=0x3C, 18*4=0x48)
    void* vtable;           // +0x00 -> PTR_FUN_00d73204
    // padding...
    void* field_0x3C;       // +0x3C (0x0F) -> PTR_LAB_00d731f4
    void* field_0x48;       // +0x48 (0x12) -> PTR_LAB_00d731f0
    // ... size 0x1E0 total

    // Constructor
    // param_2: bit 0 set if allocated via operator new (heap) – triggers cleanup on failure?
    __thiscall SomeClass(byte param_2) {
        vtable = &PTR_FUN_00d73204;       // Primary vtable
        field_0x3C = &PTR_LAB_00d731f4;   // Secondary vtable or function pointer
        field_0x48 = &PTR_LAB_00d731f0;   // Another vtable/function pointer

        // Call base class constructor (likely EARS base object)
        FUN_0046c640();  // Base::Base()

        // If heap-allocated and construction fails, delete this
        if ((param_2 & 1) != 0) {
            // operator delete(this, 0x1E0) – custom sized delete
            FUN_0043b960(this, 0x1E0);
        }
    }
};