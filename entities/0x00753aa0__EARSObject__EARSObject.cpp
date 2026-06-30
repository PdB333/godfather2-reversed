// FUNC_NAME: EARSObject::EARSObject
// Function at 0x00753aa0: Constructor for EARSObject with initialization flags.
// When bit 0 of flags is set, a destructor-like cleanup is called after base init.

class EARSObject {
public:
    // Constructor takes a byte parameter for initialization flags.
    // Calls base initializer (FUN_00752e00), then conditionally calls cleanup (FUN_00624da0) if (flags & 1) != 0.
    EARSObject(byte flags) {
        // Call base class or member initialization routine (0x00752e00)
        BaseInit(); // replaced FUN_00752e00

        // If the lowest bit of flags is set, perform a cleanup/destructor call on this instance
        if ((flags & 1) != 0) {
            CleanupOnBit1(); // replaced FUN_00624da0
        }
    }

private:
    void BaseInit();      // placeholder for 0x00752e00
    void CleanupOnBit1(); // placeholder for 0x00624da0
};