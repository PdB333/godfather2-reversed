// FUNC_NAME: StreamManager::~StreamManager

void __thiscall StreamManager::destroy(void)
{
    // Set vtable to base class vtable (for proper destruction ordering)
    *(int *)this = (int)&PTR_LAB_00d642b0;

    // Clean up buffer at offset +0x54 (size 0x40 = 64 bytes?)
    FUN_00939710(*(int *)((char *)this + 0x54));
    FUN_00939670(*(int *)((char *)this + 0x54), 0x40);

    // Check bit 3 of flags at +0x50
    if ((*(uint *)((char *)this + 0x50) >> 3 & 1) != 0)
    {
        // Clear bit 3
        *(uint *)((char *)this + 0x50) &= 0xfffffff7;

        // Call virtual function at vtable+0x290 (likely a stop/release method)
        (*(void (__thiscall **)(int, int))(**(int **)((char *)this + 0x54) + 0x290))(1, 1);
    }

    // Check bit 0 of flags
    if ((*(byte *)((char *)this + 0x50) & 1) != 0)
    {
        // If buffer pointer at +0x54 is valid, release global resource
        if (*(int *)((char *)this + 0x54) != 0)
        {
            FUN_0043b870(DAT_01131018);
        }

        // Global reset/clear
        FUN_009ae900(0);

        // Release resource handles if valid and not a sentinel (0x48 = max handle)
        if ((*(int *)((char *)this + 0x58) != 0) && (*(int *)((char *)this + 0x58) != 0x48))
        {
            FUN_007f6420(0x14); // Release handle 0x14 (20)
        }
        FUN_007f6420(0x12); // Release handle 0x12 (18)
        FUN_007f6420(0x13); // Release handle 0x13 (19)
    }

    // Check bit 4 and if buffer is valid, and global condition
    if ((((*(uint *)((char *)this + 0x50) >> 4 & 1) != 0) && (*(int *)((char *)this + 0x54) != 0)) &&
        (FUN_0043b870(DAT_01131040) != 0))
    {
        FUN_009b1250(); // Cleanup global resource
        *(uint *)((char *)this + 0x50) &= 0xffffffef; // Clear bit 4
    }

    // Destroy sub-object at offset +0x58
    if (*(int *)((char *)this + 0x58) != 0)
    {
        FUN_004daf90((char *)this + 0x58);
    }

    // Final global cleanup
    FUN_004ac1e0();
}