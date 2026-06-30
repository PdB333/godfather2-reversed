// FUNC_NAME: SomeClass::releaseManagedObjects
// Address: 0x00621f80
// This function releases two referenced sub-objects by calling their release methods
// (virtual functions at index 1) and then calls cleanup (index 3) on the parent interfaces.
// Offsets relative to this: +0x4 (vtableA), +0x8 (objA), +0xc (vtableB), +0x10 (objB).

void __thiscall SomeClass::releaseManagedObjects()
{
    if (mObjB)
    {
        mInterfaceB->Release(mObjB, 0);
        mObjB = 0;
    }
    mInterfaceB->Cleanup();

    if (mObjA)
    {
        mInterfaceA->Release(mObjA, 0);
        mObjA = 0;
    }
    mInterfaceA->Cleanup();
}