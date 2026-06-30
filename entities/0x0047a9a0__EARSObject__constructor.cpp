// FUNC_NAME: EARSObject::constructor
// Function at 0x0047a9a0: Initializes an EARS engine object.
// Calls base class constructor, then sets vtable and additional virtual function pointers.
// Offsets: +0x00 = vtable pointer, +0x3C = pointer to secondary vtable or dispatch table, +0x48 = another pointer.

#include <cstdint>

class EARSObject {
public:
    // Vtable pointer at offset 0x00
    void* vtable;                     // +0x00

    // Fields at offsets 0x3C and 0x48 (in 4-byte units, i.e., 15th and 18th 4-byte slots)
    // These are likely pointers to other virtual function tables or type info.
    void* secondaryVtableOrDispatch;  // +0x3C
    void* tertiaryPtr;                // +0x48

    // Constructor
    EARSObject() {
        // Call base class constructor (likely sets up base vtable and members)
        // Address: 0x004cf640
        baseConstructor();

        // Set vtable pointer for this class (EARSObject)
        // Address: 0x00e33088
        this->vtable = reinterpret_cast<void*>(0x00e33088);

        // Set secondary vtable pointer (offset +0x3C)
        // Address: 0x00e330a8
        this->secondaryVtableOrDispatch = reinterpret_cast<void*>(0x00e330a8);

        // Set tertiary pointer (offset +0x48)
        // Address: 0x00e330b8
        this->tertiaryPtr = reinterpret_cast<void*>(0x00e330b8);
    }

private:
    void baseConstructor(); // Internal function at 0x004cf640
};

// Note: The actual function returns this pointer (undefined4*), but it's implicit in the constructor.