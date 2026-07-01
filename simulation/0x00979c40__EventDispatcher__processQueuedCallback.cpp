// FUNC_NAME: EventDispatcher::processQueuedCallback
// Function address: 0x00979c40
// Role: Checks if a pending callback flag is set (bit 2 at +0x60),
//       then calls a callback registration function (FUN_005c02f0) with 
//       a sub-object at +0x10 and a function pointer (FUN_00979ac0) as argument,
//       and clears the flag afterwards.

void __thiscall EventDispatcher::processQueuedCallback(uint arg1)
{
    // Check if bit 2 (0x04) is set in flags at offset 0x60
    if ((*(uint *)(arg1 + 0x60) >> 2) & 1)
    {
        // Call the callback registration function with:
        //   - pointer to sub-object at +0x10 (likely a callback manager)
        //   - callback function FUN_00979ac0
        //   - parameter 1 (maybe a priority or ID)
        FUN_005c02f0(arg1 + 0x10, FUN_00979ac0, 1);

        // Clear bit 2 in flags
        *(uint *)(arg1 + 0x60) &= ~0x04;   // 0xfffffffb
    }
    return;
}