// FUNC_NAME: EARSObject::constructor
// Address: 0x0072d270
// Reconstruction of a base object constructor in the EA EARS engine.
// The function is __thiscall, returns the `this` pointer.
// param_2 (byte) is a flag: bit0 controls whether additional initialization (vtable setup?) is performed.

class EARSObject {
public:
    // Constructor with optional vtable/reference initialization
    // This is the actual implementation at 0x0072d270
    EARSObject* constructor(byte allocFlag) {
        // Call base initialization (common to all objects)
        baseInit();  // called at 0x0090c670

        // If the allocation flag has bit 0 set, perform extra init
        if (allocFlag & 1) {
            initVTable(this);  // called at 0x009c8eb0 – possibly sets up vtable or ref count
        }

        return this; // returns the constructed object pointer
    }

private:
    void baseInit();       // placeholder for common init routine
    void initVTable(EARSObject* obj); // placeholder for vtable/reference setup
};