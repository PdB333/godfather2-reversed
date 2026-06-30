// FUNC_NAME: GameNetObject::storeClientData
void __fastcall GameNetObject::storeClientData(int thisPtr)
{
    undefined4 value1;
    undefined4 value2;
    int *pIterator;

    value1 = *(undefined4 *)(thisPtr + 0x14);  // +0x14: some float/int field
    pIterator = (int *)(DAT_01206880 + 0x14);  // +0x14: offset into global data buffer
    value2 = *(undefined4 *)(thisPtr + 0x20);  // +0x20: another field

    // Write vtable pointer (PTR_LAB_011273b8) at iterator position
    *(undefined ***)*pIterator = &PTR_LAB_011273b8;
    *pIterator = *pIterator + 4;

    // Store value2 (from offset 0x20)
    *(undefined4 *)*pIterator = value2;
    *pIterator = *pIterator + 4;

    // Store value1 (from offset 0x14)
    *(undefined4 *)*pIterator = value1;
    *pIterator = *pIterator + 4;

    // Copy field at +0x18 to +0x0C (seems like a local copy/validation)
    *(undefined4 *)(thisPtr + 0xc) = *(undefined4 *)(thisPtr + 0x18);
    return;
}