// FUNC_NAME: EARSObject::construct(unsigned char flags)

class EARSObject {
public:
    // Initializes base class members (called regardless)
    void initBase(); // FUN_004c27f0

    // Full cleanup/destructor (called if flags & 1)
    void destroy(); // FUN_009c8eb0

    // Constructs object in place with optional full reset
    // param_1: this (__thiscall)
    // param_2: flags – if bit 0 set, calls destroy() after init
    __thiscall EARSObject* construct(unsigned char flags) {
        initBase();                                  // Always call base initializer
        if (flags & 1) {
            destroy();                               // Optional cleanup before return
        }
        return this;                                 // Return constructed object
    }
};