// FUNC_NAME: UnknownClass::UnknownClass (constructor)
// Address: 0x005fc9e0
// This function is a constructor for an unknown class. It calls a base constructor (FUN_005fc970) and then conditionally calls an additional initialization function (FUN_009c8eb0) if the given byte flag has bit 0 set.
// Return value is the this pointer.

class UnknownClass {
public:
    // Constructor with flag parameter (byte), likely used to control initialization behavior.
    UnknownClass *__thiscall UnknownClass(byte flag) {
        // Call base class constructor or common initialization routine
        FUN_005fc970();

        // If the lowest bit of flag is set, perform additional initialization
        if ((flag & 1) != 0) {
            FUN_009c8eb0(this);
        }

        return this;
    }
};