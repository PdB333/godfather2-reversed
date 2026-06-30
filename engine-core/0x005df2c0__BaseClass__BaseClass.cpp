// FUNC_NAME: BaseClass::BaseClass
// Function address: 0x005df2c0
// Role: Constructor for a base class; initializes vtable and calls base constructor.
//       If the flags parameter has bit 0 set, performs additional cleanup (likely for dynamic allocation).

// External reference to vtable
extern void* PTR_FUN_00e3f2c8;

// Forward declarations for unknown functions
extern void FUN_004de130();  // Likely base class constructor
extern void FUN_009c8eb0(void* obj); // Likely destructor or cleanup

class BaseClass {
public:
    // Constructor: takes a flags byte (bit 0 indicates dynamic allocation)
    // Equivalent to: BaseClass(bool isDynamic) { ... }
    BaseClass(byte flags);
    // Destructor assumed virtual from vtable
};

BaseClass::BaseClass(byte flags) {
    // Set virtual function table pointer
    this->vtable = &PTR_FUN_00e3f2c8;  // +0x00: virtual table address
    
    // Call base class constructor (possibly initializing parent members)
    FUN_004de130(); // Base initializer
    
    // If the object was dynamically allocated (bit 0 set), call cleanup
    if (flags & 1) {
        FUN_009c8eb0(this); // Likely destructor or deallocation function
    }
}