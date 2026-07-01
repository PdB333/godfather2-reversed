// FUNC_NAME: SomeClass::SomeClass
// 0x009580c0: Constructor for a derived class (size 0x70 = 112 bytes)
// Calls base constructor then conditionally handles heap-allocated objects

void * __thiscall SomeClass::SomeClass(void *this, byte flags) {
    // Call base class constructor (FUN_00958030 likely BaseClass::BaseClass())
    FUN_00958030();

    // If the object was allocated on the heap (bit0 set), call a cleanup/deallocation function
    // FUN_0043b960 may be operator delete or a destructor stub
    // 0x70 is the object size (112 bytes)
    if (flags & 1) {
        FUN_0043b960(this, 0x70);
    }

    return this; // constructor returns this
}