// FUNC_NAME: SomeClass::constructor
// Address: 0x005be540
// Likely constructor for a class derived from BaseClass. The byte parameter indicates
// whether the object was heap-allocated (bit 0 set) – if so, a cleanup function is called
// (likely operator delete or a deallocator) after the base constructor call.

class SomeClass : public BaseClass {
public:
    SomeClass(byte allocationFlag);
};

SomeClass::SomeClass(byte allocationFlag) {
    // Set vtable pointer (0x00e3e52c)
    this->vtable = &SomeClass_vtable;
    // Call base class constructor (0x0049c640)
    BaseClass::baseConstructor();
    // If heap-allocated, free memory (0x009c8eb0)
    if (allocationFlag & 1) {
        operator delete(this);
    }
}