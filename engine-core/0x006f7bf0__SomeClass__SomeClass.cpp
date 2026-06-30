// FUNC_NAME: SomeClass::SomeClass
// Function address: 0x006f7bf0
// Role: Constructor with conditional cleanup flag

class SomeClass {
public:
    SomeClass(byte flags);
private:
    void baseInit();  // FUN_006f7b80
    void cleanup();   // FUN_009c8eb0
};

SomeClass::SomeClass(byte flags) {
    baseInit();
    if (flags & 1) {
        cleanup();
    }
    // Note: 'this' is returned implicitly, as seen in the assembly.
}