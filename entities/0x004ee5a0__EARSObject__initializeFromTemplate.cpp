// FUNC_NAME: EARSObject::initializeFromTemplate
void __thiscall EARSObject::initializeFromTemplate(int pEntity, int pTemplate) {
    int *pStackPtr;
    uint alignedPtr;
    int data1, data2, data3;

    // Store template reference at offset +0x24
    *(int *)(pEntity + 0x24) = pTemplate;

    // Allocate node in global object pool (DAT_01206880)
    // Pool structure at +0x14 holds pointer to free stack
    pStackPtr = (int *)*(int *)(DAT_01206880 + 0x14);
    // Write type descriptor / vtable link
    *(int *)*pStackPtr = (int)&PTR_LAB_01124c88;
    *pStackPtr += 4;  // advance stack
    // Store entity pointer
    *(int *)*pStackPtr = pEntity;
    // Align to 4-byte boundary (round up)
    alignedPtr = ((uint)(*pStackPtr + 7) & 0xfffffffc);
    *pStackPtr = alignedPtr;
    // Store template pointer in aligned slot
    *(int *)alignedPtr = pTemplate;
    *pStackPtr = alignedPtr + 4;

    // Read three transform components from template (position/rotation)
    int templ = *(int *)(pEntity + 0x24);  // pTemplate
    ushort flags = *(ushort *)(templ + 0x2c);

    // Swizzle based on orientation flag (0x200)
    if ((flags & 0x200) == 0) {
        data1 = *(int *)(templ + 0x24);   // default order
        data2 = *(int *)(templ + 0x20);
        data3 = *(int *)(templ + 0x28);
    } else {
        data1 = *(int *)(templ + 0x20);   // swapped order
        data2 = *(int *)(templ + 0x28);
        data3 = *(int *)(templ + 0x24);
    }

    // Finalize object (commit changes to engine)
    FUN_0048ee40();

    // Store final transform data into entity
    // offsets: +0x60, +0x64, +0x68 (likely translation/rotation axes)
    *(int *)(pEntity + 0x64) = data1;
    *(int *)(pEntity + 0x60) = data2;
    *(int *)(pEntity + 0x68) = data3;

    return;
}