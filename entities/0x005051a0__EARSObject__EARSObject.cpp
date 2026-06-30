// FUNC_NAME: EARSObject::EARSObject

class EARSObject {
public:
    __thiscall EARSObject(byte flags);
};

// Base class constructor stub (actual at 0x005051c0)
void __thiscall baseConstructor();

// Additional initialization function (actual at 0x009c8eb0)
void __thiscall additionalInit();

__thiscall EARSObject::EARSObject(byte flags) {
    // Call base class constructor (0x005051c0)
    baseConstructor();

    // If bit 0 of flags is set, perform additional initialization
    if ((flags & 1) != 0) {
        additionalInit();
    }

    // Return this pointer (implicitly in __thiscall)
}