// FUNC_NAME: ResourceObject::loadData
void __fastcall ResourceObject::loadData(void *this)
{
    // Check if already loaded (bit 0 of flags at +0x5c)
    if ((*(byte *)((int)this + 0x5c) & 1) == 0)
    {
        // Global pointer to some resource buffer (e.g., audio/tex data)
        if (DAT_012069c4 != 0)
        {
            // Copy data from global buffer into this object (size 0x8000 = 32KB)
            FUN_00408900(this, &DAT_012069c4, 0x8000);
        }
        // Mark as loaded
        *(ushort *)((int)this + 0x5c) = *(ushort *)((int)this + 0x5c) | 1;
    }
}