// FUNC_NAME: SimObject::setData
void __thiscall SimObject::setData(SimObject *this, const byte *sourceData)
{
    // Compare the name string at this+0x10 with the one in sourceData (wide character null-terminated)
    wchar_t *currentName = reinterpret_cast<wchar_t *>(this + 0x10);   // +0x10: name buffer (100 bytes = 50 wchar_t)
    const wchar_t *newName = reinterpret_cast<const wchar_t *>(sourceData);
    int cmpResult = 0;

    while (true) {
        wchar_t curChar = *currentName;
        wchar_t newChar = *newName;
        bool curLess = curChar < newChar;
        if (curChar != newChar) {
            // Result: -1 if curChar < newChar, +1 if curChar > newChar
            cmpResult = (curChar < newChar) ? -1 : 1;
            break;
        }
        if (curChar == 0) break;   // both null terminator -> strings equal
        currentName++;
        newName++;
    }

    // Copy the entire 100-byte input block (name + associated data) into this+0x10
    byte *dest = reinterpret_cast<byte *>(this) + 0x10;
    for (int i = 0; i < 25; i++) {        // 0x19 iterations, 4 bytes each = 100 bytes total
        *(reinterpret_cast<uint32_t *>(dest)) = *(reinterpret_cast<const uint32_t *>(sourceData));
        sourceData += 4;
        dest += 4;
    }

    // If the name changed (cmpResult != 0), call the notification callback
    if (cmpResult != 0) {
        // Name changed callback – updates dependents (e.g., re-register in hash tables)
        onNameChanged();
    }

    // Cache three pairs of values from the original source offsets into separate storage
    // Each pair is a 2D vector (e.g., position, rotation, scale)
    // Source data was at this+0x50, 0x54, 0x58, 0x5C, 0x64, 0x68 (relative to this)
    // But after the copy, those offsets now hold the new values from sourceData
    // So we reread from this+0x50 etc. (the newly copied data)
    // Store cached copies at higher offsets:
    // Pair1: this+0x50 -> this+0x104, this+0x54 -> this+0x108
    *(float *)(this + 0x104) = *(float *)(this + 0x50);
    *(float *)(this + 0x108) = *(float *)(this + 0x54);
    *(byte *)(this + 0x100) = 0;   // flag for pair1 (e.g., "dirty" cleared)

    // Pair2: this+0x58 -> this+0x134, this+0x5C -> this+0x138
    *(float *)(this + 0x134) = *(float *)(this + 0x58);
    *(float *)(this + 0x138) = *(float *)(this + 0x5C);
    *(byte *)(this + 0x130) = 0;   // flag for pair2

    // Pair3: this+0x64 -> this+0x164, this+0x68 -> this+0x168
    *(float *)(this + 0x164) = *(float *)(this + 0x64);
    *(float *)(this + 0x168) = *(float *)(this + 0x68);
    *(byte *)(this + 0x160) = 0;   // flag for pair3

    // Set a global “active” flag
    *(byte *)(this + 0x1A0) = 1;
}