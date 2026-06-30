// FUNC_NAME: EARSObject::EARSObject
// Address: 0x00721700
// Constructor for a base EA EARS object (likely EARS::Framework::Object or similar)
// Object size: 0xA0 bytes

// Vtable pointers (based on offsets):
// +0x00: vtable for main class (PTR_FUN_00d62028)
// +0x3C (0xF*4): secondary vtable (PTR_LAB_00d62018)
// +0x48 (0x12*4): another vtable (PTR_LAB_00d62014)
// +0x68 (0x1A*4): sub-object vtable (initially PTR_LAB_00d62010, later overridden to PTR_LAB_00e32854)
// +0x6C (0x1B*4): sub-object (calls constructors FUN_004086d0 and FUN_00408310)

class EARSObject {
public:
    // Constructor
    // param_2: flag (bit 0) indicating if this object was heap-allocated and should be freed on failure?
    // Returns this pointer.
    __thiscall EARSObject(byte flags) {
        // Set vtable for main class
        *(void**)this = (void*)&PTR_FUN_00d62028;          // +0x00

        // Set secondary vtables
        this->vtable1 = (void*)&PTR_LAB_00d62018;          // +0x3C (offset 0xF)
        this->vtable2 = (void*)&PTR_LAB_00d62014;          // +0x48 (offset 0x12)
        this->vtable3 = (void*)&PTR_LAB_00d62010;          // +0x68 (offset 0x1A)

        // Initialize subobject at offset +0x6C
        FUN_004086d0(&this->subObject);                   // probably constructor for base subobject
        FUN_00408310(&this->subObject);                   // probably additional init for same subobject

        // Override the vtable at +0x68 to a different one
        this->vtable3 = (void*)&PTR_LAB_00e32854;         // +0x68

        // Global initialization (e.g., singleton access or reference counting)
        FUN_0099d180();

        // If flags indicate heap-allowed, deallocate? (unusual pattern, maybe custom cleanup)
        if (flags & 1) {
            FUN_0043b960(this, 0xA0);                     // operator delete(this, sizeof(EARSObject))
        }

        // Return this pointer
        return this;
    }

private:
    // Placeholder members for known offsets
    // Offset 0x00: vtable (main)
    // Offset 0x3C: void* vtable1
    // Offset 0x48: void* vtable2
    // Offset 0x68: void* vtable3
    // Offset 0x6C: SomeSubObject subObject; // size unknown
    // ... rest up to 0xA0 bytes
};