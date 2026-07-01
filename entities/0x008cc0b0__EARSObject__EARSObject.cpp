// FUNC_NAME: EARSObject::EARSObject
// Address: 0x008cc0b0
// Role: Constructor for base EARS engine object. Sets vtable, calls base constructor, then optionally deletes self if allocation flag is set.

// Forward declarations (assumed external)
void __fastcall baseConstructor(void); // FUN_008cf910
void __fastcall deallocateSelf(void* this); // FUN_009c8eb0

// Vtable symbol (from vtable pointer at 0x00d7c328)
extern void* __ptr32 vtable_EARSObject; // PTR_FUN_00d7c328

// Class definition (partial)
class EARSObject {
public:
    void* vfptr; // +0x00 vtable pointer

    // Constructor with allocation flag (param_2 & 1 indicates heap allocation)
    // Returns 'this' for chaining.
    void* __thiscall constructor(byte allocFlag) {
        // Set vtable
        this->vfptr = &vtable_EARSObject;

        // Call base class constructor (assumed from FUN_008cf910)
        baseConstructor();

        // If object was heap-allocated (flag bit 0 set), call deallocation routine
        // This is typical pattern for EA engine constructors: if allocation fails or needs cleanup.
        if ((allocFlag & 1) != 0) {
            deallocateSelf(this);
        }

        return this;
    }
};