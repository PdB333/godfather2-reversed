// FUNC_NAME: UnknownEARSClass::~UnknownEARSClass
// Function address: 0x0067c630
// Destructor that calls two member destructors via stored function pointers,
// then sets the vtable pointer to a base class vtable (PTR_LAB_00d576d4) for chained destruction.

struct UnknownEARSClass {
    void** vtable;                                      // +0x00
    // +0x04, +0x08: unused in this function
    void* subObj2;                                      // +0x0C (param_1[3])
    // +0x10, +0x14: unused
    void (*destructor2)(void*);                         // +0x18 (param_1[6])
    void* subObj1;                                      // +0x1C (param_1[7])
    // +0x20, +0x24: unused
    void (*destructor1)(void*);                         // +0x28 (param_1[10])
};

void __thiscall UnknownEARSClass::~UnknownEARSClass() {
    // Destroy second subobject (if allocated)
    if (this->subObj1 != nullptr) {
        this->destructor1(this->subObj1);
    }
    // Destroy first subobject (if allocated)
    if (this->subObj2 != nullptr) {
        this->destructor2(this->subObj2);
    }
    // Chain to base class destructor by updating vtable
    this->vtable = (void**)&PTR_LAB_00d576d4;
}