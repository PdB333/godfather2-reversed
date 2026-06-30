// FUNC_NAME: Entity::finalizeDeferredAction
void __fastcall Entity::finalizeDeferredAction(void* thisPtr)
{
    uint flags = *(uint*)((int)thisPtr + 0x84); // +0x84: bitfield flags
    // Check if bit4 (0x10) is set and bit5 (0x20) is not set
    if (((flags >> 5) & 1) == 0 && ((flags >> 4) & 1) != 0)
    {
        void* actionData = *(void**)((int)thisPtr + 0x5c); // +0x5c: pointer to pending action data
        FUN_00726e10(actionData); // release or process the action data
        // Mark bit5 as completed
        *(uint*)((int)thisPtr + 0x84) |= 0x20;
    }
}