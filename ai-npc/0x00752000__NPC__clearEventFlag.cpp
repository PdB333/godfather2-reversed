// FUNC_NAME: NPC::clearEventFlag
void __fastcall NPC::clearEventFlag(int thisPtr)
{
    // Check if bit 5 (0x20) of the flags field at +0xCC is set.
    if ((*(uint *)(thisPtr + 0xCC) >> 5 & 1) != 0) {
        // Call some reset/clear function with parameters 0,0
        FUN_007f9340(0, 0);
        // Clear the flag by ANDing with the complement of 0x20 (0xFFFFFFDF)
        *(uint *)(thisPtr + 0xCC) &= 0xFFFFFFDF;
    }
}