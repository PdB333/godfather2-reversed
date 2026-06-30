// FUNC_NAME: EARSBaseObject::destructor
void __thiscall EARSBaseObject::destructor(byte flags)
{
    // Release sub-object at this+0x1C if present
    if (this->subObj1 != 0) {
        // Call release function at this+0x28 (vtable entry)
        (this->subObj1->release)(this->subObj1);
    }
    // Release sub-object at this+0x0C if present
    if (this->subObj2 != 0) {
        // Call release function at this+0x18
        (this->subObj2->release)(this->subObj2);
    }
    // Set vtable to base class vtable (EA_RTTI pointer 0x00d576d4)
    this->vtable = (int*)&VTABLE_EARSBaseObject;
    // If bit 0 set, deallocate memory
    if ((flags & 1) != 0) {
        operatorDelete(this);
    }
}