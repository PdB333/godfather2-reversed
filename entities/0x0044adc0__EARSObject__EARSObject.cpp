// FUNC_NAME: EARSObject::EARSObject
// Address: 0x0044adc0
// Role: Constructor for EARSObject. Calls base initialization, then if flags bit 0 is set, applies extra flags.

class EARSObject {
public:
    __thiscall EARSObject(unsigned char flags) {
        // Call base initialization (FUN_0044ade0)
        initBase(); 
        // If bit 0 of flags is set, perform additional setup (FUN_009c8eb0)
        if (flags & 1) {
            applyFlags(this);
        }
    }

    // Base init (0x0044ade0)
    void initBase(); 
    // Post-init with flags (0x009c8eb0)
    static void applyFlags(EARSObject* obj);
};