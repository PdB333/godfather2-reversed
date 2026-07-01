// FUNC_NAME: SomeManager::updateCountAndFlag
void __thiscall SomeManager::updateCountAndFlag(void *this)
{
    // Check if bit 2 of flags at offset 0x80 is clear
    if (((*(uint8_t *)((uintptr_t)this + 0x80) >> 2) & 1) == 0)
    {
        // If global pointer is non-null, call a function on the base object (this - 0x14)
        if (g_pSomeGlobal != 0)
        {
            someFunction((void *)((uintptr_t)this - 0x14), &g_pSomeGlobal, 0x8000);
        }
        // Increment counter at offset 0x84
        *(int32_t *)((uintptr_t)this + 0x84) = *(int32_t *)((uintptr_t)this + 0x84) + 1;
        // Set bit 1 (0x02) in the 16-bit flags at offset 0x80
        *(uint16_t *)((uintptr_t)this + 0x80) = *(uint16_t *)((uintptr_t)this + 0x80) | 2;
    }
}