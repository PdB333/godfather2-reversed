// FUNC_NAME: SomeInputHistoryClass::recordAction

int __thiscall SomeInputHistoryClass::recordAction(int actionId) {
    // Global time-related variables (likely from game timer)
    float timeScale = *(float*)0x00d5780c / *(float*)0x012067e8;
    int isActive = FUN_00410eb0(); // Checks if game is active (e.g., not paused)
    
    if (isActive != 0 && *(float*)0x00d5f530 < timeScale) {
        int bufferSize = 5; // default history size
        // Query some object at offset 0x564 from a global pointer (likely player or camera)
        int someObj = FUN_00411070(*(byte*)(*(int*)0x012233b4 + 0x564));
        if (*(float*)(someObj + 0x11c) < *(float*)0x00d5f52c) {
            bufferSize = 3; // smaller buffer under certain condition (e.g., low frame rate)
        }
        
        // Write action to circular buffer at this+0x20c, indexed by m_actionIndex (this+0x220)
        int currentIndex = *(int*)(this + 0x220);
        *(int*)(this + 0x20c + currentIndex * 4) = actionId;
        
        // Advance and wrap index modulo bufferSize
        int newIndex = currentIndex + 1;
        *(int*)(this + 0x220) = newIndex % bufferSize;
        
        // The following pointer arithmetic is likely a convoluted way to return the address
        // of the next writable slot or the end of the buffer. The decompiler has obscured it.
        int retPtr;
        int count = 0;
        if (3 < bufferSize) {
            int steps = (bufferSize - 4 >> 2) + 1;
            retPtr = this + 0x210;
            count = steps * 4;
            do {
                retPtr += 0x10;
                steps--;
            } while (steps != 0);
        }
        if (count < bufferSize) {
            retPtr = this + 0x20c + count * 4;
            int remaining = bufferSize - count;
            do {
                retPtr += 4;
                remaining--;
            } while (remaining != 0);
        }
        return retPtr; // Possibly unused by caller
    }
    return isActive;
}