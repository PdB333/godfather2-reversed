// FUNC_NAME: Entity::dispatchPendingEventIfFlagged
void __fastcall Entity::dispatchPendingEventIfFlagged(Entity* this)
{
    // Check if bit 2 (0x4) is set in the flags at offset 0x84
    if ((*(unsigned char*)((uintptr_t)this + 0x84) >> 2 & 1) != 0) {
        undefined4 local_c; // local copy of the global event data
        undefined1* local_8; // unused? set to stack pointer
        undefined1 local_4; // unused? initialized to 0

        local_8 = &stack0x00000004; // stack marker (debugging?)
        local_c = g_pendingEventCallback; // DAT_0112dbd0 - global callback data
        local_4 = 0;

        // Dispatch the pending event with ID 0
        dispatchPendingEvent(&local_c, 0); // FUN_00408a00

        // Clear bit 2 (0x4) in the 16-bit flags at offset 0x84
        *(unsigned short*)((uintptr_t)this + 0x84) &= 0xFFFB;
    }
}