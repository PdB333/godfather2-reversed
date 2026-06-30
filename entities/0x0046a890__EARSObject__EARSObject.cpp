// FUNC_NAME: EARSObject::EARSObject

extern void * VTABLE_00e3269c;
extern void * VTABLE_00e30ea0;

// Forward declarations
void __thiscall BaseClassConstructor(void *this);  // FUN_0043e380
void __thiscall DeallocationFunction(void *this);  // FUN_009c8eb0

class EARSObject {
public:
    void *vtable; // +0x00

    // Constructor with heap allocation flag (bit 0 set = allocated with new)
    static EARSObject* __thiscall constructor(EARSObject *this, byte allocFlag);
};

EARSObject* __thiscall EARSObject::constructor(EARSObject *this, byte allocFlag) {
    // Set vtable to base class (intermediate virtual table)
    this->vtable = &VTABLE_00e3269c;
    // Call base class constructor
    BaseClassConstructor(this);
    // Override vtable to this class's final virtual table
    this->vtable = &VTABLE_00e30ea0;
    // If the object was heap-allocated (allocFlag & 1), call deallocation function
    // Note: This likely handles placement new cleanup/deletion on construction failure
    if (allocFlag & 1) {
        DeallocationFunction(this);
    }
    return this;
}