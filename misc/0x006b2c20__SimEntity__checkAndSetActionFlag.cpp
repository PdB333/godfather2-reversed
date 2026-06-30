// FUNC_NAME: SimEntity::checkAndSetActionFlag
void __fastcall SimEntity::checkAndSetActionFlag(SimEntity* thisPtr)
{
    // Check state field at offset +0xC4: must be 0 or 1 (e.g., idle/active)
    int state = *(int*)((char*)thisPtr + 0xC4);
    if ((state != 0 && state != 1) ||
        // Type field at offset +0x40 – skip specific object (e.g., vehicle type 0x637b907)
        *(int*)((char*)thisPtr + 0x40) == 0x637b907 ||
        // Flags at offset +0x34: bit 4 must be clear (e.g., some blocking condition)
        ((*(unsigned int*)((char*)thisPtr + 0x34) >> 4) & 1) != 0 ||
        // Bit 23 must be clear (e.g., action already active)
        ((*(unsigned int*)((char*)thisPtr + 0x34) >> 23) & 1) != 0)
    {
        return;
    }

    // Call into unknown auxiliary check function (0x008c7f80)
    char result = unknownCheckFunction(thisPtr); // returns bool-like
    if (result != 0)
    {
        // Set bit 23 (0x800000) to mark action as started
        *(unsigned int*)((char*)thisPtr + 0x34) |= 0x800000;
    }
}