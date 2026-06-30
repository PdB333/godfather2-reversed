// FUNC_NAME: TLSArrayOwner::~TLSArrayOwner
void __fastcall TLSArrayOwner::~TLSArrayOwner(undefined4* this)
{
    uint countA;
    uint countB;

    // Deallocate first array (elements of size 0xC) if count is valid (>=0)
    countA = this[7]; // +0x1C: count for array A (0xC element size)
    if (-1 < (int)countA)
    {
        TlsGetValue(DAT_01139810); // retrieve TLS context needed by deallocation
        FUN_00aa26e0(this[5], (countA & 0x3fffffff) * 0xc, 0x17); // +0x14: pointer to array A, size = count * 12, flag 0x17
    }

    // Deallocate second array (elements of size 0x30) if count is valid (>=0)
    countB = this[4]; // +0x10: count for array B (0x30 element size)
    if (-1 < (int)countB)
    {
        TlsGetValue(DAT_01139810);
        FUN_00aa26e0(this[2], (countB & 0x3fffffff) * 0x30, 0x17); // +0x08: pointer to array B, size = count * 48, flag 0x17
    }

    // Set vtable pointer for this class
    *this = &PTR_LAB_00d96914;
    return;
}