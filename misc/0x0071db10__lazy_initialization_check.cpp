// FUNC_NAME: lazy_initialization_check

void __fastcall lazy_initialization_check(void* thisPtr)
{
    // +0x84: flags field (bit 0 = initialized)
    uint32_t& flags = *(uint32_t*)((uint8_t*)thisPtr + 0x84);

    if ((flags & 1) == 0)
    {
        flags |= 1;
        // Call actual initialization function (0x007ee2e0)
        FUN_007ee2e0(thisPtr);
    }
}