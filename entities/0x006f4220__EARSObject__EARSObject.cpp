// FUNC_NAME: EARSObject::EARSObject
// Function address: 0x006f4220 - Constructor for EARSObject (base object initialization)

class EARSObject {
public:
    EARSObject(unsigned char flags) {
        // Global initialization called unconditionally (FUN_006f4c60)
        baseInit();

        // If bit 0 of flags is set, perform additional construction steps (FUN_009c8eb0)
        if (flags & 1) {
            finalizeConstruction(this);
        }
    }
};