// FUNC_NAME: AudioStreamManager::getStreamPosition
uint AudioStreamManager::getStreamPosition(uint param_2) // param_1 is unused? Possibly this pointer? But not used.
{
    // Check if stream manager is initialized (flag at +0x1744 relative to global singleton)
    if (*(char *)(g_audioStreamManagerInstance + 0x1744) != '\0') {
        // Get pointer to active stream object from internal cache
        uint streamPtr = getActiveStream(); // FUN_005e2150
        if (streamPtr != 0) {
            // Call virtual function at vtable offset 0x98 (likely getPosition or getStatus)
            // The call takes a value from stream object at offset 0x1cc (maybe a handle or timestamp) and param_2 (e.g., unit mode)
            uint result = ((uint (*)(uint, uint))(*g_audioStreamVTable + 0x98))(*(uint *)(streamPtr + 0x1cc), param_2);
            return result;
        }
    }
    // Return early: clear lower byte of whatever was in EAX (likely error code)
    return in_EAX & 0xffffff00;
}