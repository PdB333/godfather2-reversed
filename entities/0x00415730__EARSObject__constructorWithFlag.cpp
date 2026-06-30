// FUNC_NAME: EARSObject::constructorWithFlag
// Address: 0x00415730
// Purpose: Constructor that calls base initializer and optionally performs cleanup based on a flag.
//          Typically used in EA EARS engine for objects with conditional allocation/deallocation.
//          The flag (param_2) bit 0 indicates whether to call a cleanup/destroy function after base init.

class EARSObject {
public:
    // Base initializer at 0x00415760
    void baseInit(); // FUN_00415760

    // Cleanup/destroy function at 0x009c8eb0
    static void destroy(EARSObject* obj); // FUN_009c8eb0

    // Constructor with flag
    // param_2: bit0 = 1 to call destroy after baseInit (used for conditional placement new)
    EARSObject* __thiscall constructorWithFlag(byte param_2) {
        this->baseInit();
        if (param_2 & 1) {
            EARSObject::destroy(this);
        }
        return this;
    }
};