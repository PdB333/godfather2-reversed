// FUNC_NAME: ReplicatedStateEntry::setStringAndData
// 0x006db520
// Sets the 100-byte string at +0x10, copies current data blocks to sent slots, and marks dirty.
// If the new string differs from the current one, triggers a notification callback.
void __thiscall ReplicatedStateEntry::setStringAndData(const char* newString)
{
    // Compare current string at +0x10 with new string (byte-by-byte, null-terminated)
    const byte* cur = (const byte*)(this + 0x10);
    const byte* src = (const byte*)newString;
    int cmpRes;
    do {
        byte b = *cur;
        bool less = b < *src;
        if (b != *src) {
            cmpRes = (1 - (uint)less) - (uint)(less != 0); // -1, 0, or 1
            break;
        }
        if (b == 0) { cmpRes = 0; break; }
        b = cur[1];
        less = b < src[1];
        if (b != src[1]) {
            cmpRes = (1 - (uint)less) - (uint)(less != 0);
            break;
        }
        cur += 2;
        src += 2;
    } while (b != 0);
    // Note: the loop above is equivalent to strcmp, but we keep the exact logic.

    // Copy new string into current string buffer (100 bytes, 25 * 4)
    byte* dest = (byte*)(this + 0x10);
    const byte* newData = (const byte*)newString;
    for (int i = 25; i != 0; i--) {
        *(uint32*)dest = *(uint32*)newData;
        newData += 4;
        dest += 4;
    }

    // If the string changed, call the update notification function
    if (cmpRes != 0) {
        FUN_006db310(); // notification callback
    }

    // Copy current data to sent data (three groups of two 4-byte values each)
    // Group 1: current at +0x50,0x54 -> sent at +0x104,0x108
    *(uint32*)(this + 0x104) = *(uint32*)(this + 0x50);
    *(uint32*)(this + 0x108) = *(uint32*)(this + 0x54);
    *(byte*)(this + 0x100) = 0; // clear valid flag for group 1

    // Group 2: current at +0x58,0x5c -> sent at +0x134,0x138
    *(uint32*)(this + 0x134) = *(uint32*)(this + 0x58);
    *(uint32*)(this + 0x138) = *(uint32*)(this + 0x5c);
    *(byte*)(this + 0x130) = 0; // clear valid flag for group 2

    // Group 3: current at +0x64,0x68 -> sent at +0x164,0x168
    *(uint32*)(this + 0x164) = *(uint32*)(this + 0x64);
    *(uint32*)(this + 0x168) = *(uint32*)(this + 0x68);
    *(byte*)(this + 0x160) = 0; // clear valid flag for group 3

    // Mark the entry as dirty (unsent changes)
    *(byte*)(this + 0x1a0) = 1;
}