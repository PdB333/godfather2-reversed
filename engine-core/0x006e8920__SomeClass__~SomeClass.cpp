// FUNC_NAME: SomeClass::~SomeClass
// Address: 0x006e8920
// Destructor for SomeClass. Sets vtable to derived class, calls base destructor if base pointer exists, then sets vtable to base class vtable.
class SomeClass {
    // +0x00: vtable pointer (implicit)
    // +0x0C: pointer to base class subobject (m_pBase)
    void* m_pBase;
public:
    void __thiscall ~SomeClass();
};

void __thiscall SomeClass::~SomeClass() {
    // Set vtable to derived class vtable
    this->vtable = &PTR_FUN_00d5fb78;
    if (this->m_pBase != nullptr) {
        // Call base class destructor with delete flag 1
        typedef void (__thiscall* BaseDtor)(int);
        BaseDtor dtor = *(BaseDtor*)this->m_pBase;
        dtor(1);
    }
    // Set vtable to base class vtable (post-destruction state)
    this->vtable = &PTR_LAB_00e2f638;
}