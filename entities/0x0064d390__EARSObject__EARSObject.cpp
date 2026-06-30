// FUNC_NAME: EARSObject::EARSObject
// Function address: 0x0064d390
// Base class constructor: initializes vtable, zeroes two fields, stores two parameters

void __thiscall EARSObject::EARSObject(void* this, int valueA, int valueB)
{
    // +0x04: field1 = 0
    *(int*)((char*)this + 4) = 0;
    // +0x08: field2 = 0
    *(int*)((char*)this + 8) = 0;
    // +0x10: field4 = valueA (second parameter)
    *(int*)((char*)this + 16) = valueA;
    // +0x0C: field3 = valueB (third parameter)
    *(int*)((char*)this + 12) = valueB;
    // +0x00: vtable pointer (global vtable at 0x00e42df0)
    *(void**)this = (void*)&g_vtable_00e42df0;
}