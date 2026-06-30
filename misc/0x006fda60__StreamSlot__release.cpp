// FUNC_NAME: StreamSlot::release

void __thiscall StreamSlot::release(undefined4 *thisSlot, char invokeCallback)
{
    int slotIndex = thisSlot[10]; // +0x28: slot index
    int *streamManager = (int *)DAT_0112a9f4;

    // If this slot is currently active in the stream manager, clear it
    if ((slotIndex != -1) && (streamManager[0x208 / 4] == slotIndex)) {
        streamManager[0x208 / 4] = -1;
        debugPrint("StreamSlot released\n"); // FUN_005e6640(&LAB_006fd640)
    }

    if (thisSlot[6] != 0) { // +0x18: resource handle
        if ((invokeCallback != '\0') && (thisSlot[0] != (code *)0x0)) { // vtable
            // Call vtable[0] with command 4 and the user data at offset 0x4
            ((code (*)(int, int, int))thisSlot[0])(thisSlot[6], 4, thisSlot[1]);
        }

        int currentTime = getCurrentTimeMs(); // FUN_005e3260
        scheduleRelease(thisSlot[6], currentTime); // FUN_005e2ad0

        // Check flag at byte offset 0x2c (bit 3 = playing)
        if ((*(byte *)(thisSlot + 0xb) & 8) != 0) {
            stopStream(); // FUN_006fd240
        }

        destructorBase(); // FUN_006fd030
    }
}