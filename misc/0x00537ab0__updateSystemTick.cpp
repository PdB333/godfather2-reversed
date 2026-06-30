// FUNC_NAME: updateSystemTick
void updateSystemTick(void) {
    // Calls the underlying engine processing function with two global data structures.
    // gSystemManager (0x0121a390) is a pointer to a central manager (e.g., SimManager or GodfatherGameManager).
    // gSystemData (0x0121b638) is a pointer to an internal data block; the value at offset +0x10 is a 4-byte identifier or state.
    FUN_0060ab00(gSystemManager, *(uint32_t*)(gSystemData + 0x10));
    return;
}