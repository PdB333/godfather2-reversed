// FUNC_NAME: EntityDataManager::shiftEntityDataBackward
// Function address: 0x005daaa0
// Shifts an array of 40-byte structures backward to fill a gap.
// The destination pointer is passed in the EAX register (not captured as a parameter in Ghidra's decompilation).
// This is used when removing an entity from the middle of a fixed-size array.
typedef unsigned long long QWord; // 8-byte unit

void __thiscall EntityDataManager::shiftEntityDataBackward(void* srcEnd, void* dstEnd) {
    // The actual destination start is in EAX; we must treat it as a hidden input.
    // For reconstruction, we assume the caller has placed the destination pointer in a local variable.
    QWord* dest = /* set by caller */; // Corresponds to in_EAX in decompiled code
    char* src = (char*)srcEnd;
    char* dstEndChar = (char*)dstEnd;

    if (src != dstEndChar) {
        do {
            char* newSrc = src - 0x28; // Move source back by 40 bytes
            // Copy 5 QWords (40 bytes) from source region to destination region
            dest[-5] = *(QWord*)(src - 0x28);
            dest[-4] = *(QWord*)(src - 0x20);
            dest[-3] = *(QWord*)(src - 0x18);
            dest[-2] = *(QWord*)(src - 0x10);
            dest[-1] = *(QWord*)(src - 8);
            dest -= 5; // Move destination pointer back by 5 QWords (40 bytes)
            src = newSrc;
        } while (newSrc != dstEndChar);
    }
}