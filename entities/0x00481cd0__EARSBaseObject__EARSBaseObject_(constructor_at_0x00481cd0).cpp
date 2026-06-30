// FUNC_NAME: EARSBaseObject::EARSBaseObject (constructor at 0x00481cd0)

int __thiscall EARSBaseObject::EARSBaseObject(EARSBaseObject *this, byte allocFlag)
{
    // Set virtual function table pointer at offset +0x28
    *(void ***)(this + 0x28) = &gEARSBaseObjectVtable;  // PTR_LAB_00e317cc

    // Call base class constructor (likely for some core object)
    baseConstructor();  // FUN_004530e0

    // If allocFlag has bit 0 set, call deallocation helper (probably for heap-allocated objects)
    if ((allocFlag & 1) != 0) {
        heapDeallocHelper(this);  // FUN_009c8eb0
    }

    return (int)this;
}