// FUNC_NAME: SomeClass::SomeClass
// Address: 0x004cb420
// Role: Constructor with optional initialization flag

class SomeClass {
public:
    // __thiscall
    SomeClass* SomeClass(byte flags) {
        // Call base initializer (likely zeros memory or calls parent constructor)
        FUN_004cb490();
        // If bit 0 of flags is set, perform additional initialization (e.g., register component)
        if ((flags & 1) != 0) {
            FUN_009c8eb0(this);
        }
        return this;
    }
};