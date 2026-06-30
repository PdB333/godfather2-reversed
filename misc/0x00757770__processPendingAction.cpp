// FUNC_NAME: processPendingAction
void __fastcall processPendingAction(void* this) {
    // Check flag at offset 0xa8, bit 21 (0x200000) indicating pending action
    if ((*(uint*)((int)this + 0xa8) >> 21 & 1) != 0) {
        // Process the action data at offset 0xf4
        FUN_007ee320((int)this + 0xf4);
        // Clear the pending action flag (mask 0xffdfffff)
        *(uint*)((int)this + 0xa8) &= 0xffdfffff;
    }
}