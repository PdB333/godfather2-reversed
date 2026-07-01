// FUNC_NAME: SomeDerivedClass::SomeDerivedClass
// Address: 0x00842020 - Constructor for a derived class with two base classes (vtable at +0x0 and +0x4)
// Primary vtable set to base1 (0xd74620) then overridden to derived (0xd74820) after initialization
// Secondary vtable (offset +0x4) set to base2 (0xd747f8)
// Fields at offsets 0x3C, 0x40, 0x44 initialized to zero

class SomeBaseClass1 {
public:
    // vtable at +0x0
};

class SomeBaseClass2 {
public:
    // vtable at +0x4
};

class SomeDerivedClass : public SomeBaseClass1, public SomeBaseClass2 {
public:
    // Offset +0x3C
    int field_0x3C;
    // Offset +0x40
    int field_0x40;
    // Offset +0x44
    int field_0x44;

    __thiscall SomeDerivedClass() {
        // Set primary vtable to base class 1 vtable
        this->vtable = (void**)0x00d74620;
        // Call base class 1 constructor (likely sets its vtable and initializes base members)
        baseConstructor1();
        // Set secondary vtable (offset 4) to base class 2 vtable
        *(void***)((char*)this + 4) = (void**)0x00d747f8;
        // Initialize derived fields
        this->field_0x3C = 0;
        this->field_0x40 = 0;
        this->field_0x44 = 0;
        // Override primary vtable to derived class vtable
        this->vtable = (void**)0x00d74820;
    }
};