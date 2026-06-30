// FUN_004e52b0: EARSBaseObject::EARSBaseObject(uint8 flags)
// Constructor for base EARS object. Calls a global base initializer, then optionally registers the object if the low bit of flags is set.

// Global helper functions provided by the engine
extern void earsBaseConstructor();        // 0x004e4f40
extern void earsRegisterObject(void*);    // 0x009c8eb0

class EARSBaseObject {
public:
    EARSBaseObject(uint8_t flags);
};

EARSBaseObject::EARSBaseObject(uint8_t flags) {
    // Invoke engine-wide base object initialisation
    earsBaseConstructor();

    // If the registration flag is set, register this object with the game manager
    if (flags & 1) {
        earsRegisterObject(this);
    }
}