// FUNC_NAME: EARSObject::~EARSObject

// Destructor for EARSObject (or derived class)
// Vtable pointer at offset +0x00
// Embedded subobject (e.g., animation controller) at offset +0x54
// Part of EA EARS engine (The Godfather 2, 2008)
void __thiscall EARSObject::~EARSObject(byte deleteFlag)
{
    // Set vtable to base class destructor vtable (prevents re‑destruction)
    // PTR_LAB_00d6402c is the base class vtable
    this->vtable = &EARSObject_vtable_base; // +0x00

    // Check if the embedded subobject at +0x54 is initialised
    // The first DWORD of the subobject is used as a validity flag
    if (*(uint32*)((char*)this + 0x54) != 0)
    {
        // Call destructor on the subobject (function at 0x004daf90)
        ((void (__thiscall*)(void*))0x004daf90)((char*)this + 0x54);
    }

    // Call base class destructor / cleanup (function at 0x004ac1e0)
    ((void (__thiscall*)())0x004ac1e0)();

    // If the deletion flag is set, free memory via operator delete (function at 0x00624da0)
    if ((deleteFlag & 1) != 0)
    {
        ((void (__thiscall*)(void*))0x00624da0)(this);
    }

    // Destructor returns this (compiler convention)
    return this;
}