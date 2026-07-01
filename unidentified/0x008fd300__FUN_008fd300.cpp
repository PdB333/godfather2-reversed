// FUNC_NAME: SomeClass::SomeClass
// Function at 0x008fd300 - Constructor with flag parameter
// Calls base class default constructor, then optionally calls destructor if flag & 1

SomeClass* __thiscall SomeClass::SomeClass(SomeClass* this, byte flag) {
    // Call base class constructor (at 0x008fcda0)
    BaseClass::BaseClass();
    
    // If flag bit 0 is set, call destructor (at 0x009c8eb0)
    if (flag & 1) {
        this->~SomeClass();
    }
    
    return this;
}