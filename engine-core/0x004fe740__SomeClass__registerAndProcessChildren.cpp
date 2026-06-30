// FUNC_NAME: SomeClass::registerAndProcessChildren
void __fastcall SomeClass::registerAndProcessChildren(SomeClass* this)
{
    // Write vtable and object pointer into global registration slot at offset 0x14
    int* pSlot = (int*)(DAT_01206880 + 0x14);
    pSlot[0] = (int)&PTR_LAB_01124ee0; // vtable for this object type
    pSlot[1] = (int)this;              // object pointer

    // Process children: call processOneChild for each item (count at +0x3c)
    int childCount = *(int*)((int)this + 0x3c);
    for (int i = 0; i < childCount; i++)
    {
        processOneChild((int)this);
    }
}