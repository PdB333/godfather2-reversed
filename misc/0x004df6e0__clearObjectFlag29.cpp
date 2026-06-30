// FUNC_NAME: clearObjectFlag29
// Clears bit 29 (0x20000000) of the flags field at offset 0xC in the object
// pointed to by *pObjPtr. pObjPtr is a pointer to a handle (pointer-to-pointer).
// Used to clear a pending update or dirty flag across many call sites.
void __fastcall clearObjectFlag29(int* pObjPtr)
{
    int* obj = (int*)*pObjPtr;
    if (obj != 0)
    {
        uint32_t* flags = (uint32_t*)((char*)obj + 0xC); // flags at +0xC
        *flags &= 0xDFFFFFFF; // clear bit 29
    }
}