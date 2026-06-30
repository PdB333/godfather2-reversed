// FUNC_NAME: EARSObject::EARSObject(byte allocFlag)
// Function address: 0x00411c10
// Role: Constructor for EARSObject base class (EA EARS engine object)
// Sets up vtable pointers at offsets 0 and 0xC (multiple inheritance)
// Calls initialization functions and handles allocation flag

class EARSObject {
public:
    // vtable pointers
    void* __vftable;              // +0x00 primary vtable
    void* __vftable2;             // +0x0C secondary vtable (base class)
    // ... other members after

    // Constructor
    // param_1 is 'this' (implicit)
    // param_2: allocFlag – if bit 0 set, indicates heap-allocation for cleanup
    __thiscall EARSObject(byte allocFlag) {
        // Set primary vtable
        this->__vftable = &PTR_FUN_00e2f4c8;

        // Set secondary vtable to base class temporary
        this->__vftable2 = &PTR_LAB_00e2f4d8;

        // Initialize static/globals (likely factory registration)
        sub_408310(&DAT_01206a20);
        sub_408310(&DAT_01206a28);

        // Switch secondary vtable to final derived class
        this->__vftable2 = &PTR_LAB_00e2f4dc;

        // Reset global flag
        DAT_012233b8 = 0;

        // Post-construction call
        sub_4083D0();

        // If object was allocated with new, handle cleanup (e.g., placement delete)
        if (allocFlag & 1) {
            sub_9C8EB0(this);
        }

        return; // Note: actually returns 'this' via eax
    }
};