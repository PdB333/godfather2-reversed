// FUNC_NAME: UnknownClass::constructor
// Function at 0x00836650: Constructor for an unknown class with vtable at 0x00d73738.
// Sets a float member at offset 0x4c (this[0x13]) from a source object's float at the same offset,
// scaled by a factor parameter. Also calls a base constructor (FUN_008334a0).
// Note: The global _DAT_00d5780c is used as an initial default but immediately overwritten.

struct UnknownClass {
    void* vtable;              // +0x00
    // ... other members ...
    float someFloat;           // +0x4c (this[0x13])
    // ... rest of class ...
};

// Base constructor (FUN_008334a0) - assumed to be a void function.
extern void __thiscall baseConstructor(UnknownClass* this);

// Vtable pointer (likely defined elsewhere)
extern void* PTR_LAB_00d73738;
// Global default value (float) at 0x00d5780c
extern float _DAT_00d5780c;

UnknownClass* __thiscall UnknownClass::constructor(UnknownClass* this, float factor, UnknownClass* source) {
    // Call base class constructor
    baseConstructor(this);
    
    // Set vtable pointer to derived class vtable
    this->vtable = PTR_LAB_00d73738;
    
    // Initialize float member at offset 0x4c with global default (likely 0.0f or some constant)
    this->someFloat = _DAT_00d5780c;
    
    // Overwrite with scaled value from source object's same member
    this->someFloat = source->someFloat * factor;
    
    return this;
}