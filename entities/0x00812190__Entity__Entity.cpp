// FUNC_NAME: Entity::Entity
// Address: 0x00812190
// Constructor for Entity base class. Calls base class initializer (likely EARSObject::EARSObject) with the given parameter.
// Object layout (dword offsets):
// +0x00: vtable pointer (PTR_FUN_00d72fc0)
// +0x3C: pointer to base class vtable (PTR_LAB_00d72fb0)
// +0x48: pointer to another base vtable (PTR_LAB_00d72fac)
// +0x50: field_0x50
// +0x54: field_0x54
// +0x58 through +0x6C: six consecutive zeroed fields (maybe an array of 6 ints)

Entity* __thiscall Entity::Entity(uint param)
{
    // Base class constructor (likely EARSObject::EARSObject or similar)
    BaseClass::BaseClass(param);

    // Zero out three initial fields
    this->field_0x50 = 0;
    this->field_0x54 = 0;

    // Set vtable for this class
    this->vtable = (void*)&vtable_Entity; // PTR_FUN_00d72fc0

    // Set base class vtable pointers for multiple inheritance
    this->baseVtable1 = (void*)&baseVtable1; // PTR_LAB_00d72fb0
    this->baseVtable2 = (void*)&baseVtable2; // PTR_LAB_00d72fac

    // Zero out block of six fields (likely an array of flags or counters)
    this->field_0x58 = 0;
    this->field_0x5C = 0;
    this->field_0x60 = 0;
    this->field_0x64 = 0;
    this->field_0x68 = 0;
    this->field_0x6C = 0;

    return this;
}