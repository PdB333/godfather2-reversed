// FUNC_NAME: SomeClass::~SomeClass
// Function address: 0x00747390
// Role: Destructor - cleans up internal pointer then calls base destructor

// Note: This is a __thiscall method; the this pointer is passed in ecx.
// The vtable pointer at offset 0x00 is set to a base class vtable.
// A pointer at offset 0x54 (index 0x15) may be freed if non-null.
// Then a base class destructor is invoked (likely from EARS framework).

class SomeClass {
public:
    void *vtable;                // +0x00
    // ... other members ...
    void *unknownPtr0x54;        // +0x54 (index 0x15)
    // ...
};

void __thiscall SomeClass::~SomeClass(SomeClass *this) {
    // Set vtable to base class vtable to ensure proper virtual dispatch during destruction chain
    this->vtable = (void*)&VRAM_BASE_VTABLE; // PTR_LAB_00d6402c

    // Free the pointer at offset 0x54 if it exists
    if (this->unknownPtr0x54 != NULL) {
        FUN_004daf90(this->unknownPtr0x54); // Likely delete or release
    }

    // Call base class destructor
    FUN_004ac1e0(); // Typically EARS base destructor
}