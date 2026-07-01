// FUNC_NAME: SomeManager::clearAndNotify
void __thiscall SomeManager::clearAndNotify(int thisPtr, int target, undefined4 param3, undefined4 param4)
{
    byte flags;
    int configPtr;
    uint i;

    // If there are pending items, process them
    if (*(int *)(thisPtr + 0x18) != 0) {
        i = 0;
        do {
            processTick();  // FUN_004df600 - likely a per-tick update
            i = i + 1;
        } while (i < *(uint *)(thisPtr + 0x18));
    }
    // Reset the count
    *(undefined4 *)(thisPtr + 0x18) = 0;

    // If a target is provided, check global config flags and send messages
    if ((target != 0) && (configPtr = getGlobalConfig(g_globalConfig), configPtr != 0)) {
        flags = *(byte *)(configPtr + 0x44);  // +0x44: bitmask of enabled events
        if ((flags & 4) != 0) {
            sendMessage(target, param3, param4, kEventEnter);  // DAT_00d83438
        }
        if ((flags & 8) != 0) {
            sendMessage(target, param3, param4, kEventExit);   // DAT_00d83434
        }
        if ((flags & 0x10) != 0) {
            sendMessage(target, param3, param4, kEventSelect); // DAT_00d83430
        }
        if ((flags & 0x20) != 0) {
            sendMessage(target, param3, param4, kEventBack);   // DAT_00d8342c
        }
        if ((flags & 0x40) != 0) {
            sendMessage(target, param3, param4, kEventConfirm);// PTR_LAB_00d83428
        }
        if ((signed char)flags < 0) {  // bit 7
            sendMessage(target, param3, param4, kEventCancel); // DAT_00d83424
        }
    }
}