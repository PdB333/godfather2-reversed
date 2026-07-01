// FUNC_NAME: SomeObject::constructor

// Address: 0x00858550
// Role: Constructor for an object with vtable at 0x00e315b0 (likely a derived class in EARS engine).
// Calls base constructor (FUN_004149b0) and conditionally calls a cleanup/deallocation function (FUN_009c8eb0) if ctorFlags bit 0 is set.
// Returns this pointer.

class SomeObject
{
public:
    // Constructor with allocation flag
    SomeObject* __thiscall constructor(byte ctorFlags)
    {
        // Set vtable to class-specific table
        *(void**)this = (void*)&PTR_LAB_00e315b0; // +0x00 vtable pointer

        // Call base class constructor (likely common base)
        FUN_004149b0(); // base class construction

        // If bit 0 of ctorFlags is set, perform deallocation (e.g., operator delete or custom free)
        if ((ctorFlags & 1) != 0)
        {
            FUN_009c8eb0(this); // deallocation function
        }

        return this;
    }
};