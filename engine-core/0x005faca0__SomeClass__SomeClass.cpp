// FUNC_NAME: SomeClass::SomeClass
// Address: 0x005faca0 - Constructor for SomeClass
// Calls base constructor at 0x005facc0, then optionally calls additionalInit at 0x009c8eb0

class BaseClass {
public:
    BaseClass(); // Constructor at 0x005facc0
};

class SomeClass : public BaseClass {
public:
    SomeClass(bool doInit);
private:
    void additionalInit(); // At 0x009c8eb0, called when doInit is true
};

SomeClass::SomeClass(bool doInit) : BaseClass() {
    if (doInit) {
        additionalInit();
    }
}