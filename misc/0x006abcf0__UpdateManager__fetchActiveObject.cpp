// FUNC_NAME: UpdateManager::fetchActiveObject
int __fastcall UpdateManager::fetchActiveObject(int thisPtr)
{
    int objectPtr = *(int*)(thisPtr + 0x10);  // +0x10: currentObject
    if (objectPtr == 0) {
        return 0;
    }

    short status = *(short*)(objectPtr + 0x78);  // +0x78: object status flag
    if (status == 0) {
        // Object is dead; clear the pointer
        *(int*)(thisPtr + 0x10) = 0;
    }
    else if (status == 1 && objectPtr == *(int*)(thisPtr + 0x14)) {
        // Object is fading out and it's the one we're tracking as active
        *(int*)(thisPtr + 0x14) = 0;
    }

    if (objectPtr != 0) {
        // Update the timer for this object (e.g., next wake-up time)
        *(float*)(thisPtr + 0x2c) = *(float*)(thisPtr + 0x24) + g_updateInterval;  // DAT_01205228
        return objectPtr;
    }

    return 0;
}