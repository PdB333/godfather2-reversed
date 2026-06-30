// FUNC_NAME: Object::constructor
// Address: 0x005963d0
// Typical EA EARS constructor pattern: sets vtable, calls base initializer, then optionally calls destructor (for placement new cleanup).
// param_2: flag byte; bit 0 indicates whether the object was allocated and should be freed on failure (calls operator delete via FUN_009c8eb0? Actually it's likely a cleanup function).
// The vtable pointer is set to &PTR_FUN_00e3adf0 (vtable for this class).
// Callee FUN_00596650 is the base/init function.

class Object {
public:
    void* vtable; // +0x00 vtable pointer

    // Constructor
    Object(byte aFlag) {
        // Set vtable
        this->vtable = &PTR_FUN_00e3adf0; // vtable for Object class (or derived)
        // Call initialization routine (likely base constructor)
        FUN_00596650(); // Could be Object::init() and sets up base class data

        // If the object was allocated (not placement new), handle cleanup on exception? 
        // Typically: if (aFlag & 1) { operator delete(this); } or call a specific destructor
        if ((aFlag & 1) != 0) {
            FUN_009c8eb0(this); // Likely a destructor/cleanup function
        }
    }
};