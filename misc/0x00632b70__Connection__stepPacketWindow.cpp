// FUNC_NAME: Connection::stepPacketWindow
bool __fastcall Connection::stepPacketWindow(int count, PacketHistory* history) {
    // this pointer in EDI, not standard thiscall
    // +0x5c: mPacketSlotIndex (int)

    PacketEntry* currentEntry = reinterpret_cast<PacketEntry*>(history->mCurrentEntry);  // +0x14
    PacketEntry* startEntry = reinterpret_cast<PacketEntry*>(history->mStartEntry);      // +0x28

    // Scan backwards through the history until count is exhausted
    while (count > 0) {
        // If we've reached the start, we can't go further
        if (currentEntry <= startEntry) {
            // Not enough entries to satisfy count, fail
            if (count > 0) {
                return false;
                // unreachable but the decompiler shows a path
            }
            break;
        }
        count--;  // Each entry counts as at least 1 unit

        // If the entry's first bit is clear, it contributes an extra skip value
        if ((currentEntry->flags[8] & 0x01) == 0) {
            count -= currentEntry->skipValue;  // +0x14
        }

        // Move to previous entry (0x18 = sizeof(PacketEntry))
        currentEntry = reinterpret_cast<PacketEntry*>((uint8_t*)currentEntry - 0x18);
    }

    // After loop, check if we landed exactly on an entry
    if (currentEntry == startEntry) {
        return false;  // Hit the start boundary
    }

    // If we overshot (count became negative), reset the slot index to 0
    if (count < 0) {
        this->mPacketSlotIndex = 0;
        return true;
    }

    // Calculate the zero‑based index of the found entry relative to start
    this->mPacketSlotIndex = static_cast<int>(
        (reinterpret_cast<uintptr_t>(currentEntry) - reinterpret_cast<uintptr_t>(startEntry)) / 0x18
    );
    return true;
}